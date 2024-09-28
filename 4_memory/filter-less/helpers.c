#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                ((float) image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int oldRed = image[i][j].rgbtRed;
            int oldGreen = image[i][j].rgbtGreen;
            int oldBlue = image[i][j].rgbtBlue;
            float sepiaRed = .393 * oldRed + .769 * oldGreen + .189 * oldBlue;
            float sepiaGreen = .349 * oldRed + .686 * oldGreen + .168 * oldBlue;
            float sepiaBlue = .272 * oldRed + .534 * oldGreen + .131 * oldBlue;
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : round(sepiaRed);
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : round(sepiaGreen);
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int half = width / 2;
        // only do half, if width is odd, the middle is truncated anyway
        for (int j = 0; j < half; j++)
        {
            // left pixel, C create a copy, not reference like JS
            RGBTRIPLE tmp = image[i][j];

            // swap
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // start bluring
    // loop row
    for (int i = 0; i < height; i++)
    {
        // loop col
        for (int j = 0; j < width; j++)
        {
            int time = 0;
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            // from -1 on x axis to 1
            for (int x = -1; x < 2; x++)
            {
                // from -1 on y axis to 1
                for (int y = -1; y < 2; y++)
                {
                    // x = 0, y = 0 will be current pixel
                    int currentCol = i + x;
                    int currentRow = j + y;
                    if (currentCol < 0 || currentCol == height || currentRow < 0 ||
                        currentRow == width)
                    {
                        // outside image, do nothing
                    }
                    else
                    {
                        RGBTRIPLE current = copy[currentCol][currentRow];
                        sumRed += current.rgbtRed;
                        sumBlue += current.rgbtBlue;
                        sumGreen += current.rgbtGreen;
                        time++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float) sumRed / time);
            image[i][j].rgbtBlue = round((float) sumBlue / time);
            image[i][j].rgbtGreen = round((float) sumGreen / time);
        }
    }
}

