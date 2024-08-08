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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed,sepiaGreen,sepiaBlue;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed  + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed  + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            if( sepiaRed>255){
                sepiaRed=255;
            }
            if( sepiaGreen>255){
                sepiaGreen=255;
            }
            if( sepiaBlue>255){
                sepiaBlue=255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int arr[9][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 0}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
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

            temp[i][j].rgbtBlue = round((float) Blue / count);
            temp[i][j].rgbtGreen = round((float) Green / count);
            temp[i][j].rgbtRed = round((float) Red / count);
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
