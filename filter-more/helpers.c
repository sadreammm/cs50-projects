#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width/2;j++){
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int arr[9][2] = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,0},{0,1},
        {1,-1},{1,0},{1,1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red = 0;
            int Green = 0;
            int Blue = 0;
            int count = 0;

            for (int k = 0; k < 9; k++)
            {
                int newi = i + arr[k][0];
                int newj = j + arr[k][1];

                if (newi >= 0 && newi < height && newj >= 0 && newj < width)
                {
                    Blue += image[newi][newj].rgbtBlue;
                    Green += image[newi][newj].rgbtGreen;
                    Red += image[newi][newj].rgbtRed;
                    count++;
                }
            }

            temp[i][j].rgbtBlue = Blue / count;
            temp[i][j].rgbtGreen = Green / count;
            temp[i][j].rgbtRed = Red / count;
        }
    }

    // Copy the blurred values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    return;
}
