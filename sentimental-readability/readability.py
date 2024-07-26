def main():
    text = input("Text: ")
    X = index(text)
    if X<1:
        print("Before Grade 1")
    elif X<16:
        print("Grade",X)
    else:
        print("Grade 16+")

def index(text):
    L=0
    S=0
    W=1

    for c in text:
        if c.isalpha():
            L+=1
        elif c.isspace():
            W+=1
        elif c in ['.','!','?']:
            S+=1

    L = (L/W)*100
    S = (S/W)*100

    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)

if __name__=="__main__":
    main()
