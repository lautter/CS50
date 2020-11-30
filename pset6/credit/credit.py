# trying to figure out the credit cards flags only by theyr numbers

from cs50 import get_string

def main():
    n = get_number()
    if len(n) != 13 and len(n) != 15\
        and len(n) != 16:
            print("INVALID")
    else:
        if luh_alg(n):
            get_flag(n)
        else:
            print("INVALID")

def luh_alg(num):
    mult = 1
    soma = 0
    soma1 = 0
    num_cpy = int(num)
    for i in range(len(num)):
        temp = int(num_cpy / mult) % 10
        if i % 2 != 0:
            temp = 2 * temp
            if temp >= 10:
                temp = (temp % 10) + int(temp / 10)
            soma += temp
        else:
            soma1 += temp
        mult *= 10
    #print(int(soma + soma1))
    if (int(soma + soma1) % 10) == 0:
        return True
    else:
        return False

def get_flag(number):
    l2num = number[:2]
    if l2num[:1] == "4":
        print("VISA")
    elif l2num == "34" or l2num == "37":
        print("AMEX")
    elif int(l2num) in range(51, 56):
        print("MASTERCARD")
    else:
        print("INVALID")
    #print(l2num)

def get_number():
    n = get_string("Number: ")
    return n

if __name__ == "__main__":
    main()
