#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int newPix = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newPix = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = newPix;
            image[i][j].rgbtGreen = newPix;
            image[i][j].rgbtRed = newPix;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int newBlue, newGreen, newRed = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newBlue = round(.131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen + .272 * image[i][j].rgbtRed);
            newGreen = round(.168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen + .349 * image[i][j].rgbtRed);
            newRed = round(.189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen + .393 * image[i][j].rgbtRed);

            newRed > 255 ? newRed = 255 : newRed;
            newGreen > 255 ? newGreen = 255 : newGreen;
            newBlue > 255 ? newBlue = 255 : newBlue;

            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temPix;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, tail = width - 1; j < tail; j++, tail--)
        {
            temPix = image[i][j];
            image[i][j] = image[i][tail];
            image[i][tail] = temPix;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float count;
    int newBlue, newGreen, newRed;
    RGBTRIPLE reImage[height][width];

    for (int i = 0; i < height; i++)
    {
    	for (int j = 0; j < width; j++)
    	{
    	    newBlue = newGreen = newRed = 0;
    	    count = 0.0;

    		for (int k = -1; k < 2; k++)
    		{
    			for (int l = -1; l < 2; l++)
    			{
    				if (i + k < 0 || i + k >= height)
		    		{
		    			continue;
		    		}
		    		else if (j + l < 0 || j + l >= width)
		    		{
		    			continue;
		    		}
		    		else
                    {
                        newRed += image[i+k][j+l].rgbtRed;
                        newGreen += image[i+k][j+l].rgbtGreen;
                        newBlue += image[i+k][j+l].rgbtBlue;
                        count += 1;
                    }
                }
    		}
    		reImage[i][j].rgbtBlue = round(newBlue / count);
    		reImage[i][j].rgbtGreen = round(newGreen / count);
    		reImage[i][j].rgbtRed = round(newRed / count);

    	}
    }

    for (int i = 0; i < height; i++)
    {
    	for (int j = 0; j < width; j++)
    	{
    	    image[i][j] = reImage[i][j];
    	}
    }
}
