#include <stdio.h>

int main(void)
{
    int b = 420;
    int *a = &b;
    int c = *a;
    printf("c value will be: %d\n", c); // 420
    *a = 69;
    printf("b value will be: %d\n", b); // 69
    a = &c;
    printf("*a value will be: %d\n", *a); // 420
}


