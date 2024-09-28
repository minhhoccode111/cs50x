import re


def is_valid_credit_card(number):
    # Remove any non-digit characters from the number
    number = re.sub(r"\D", "", number)

    # Check if the number matches the credit card number pattern
    pattern = re.compile(r"^(?:\d{13,16})$")
    if not pattern.match(number):
        return False

    # Convert the number to a list of digits
    digits = []
    for d in number:
        digits.append(int(d))

    # Multiply every other digit by 2, starting from the second-to-last digit
    i = len(digits) - 2
    while i >= 0:
        digits[i] *= 2
        if digits[i] > 9:
            digits[i] -= 9
        i -= 2

    # Calculate the sum of all digits
    total_sum = sum(digits)

    # Check if the last digit of the sum is 0
    return total_sum % 10 == 0


def get_credit_card_type(number):
    # Define regex patterns for each credit card type
    amex_pattern = re.compile(r"^3[47]\d{13}$")
    mastercard_pattern = re.compile(r"^5[1-5]\d{14}$")
    visa_pattern = re.compile(r"^4(\d{12}|\d{15})$")

    # Check the number against each pattern to determine the card type
    if amex_pattern.match(number):
        return "AMEX"
    elif mastercard_pattern.match(number):
        return "MASTERCARD"
    elif visa_pattern.match(number):
        return "VISA"
    else:
        return "INVALID"


# Prompt the user for a credit card number
number = input("Number: ")

# Remove any non-digit characters from the input
number = re.sub(r"\D", "", number)

# Check if the credit card number is valid
if is_valid_credit_card(number):
    # If valid, print the credit card type
    print(get_credit_card_type(number))
else:
    print("INVALID")
