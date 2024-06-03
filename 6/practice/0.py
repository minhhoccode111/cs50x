# print("hello, world")

# words in dictionary
words = set()


def check(word):
    """return true if word is in dictionary else false"""
    return word.lower() in words


def load(dictionary):
    """load dictionary into memory, returning true if success esle false"""
    with open(dictionary) as file:
        words.update(file.read().splitlines())
    return True


def size():
    """return number of words in dictionary if loaded else 0 if not yet loaded"""
    return len(words)


def unload():
    """unloads dictionary from memory, returning true if success else false"""
    return True
