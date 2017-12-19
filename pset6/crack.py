### 16 April 2017
### Yeong Zhi Wei

### adapted from crack.c & optimised

import sys
import crypt

def main():
    if len(sys.argv) != 2:
        print("Usage: ./crack hash")
        exit(1)
        
    alpha = []
    for i in range(26):
        alpha.append(chr(i+65))
    for i in range(26):
        alpha.append(chr(i+97))
        
    # print("{}".format(alpha))
    
    # brute force single character password
    for i in alpha:
        if crypt.crypt(i, "50") == sys.argv[1]:
            solved(i)
    
    # brute force double character password
    for i in alpha:
        for j in alpha:
            if crypt.crypt(i+j, "50") == sys.argv[1]:
                solved(i+j)
    
    # brute force triple character password
    for i in alpha:
        for j in alpha:
            for k in alpha:
                if crypt.crypt(i+j+k, "50") == sys.argv[1]:
                    solved(i+j+k)
                
    # brute force quad character password               
    for i in alpha:
        for j in alpha:
            for k in alpha: 
                for l in alpha:
                    if crypt.crypt(i+j+k+l, "50") ==sys.argv[1]:
                        solved(i+j+k+l)
    
    print("Error: Unable to find the password")
    exit(1)
    
def solved(p):
    print(p)
    exit(0)
    
if __name__ == "__main__":
    main()