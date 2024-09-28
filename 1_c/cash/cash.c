#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int coins = 0;

    while (cents > 0)
    {
        coins++;
        if (cents >= 25)
        {
            cents -= 25;
        }
        else if (cents >= 10)
        {
            cents -= 10;
        }
        else if (cents >= 5)
        {
            cents -= 5;
        }
        else
        {
            cents--;
        }
    }

    printf("%i\n", coins);
}
