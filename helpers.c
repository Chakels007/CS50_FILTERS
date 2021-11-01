#include "helpers.h"
#include <stdio.h>
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int average = round(((float)image[y][x].rgbtRed + (float)image[y][x].rgbtGreen + (float)image[y][x].rgbtBlue) / 3);
            image[y][x].rgbtRed = average;
            image[y][x].rgbtGreen = average;
            image[y][x].rgbtBlue = average;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int originalRed = image[y][x].rgbtRed;
            int originalGreen = image[y][x].rgbtGreen;
            int originalBlue = image[y][x].rgbtBlue;

            int sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));
            int sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            int sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtBlue = sepiaBlue;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            RGBTRIPLE tmp = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = tmp;
        }
    }
}

RGBTRIPLE averagePixel(int count, RGBTRIPLE x[count])
{
    float avgr = 0;
    float avgg = 0;
    float avgb = 0;
    for (int i = 0; i < count; i++)
    {
        avgr += (float)x[i].rgbtRed;
        avgg += (float)x[i].rgbtGreen;
        avgb += (float)x[i].rgbtBlue;
    }
    RGBTRIPLE pixel;
    pixel.rgbtRed = round(avgr / count);
    pixel.rgbtGreen = round(avgg / count);
    pixel.rgbtBlue = round(avgb / count);
    return pixel;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
 
    RGBTRIPLE holdingImage[height][width];

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
           
            int blurAmount = 1;
            
            RGBTRIPLE avg[(int)pow((1 + (blurAmount * 2)), 2)];

            int index = 0;

            for (int lrShift = -blurAmount; lrShift <= blurAmount; lrShift++)
            {
               
                if ((x + lrShift < 0) || (x + lrShift >= width))
                {
                    continue;
                }
                
                for (int udShift = -blurAmount; udShift <= blurAmount; udShift++)
                {
                    
                    if ((y + udShift < 0) || (y + udShift >= height))
                    {
                        continue;
                    }
                    
                    avg[index] = image[y + udShift][x + lrShift];
                    index++;
                }
            }
            
            holdingImage[y][x] = averagePixel(index, avg);
        }
    }
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image[y][x] = holdingImage[y][x];
        }
    }
}