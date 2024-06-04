#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j >= 0; j--)
        {
            if (j <= i)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int j = 0; j < height; j++)
        {
            if (j <= i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

