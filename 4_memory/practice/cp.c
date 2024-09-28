#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

typedef int8_t BYTE ;

int main(int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb");
    FILE *des = fopen(argv[2], "wb");

    BYTE b;
    while (fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, des);
    }

    fclose(src);
    fclose(des);
}
