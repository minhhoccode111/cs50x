#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


string encrypt (string input, int key);
char transform (char ch, int key);

int main (int argc, string argv[])
{

    // not 2 command line arguments print usage and quit
    if (argc != 2) 
    {
        printf("Usage: ./ceasar key\n");
        return 0;
    }

    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        char ch = argv[1][i];
        // second command line argument contain a char that not digit, print usage and quit
        if (!isdigit(ch))
        {
            printf("Usage: ./ceasar key\n");
            return 0;
        }
    }

    int key = atoi(argv[1]);

    string input = get_string("plaintext:  ");

    string encrypted = encrypt(input, key);

    printf("ciphertext: %s\n", encrypted);
    return 0;

}

string encrypt (string input, int key)
{
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        input[i] = transform(input[i], key);
    }

    return input;
}

char transform (char ch, int key)
{
    // don't touch char not in alphabet
    if (!isalpha(ch))
    {
        return ch;
    }
    // do the transform
    bool is_uppercase = isupper(ch);

    // handle different cases
    char base;
    if (isupper(ch))
    {
        base = 'A';
    }
    else
    {
        base = 'a';
    }

    ch = (ch - base + key) % 26 + base; 
    return ch;
}
