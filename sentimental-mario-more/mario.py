from cs50 import get_int

def main():
    while True:
        height = get_int("Height: ")
        if height>=1 and height<=8:
            build(height)
            break


def build(h):
    for i in range(1,h+1):
        space = h-i
        for j in range(space,0,-1):
            print(" ",end="")
        for k in range(1,i+1):
            print("#",end="")

        print("  ",end="")
        for l in range(1,i+1):
            print("#",end="")
        print()

main()
