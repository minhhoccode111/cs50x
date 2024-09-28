#include <stdio.h>

typedef char* string;

void dummy(char **a);

int main(void)
{
    char *s0 = "Tai Vi Sao";

    printf("%s\n", s0);

    string s1 = "Khong Dieu Kien";

    printf("%s\n", s1);

    // pass address of variable s1, which hold the address of first char in string
    dummy(&s1);
}

// dummy takes in an address that hold an address that hold a char
void dummy(char* *a)
{
    // then print char as string, by go to that address to get the address of first char
    printf("a belike: %s\n", *a); // Khong Dieu Kien
}
