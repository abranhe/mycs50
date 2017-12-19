### 16 April 2017
### Yeong Zhi Wei

### modified from mario.c and optimised

def main():
    while True:
        try:
            print("Number: ", end="")
            cc = input()
            int(cc) # check whether the input is a string of numbers
            break
        except ValueError:
            print("Enter numbers only.")
            
    
    if len(cc) == 15 and (int(cc[:2]) == 34 or int(cc[:2]) == 37) and checksum(cc):
        print("AMEX")
    elif len(cc) == 16 and int(cc[:2]) < 56 and int(cc[:2]) > 50 and checksum(cc):
        print("MASTERCARD")
    elif (len(cc) == 13 or len(cc) == 16) and int(cc[:1]) == 4 and checksum(cc):
        print("VISA")
    else:
        print("INVALID")
        exit(1)
    
    exit(0)

def checksum(cc):
    chksm = 0
    
    if len(cc) % 2 == 0:
        first = 1
    else:
        first = 0
    
    for i in range(len(cc)):
        sm = int(cc[i])
        if i % 2 == first:
            chksm += sm
        else:
            sm *= 2
            if len(str(sm)) == 2:
                chksm = chksm + int(str(sm)[0]) + int(str(sm)[1])
            else:
                chksm += sm
    
    return chksm % 10 == 0
    

if __name__ == "__main__":
    main()