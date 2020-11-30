import re
from math import ceil

def main():
    s = input("Text: ")
    letters = count_letters(s)
    words = count_words(s)
    sentences = count_sentences(s)
    L = (letters * 100) / words
    S = (sentences * 100) / words

    index = round(get_index(L, S))

    if (index > 16):
        print("Grade 16+")
        return
    elif(index < 1):
        print("Before Grade 1")
        return

    print(f"Grade {index}")

# Function that gets the Coleman-Liau index
def get_index(L, S):
    return (0.0588 * L - 0.296 * S - 15.8)

def count_sentences(s):
    return len(re.findall("[.!?]", s))


def count_words(s):
    return  len(s.strip().split(" "))

def count_letters(s):
    return len(re.findall("( *?[0-9a-zA-Z] *?)", s))

if __name__ == "__main__":
    main()

