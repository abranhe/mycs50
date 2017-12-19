from flask import Flask, redirect, render_template, request, url_for

import os
import sys
import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)

    # TODO
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    
    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)
    
    pos, neg, neu = 0.0, 0.0, 0.0
    
    # analyze tweets
    for t in tweets:
        score = analyzer.analyze(t)
        if score > 0.0:
            pos += 1
        elif score < 0.0:
            neg += 1
        else:
            neu += 1
    
    tweetslen = len(tweets)
    positive, negative, neutral = pos / tweetslen, neg / tweetslen, neu / tweetslen

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
