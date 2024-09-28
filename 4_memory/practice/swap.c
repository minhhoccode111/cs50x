#include <stdio.h>
#include <cs50.h>


void swap(int *a, int *b);

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("x belike: %d\n", x);
    printf("y belike: %d\n", y);

    // pass addresses of x and y instead of copy values swap(x, y)
    swap(&x , &y);

    printf("x belike: %d\n", x);
    printf("y belike: %d\n", y);
}

// swap takes in 2 addresse arguments a, b
// each address will hold an int
void swap(int *a, int *b)
{
    // go to address a and get the value in it, store in temporary variable
    int tmp = *a;

    // a is a variable that hold an address that hold an int
    // or a is a pointer that point to an address that hold an int
    // and *a will go to that address to get the value in it 
    // when *a is at the right side of `=` 
    // or set the value in it when *a is at the left side of `=`
    *a = *b;

    // go to b address and set the value of tmp back to that address
    *b = tmp;
}
