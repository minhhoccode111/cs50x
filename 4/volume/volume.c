// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header, constant
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");
    // return pointers point to file is NULL
    if (output == NULL || input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // extract the 4th argument
    float factor = atof(argv[3]);

    // an array of 44 bytes to store data from the WAV file header
    // uint8_t header[HEADER_SIZE];

    // at address `input`, read a `HEADER_SIZE` number of elements with the size of `sizeof(uint8_t)` (1 byte) and store at the header address (a block of memory) 

    // define a header pointer point to an address holds 8 bits unsign value, and use malloc to create 44 chunks of 1 byte
    int8_t *header = malloc(HEADER_SIZE);
    // copy header
    fread(header, sizeof(int8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(int8_t), HEADER_SIZE, output);

    int16_t buffer;
    // copy each element till end
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // multi with factor
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
