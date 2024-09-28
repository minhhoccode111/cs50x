#include <stdio.h>

int i = 0;


int testFunc();
int main(void)
{
    testFunc();
}

int testFunc()
{
    printf("i belike: %d\n", i); /*  */
    return i;
}


