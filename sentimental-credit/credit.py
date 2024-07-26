import re


def main():
    ccNo = input("Number: ")

    if not ccNo.isdigit():
        print("INVALID")
        return
    
    checkSum = cardValidator(ccNo)
    if checkSum:
        digitValidator(ccNo)
    else:
        print("INVALID")


def digitValidator(ccNo):
    if re.search("^(34|37)[0-9]{13}$",ccNo):
        print("AMEX")
    elif re.search("^5[1-5][0-9]{14}$",ccNo):
        print("MASTERCARD")
    elif re.search("^4[0-9]{12}(?:[0-9]{3})?$",ccNo):
        print("VISA")
    else:
        print("INVALID")


def cardValidator(ccNo):
    length = len(ccNo)
    s1=0
    s2=0
    sumCard=0
    for i in range(length-2,-1,-2):
        s=str(int(ccNo[i])*2)
        for j in s:
            s1+=int(j)
    for i in range(length-1,-1,-2):
        s2+=int(ccNo[i])

    sumCard = s1+s2
    if(sumCard%10==0):
        return True
    else:
        return False


if __name__=="__main__":
    main()
