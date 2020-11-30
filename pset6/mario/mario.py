
from cs50 import get_int

def main():
    n = get_n()
    print_pyramid(n)

def get_n():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            return n

def print_pyramid(h):
    spaces = h - 1
    for i in range(h):
        spaceL = spaces
        spaceR = h - spaces
        for j in range(h):
            if spaceL == 0:
                print("#", end="")
            else:
                print(" ", end="")
                spaceL -= 1
        print("  ", end="")
        for k in range(spaceR):
            print("#", end="")
        print("")
        spaces -= 1

if __name__ == "__main__":
    main()
