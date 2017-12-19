### 16 April 2017
### Yeong Zhi Wei

### direct porting from mario.c

import sys

def main():
    while True:
        try:
            print("Height: ", end="")
            height = int(input())
            
            if height >= 0 and height < 24:
                break
            
            print("Enter [0, 23] only.")
        except ValueError:
            print("Enter [0, 23] only.")
    
    for i in range(height):
        j = (height - i) - 1
        while j > 0:
            print(" ", end="")
            j -= 1
        
        j = i + 1
        while j > 0:
            print("#", end="")
            j -= 1
            
        print("  ", end="")
        
        j = i + 1
        while j > 0:
            print("#", end="")
            j -= 1
            
        print("")
        
    exit(0)
            
        
            
    
    
if __name__ == "__main__":
    main()