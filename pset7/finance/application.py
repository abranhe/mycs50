from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    # query the symbol of the stocks the user is holding
    query = db.execute("SELECT symbol FROM transactions WHERE user_id=:user_id GROUP BY symbol", user_id=session["user_id"])
    # list of dict for rendering in html
    rows = []
    stockexists = False
    # fair value price of all stocks
    grandtotal = 0
    # iterate through symbols
    for row in query:
        # query number of shares held
        query2 = db.execute("SELECT sum(shares) FROM transactions WHERE symbol=:symbol AND user_id=:user_id GROUP BY symbol", symbol=row['symbol'], user_id=session["user_id"])
        shares = query2[0]['sum(shares)']
        # skip if not holding the shares (where no. of shares sold = no. of shares purchased)
        if shares <= 0: 
            continue
        # make a dictionary to insert into rows[]
        dictt = {}
        result = lookup(row['symbol'])
        dictt["symbol"] = result['symbol']
        dictt["name"] = result['name']
        dictt["shares"] = shares
        dictt["price"] = usd(result['price'])
        grandtotal += dictt["shares"] * result['price']
        dictt["total"] = usd(dictt["shares"] * result['price'])
        # insert into rows[]
        rows.append(dictt)
        stockexists = True
    return render_template("index.html", stocks=rows, grandtotal=usd(grandtotal), stockexists=stockexists)
    # return apology("TODO")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    # query how much user has
    query = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    cash = query[0]['cash']
        
    if request.method == "POST":
        # ensure user entered symbol
        if not request.form.get("symbol"):
            return apology("Enter stock's symbol")
        # ensure user entered number of shares
        if not request.form.get("shares"):
            return apology("Enter number of shares to buy")
        # ensure user entered positive number of shares
        try:
            if int(request.form.get("shares")) <= 0:
                return apology("Enter positive number of shares to buy")
        except ValueError:
            return apology("Enter positive number of shares to buy")
        
        # look up the stock and ensure it is valid
        result = lookup(request.form.get("symbol"))
        if result == None:
            return apology("Stock's symbol does not exist.")
            
        # makes a purchases
        symbol = result['symbol']
        name = result['name']
        shares = int(request.form.get("shares"))
        price = result['price']
        cost = shares * price
        
        # abort the purchase if cash is not enough
        if cost > cash:
            return apology("You do not have enough money!")
        
        # record stock name & symbol in stock table
        if not db.execute("SELECT symbol FROM stock WHERE name = :name", name=name):
            db.execute("INSERT INTO stock (name, symbol) VALUES (:name, :symbol)", name=name, symbol=symbol)
        # record the purchases
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=shares, price=price)
        cash = cash - cost
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash, user_id=session["user_id"])
        return render_template("bought.html", symbol=symbol, name=name, price=usd(price), shares=shares, paid=usd(cost), cash=usd(cash))
    else:
        return render_template("buy.html", cash=usd(cash))
    # return apology("TODO")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    # query the history of users' transaction
    query = db.execute("SELECT * FROM transactions WHERE user_id=:user_id ORDER BY datetime", user_id=session["user_id"])
    # list of dict for rendering in html
    rows = []
    sn = 0
    # iterate through query
    for row in query:
        sn += 1
        dictt = {}
        dictt['sn'] = sn
        dictt['datetime'] = row['datetime']
        dictt['nature'] = 'bought' if row['shares'] > 0 else 'sold'
        dictt['symbol'] = row['symbol']
        query = db.execute("SELECT name FROM stock WHERE symbol = :symbol", symbol=row['symbol'])
        dictt['name'] = '' if not query else query[0]['name']
        dictt['shares'] = abs(row['shares'])
        dictt['price'] = usd(row['price'])
        dictt['total'] = usd(-row['shares'] * row['price'])
        rows.append(dictt)
    return render_template("history.html", stocks=rows, sn=sn)  
    # return apology("TODO")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # look up the stock and ensure it is valid
        result = lookup(request.form.get("symbol"))
        if result == None:
            return apology('could not find the stock.')
        else:
            return render_template("quoted.html", name=result['name'], price=usd(result['price']), symbol=result['symbol'])
            
    else:
        return render_template("quote.html")
    # return apology("TODO")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    if request.method == "POST":
        # check username
        if not request.form.get("username"):
            return apology("enter username")
        elif request.form.get("username") == db.execute("SELECT username FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("username already exists")
        
        # check password
        if not request.form.get("password"):
            return apology("enter password")
        elif request.form.get("password") != request.form.get("password2"):
            return apology("password does not match")
        
        # add new user to db
        hash = pwd_context.encrypt(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=hash)
        flash('You have successfully created your account. Please login.')
        return render_template("login.html")
        
    else:
        return render_template("register.html")
    # return apology("TODO")
    

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # ensure user entered symbol
        if not request.form.get('symbol'):
            return apology('Enter stock''s symbol')
        # ensure user entered number of shares
        if not request.form.get('shares'):
            return apology('Enter number of shares to sell')
        # ensure user entered positive number of shares
        try:
            if int(request.form.get('shares')) <= 0:
                return apology("Enter positive number of shares to sell")
        except ValueError:
            return apology("Enter positive number of shares to sell")
            
        symbol = request.form.get('symbol')
        shares2sell = int(request.form.get('shares'))
            
        # look up the stock and ensure it is valid
        result = lookup(symbol)
        if result == None:
            return apology('could not find the stock')
        
        # query no of shares holding
        query = db.execute("SELECT sum(shares) FROM transactions WHERE symbol=:symbol AND user_id=:user_id GROUP BY symbol", symbol=symbol, user_id=session["user_id"])
        if not query:
            return apology(' you don''t have the shares!')
        shares = query[0]['sum(shares)']
        if shares == 0:
            return apology('you don''t have the shares!')
        if shares < shares2sell:
            return apology('you can''t sell more shares than what you have')
            
        price = result['price']
        
        # record the sales
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=-shares2sell, price=price)
        
        # query and update cash in users table
        query = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        cash = query[0]['cash']
        cash = cash + (price * shares2sell)
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash, user_id=session["user_id"])
        
        flash('You have successfully sold the shares.')
        return redirect(url_for("index"))
              
    else:
        return render_template("sell.html")
    #return apology("TODO")

@app.route("/changepass", methods=["GET", "POST"])
@login_required
def changepass():
    if request.method == "POST":
        # check inputs
        if not request.form.get("currentpass"):
            return apology("enter your current password")
        if not request.form.get("password"):
            return apology("enter your new password")
        elif request.form.get("password") != request.form.get("password2"):
            return apology("new password do not match")
            
        
        # check current password
        query = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id=session["user_id"])
        if not pwd_context.verify(request.form.get("currentpass"), query[0]["hash"]):
            return apology("your current password is incorrect")
        
        # update new password in users
        hash = pwd_context.encrypt(request.form.get("password"))
        db.execute("UPDATE users SET hash = :hash WHERE id = :user_id", hash=hash, user_id=session["user_id"])
        flash('You have successfully changed your password.')
        return redirect(url_for("index"))
    else:
        return render_template("changepass.html")