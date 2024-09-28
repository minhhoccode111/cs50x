from cs50 import get_string


def count_elements(text):
    letters = sum(c.isalpha() for c in text)

    words = len(text.split())

    sentences = text.count(".") + text.count("!") + text.count("?")

    return letters, words, sentences


text = get_string("Text: ")

letters, words, sentences = count_elements(text)


averageNumberOfLettersPer100Words = letters / words * 100

averageNumberOfSentencesPer100Words = sentences / words * 100

index = round(
    0.0588 * averageNumberOfLettersPer100Words
    - 0.296 * averageNumberOfSentencesPer100Words
    - 15.8
)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
