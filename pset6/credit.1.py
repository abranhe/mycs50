### 16 Apr 2017
### Yeong Zhi Wei

### direct porting from credit.c

def main():
    while True:
        try:
            print("Number: ", end="")
            x = int(input())
            break
        except ValueError:
            print("Enter numbers only.")
            
    if (x - dec(15) < 0 and (x // dec(13) % 100 == 34 or x // dec(13) % 100 == 37) and checksum(x, 15)):
        print("AMEX")
    elif (x - dec(16) < 0 and x // dec(14) % 100 < 56 and x // dec(14) % 100 > 50 and checksum(x, 16)):
        print("MASTERCARD")
    elif (((x - dec(13) < 0 and x // dec(12) % 10 == 4) or (x - dec(16) < 0 and x // dec(15) % 10 == 4)) and checksum(x, 16)):
        print("VISA")
    else:
        print("INVALID")
        exit(1)
    
    exit(0)


def dec(n):
    x = 1
    for i in range(n):
        x *= 10
    return x

def checksum(x, n):
    chksm = 0
    for i in range(n):
        chksm += x // dec(i*2) % 10
    for i in range(n-1):
        a = (x // dec(i*2+1) % 10) * 2
        chksm += a // dec(1) % 10 + a % 10
    return chksm % 10 == 0
        
    

if __name__ == "__main__":
    main()