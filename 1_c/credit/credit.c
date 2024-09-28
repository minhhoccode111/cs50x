#include <cs50.h>
#include <stdio.h>
// AMEX: 15 digits, starts 340-349 or 370-379
// VISA: 13 or 16 digits, starts 40-49
// MASTER: 16 digits, starts 51 to 55
// INVALID
int main(void)
{
    long number = get_long("Number: ");
    long numberClone = number;       // so we don't modify the original
    bool isEvenStartFromEnd = false; // flag start at last position
    int sumDigitsMultiByTwo = 0;
    int sumDigitsNotMultiByTwo = 0;
    int counter = 0;    // to know how many digits this number has
    int prevDigits = 0; // to store the last 2 digits, 34 & 37 to Amex, 40 - 49 to Visa, 51 - 55 to Master
    while (numberClone != 0)
    {
        // only store 2 digits
        if (numberClone % 100 > 9)
        {
            prevDigits = numberClone % 100;
        }
        int digit = numberClone % 10;
        if (isEvenStartFromEnd)
        {
            int multipliedByTwo = digit * 2;
            if (multipliedByTwo > 9)
            {
                // split to 2 digits
                sumDigitsMultiByTwo += (1 + multipliedByTwo % 10);
            }
            else
            {
                sumDigitsMultiByTwo += multipliedByTwo;
            }
        }
        else
        {
            sumDigitsNotMultiByTwo += digit;
        }
        counter++;                                // count 1 digit
        isEvenStartFromEnd = !isEvenStartFromEnd; // swap flag
        numberClone /= 10;                        // remove last digit
    }
    int sum = sumDigitsMultiByTwo + sumDigitsNotMultiByTwo;
    // invalid if not end with 0
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if ((counter == 15 && prevDigits == 34) || (counter == 15 && prevDigits == 37))
        {
            printf("AMEX\n");
        }
        else if ((counter == 13 && prevDigits > 39 && prevDigits < 50) || (counter == 16 && prevDigits > 39 && prevDigits < 50))
        {
            printf("VISA\n");
        }
        else if (counter == 16 && prevDigits > 50 && prevDigits < 56)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

