#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

RGBTRIPLE BlurB(int x, int y, int height, int width, RGBTRIPLE Copy[height][width]);
float Checker(float Check);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++)
        {
            BYTE colour = round((image[y][x].rgbtBlue + image[y][x].rgbtRed + image[y][x].rgbtGreen) / 3.0); // convert to grey scale, / 3.0 was used here to avoid int division
            image[y][x].rgbtRed = colour;
            image[y][x].rgbtGreen = colour;
            image[y][x].rgbtBlue = colour;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++) // Loop through each element in image
    {
        for (int x = 0; x < width; x++)
        {
            int red = round((0.393 * image[y][x].rgbtRed) + (0.769 * image[y][x].rgbtGreen) + (0.189 * image[y][x].rgbtBlue)); // Implement filter algorithm given in cs50, available here: https://cs50.harvard.edu/x/2022/psets/4/filter/less/
            int green = round((0.349 * image[y][x].rgbtRed) + (0.686 * image[y][x].rgbtGreen) + (0.168 * image[y][x].rgbtBlue));
            int blue = round((0.272 * image[y][x].rgbtRed) + (0.534 * image[y][x].rgbtGreen) + (0.131 * image[y][x].rgbtBlue));
            //printf("%i, %i, %i", red, green, blue);
            if(red >= 255){
                image[y][x].rgbtRed = 255;
            }
            else if (red <= 0)
            {
                image[y][x].rgbtRed = 0;
            }
            else
            {
                image[y][x].rgbtRed = red;
            }

            if(green >= 255){
                image[y][x].rgbtGreen = 255;
            }
            else if(green <= 0)
            {
                image[y][x].rgbtGreen = 0;
            }
            else
            {
                image[y][x].rgbtGreen = green;
            }

            if(blue >= 255){
                image[y][x].rgbtBlue = 255;
            }
            else if (blue <= 0)
            {
                image[y][x].rgbtBlue = blue;
            }
            else
            {
                image[y][x].rgbtBlue = blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Mirror[height][width]; // This will be used as a temp variable and will have the current contents of image placed into it

    for (int y = 0; y < height; y++) // Loop through each element of image
    {
        for (int x = 0; x < width; x++)
        {
             Mirror[y][x].rgbtBlue = image[y][x].rgbtBlue; // Copy value image to Mirror variable
             Mirror[y][x].rgbtRed = image[y][x].rgbtRed;
             Mirror[y][x].rgbtGreen = image[y][x].rgbtGreen;
        }
    }

    for (int y = 0; y < height; y++) // Loop through each element of image
    {
        for (int x = 0; x < width; x++)
        {
             image[y][(width - 1) - x].rgbtBlue = Mirror[y][x].rgbtBlue; // set value of image to the reverse of mirror
             image[y][(width - 1) - x].rgbtRed = Mirror[y][x].rgbtRed;
             image[y][(width - 1) - x].rgbtGreen = Mirror[y][x].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE Copy[height][width]; // create a variable with the same dimensions as image

    for (int y = 0; y < height; y++) // Loop through x and y value
    {
        for (int x = 0; x < width; x++)
        {
             Copy[y][x].rgbtBlue = image[y][x].rgbtBlue; // copy contents of image into Copy
             Copy[y][x].rgbtRed = image[y][x].rgbtRed;
             Copy[y][x].rgbtGreen = image[y][x].rgbtGreen;
        }
    }

    for (int y = 0; y < height; y++) // Loop through y value
    {
        for (int x = 0; x < width; x++) // Loop through x value
        {
            image[y][x] = BlurB(x, y, height, width, Copy); // for every pixel run BlurB
        }
    }
    return;
}
RGBTRIPLE BlurB(int x, int y, int height, int width, RGBTRIPLE Copy[height][width])
{
    RGBTRIPLE* colour = malloc(sizeof(RGBTRIPLE)); // This will be the evential return value
    (*colour).rgbtRed = Copy[y][x].rgbtRed; // Refferencing a struct in this way is long hand for what can be found two lines down,
    (*colour).rgbtBlue = Copy[y][x].rgbtBlue; // This gets the value of color, not the pointer and then gets the element of this struct, just doing: color.rgbtBlue would try and get a propperty of a point, color being a pointer, using *color.rgbtBlue would get the value of a pointer at color.rgbtBlue, but rgbtBlue is a byte not a pointer.
    colour->rgbtGreen = Copy[y][x].rgbtGreen; // What this does is gets the value of color from the pointer and access the element rgbtBlue from it.

    int NumberOfChanges = 1; // This will keep track of how many changes happen so that the evential division will be correct, this division will make sure that no value excceds 255 and the picture does not look over exposed.

    float r = Copy[y][x].rgbtRed; // This float will be included in the return values
    float g = Copy[y][x].rgbtGreen;
    float b = Copy[y][x].rgbtBlue;

    if(x - 1 >= 0) // The following lines implement box blur as required by cs50 more information here: https://cs50.harvard.edu/x/2022/psets/4/filter/less/
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y][x - 1].rgbtRed + r;
        g = Copy[y][x - 1].rgbtGreen + g;
        b = Copy[y][x - 1].rgbtBlue + b + 0.00;
    }

    if(x + 1 < width)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y][x + 1].rgbtRed + r;
        g = Copy[y][x + 1].rgbtGreen + g;
        b = Copy[y][x + 1].rgbtBlue + b;
    }

    if(y + 1 < height)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y + 1][x].rgbtRed + r;
        g = Copy[y + 1][x].rgbtGreen + g;
        b = Copy[y + 1][x].rgbtBlue + b;
    }

    if(y - 1 >= 0)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y - 1][x].rgbtRed + r;
        g = Copy[y - 1][x].rgbtGreen + g;
        b = Copy[y - 1][x].rgbtBlue + b;
    }

    if(y - 1 >= 0 && x - 1 >= 0)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y - 1][x - 1].rgbtRed + r + 0.00;
        g = Copy[y - 1][x - 1].rgbtGreen + g + 0.00;
        b = Copy[y - 1][x - 1].rgbtBlue + b + 0.00;
    }

    if(y - 1 >= 0 && x + 1 < width)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y - 1][x + 1].rgbtRed + r + 0.00;
        g = Copy[y - 1][x + 1].rgbtGreen + g + 0.00;
        b = Copy[y - 1][x + 1].rgbtBlue + b + 0.00;
    }

    if(y + 1 < height && x + 1 < width)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y + 1][x + 1].rgbtRed + r + 0.00;
        g = Copy[y + 1][x + 1].rgbtGreen + g + 0.00;
        b = Copy[y + 1][x + 1].rgbtBlue + b + 0.00;
    }
    if(y + 1 < height && x - 1 >= 0)
    {
        NumberOfChanges = NumberOfChanges + 1;
        r = Copy[y + 1][x - 1].rgbtRed + r + 0.00;
        g = Copy[y + 1][x - 1].rgbtGreen + g + 0.00;
        b = Copy[y + 1][x - 1].rgbtBlue + b + 0.00;
    }

    r = r / NumberOfChanges;
    g = g / NumberOfChanges;
    b = b / NumberOfChanges;

    r = Checker(r); // This function will make sure that r, g, and b are no more than 255 and more than 0
    g = Checker(g);
    b = Checker(b);

    r = round(r); // Round the float as it will be parsed to a BYTE in the next function
    g = round(g);
    b = round(b);

    colour->rgbtRed = (BYTE)r;
    colour->rgbtGreen = (BYTE)g;
    colour->rgbtBlue = (BYTE)b;

    return *colour; // Return value of pointer colour
}
float Checker(float Check) // Used to ensure float is within bounds of BYTE
{
    if(Check >= 255)
    {
        return 255;
    }
    else if(Check <= 0)
    {
        return 0;
    }
    return Check;
}
