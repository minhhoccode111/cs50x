#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[])
{
    // accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open the memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // create a buffer for a block of data
    uint8_t buffer[512];

    // count number of images to create names
    int number = 0;

    // a pointer point to 8 bytes chunk for 8 char, xxx.jpg\0
    char file_name[8];

    // combine number with .jpg to write to file_name 
    sprintf(file_name, "%03i.jpg", number);

    // pre-open first file with the name to write
    FILE *current = fopen(file_name, "w");

    // make sure open success
    if (current == NULL)
    {
        printf("Could not open file.\n");
        return 3;
    }

    // flag to identify first file header found
    int isFirst = 1;

    // keep reading the card 512 bytes at a time till its end
    // and store in buffer
    while (fread(buffer, 1, 512, card) == 512)
    {
        // check if 4 bytes of this buffer chunk is header
        int isStart = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0;

        // if 4 bytes of this buffer chunk is header
        if (isStart)
        {
            // if it's the first JPEG we found
            if (isFirst)
            {
                // turn off flag
                isFirst = 0;
                // nothing to do since we pre-open a file above
            }
            // else not first JPEG
            else
            {
                // close previous open JPEG
                fclose(current);
                // increase number for new name
                number++;
                sprintf(file_name, "%03i.jpg", number);
                // open new file
                current = fopen(file_name, "w");
            }

            // then write the to the file (the header part)
            fwrite(buffer, 1, 512, current);
        }
        // else not header
        else
        {
            // if already found JPEG
            if (!isFirst)
            {
                // then write the to the file (the body part)
                fwrite(buffer, 1, 512, current);
            }
            // else do nothing
        }
    }

    // close any remaining files
    fclose(card);
    fclose(current);
}
