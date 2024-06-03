from cs50 import get_int

while True:
    number = get_int("Height: ")
    if number > 0 and number < 9:
        break

# start from 0 to number - 1
index = 1
while index <= number:
    print(("#" * index).rjust(number, " "), end="")
    print("  ", end="")
    print("#" * index)
    index += 1
