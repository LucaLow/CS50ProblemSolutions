//Library Declarations
#include <stdio.h>
#include <cs50.h>
// Variable Declarations
int Height;
const char StartC = ' ';
const char EndC = '#';
// Function Declarations, this is required in C to show the functions which are going to be used, the CLANG compiler requires this
void PrintThing(int x, char _StartC, char _EndC, int _Height);

int main(void)
{
    do
    {
        Height = get_int("Line height? ");
    }
    while (Height <= 0 || Height >= 9);
    // This for loop is used to make the width of this program smaller
    for (int x = Height; x > 0; x--)
    {
        //This Function is used to print the apropriate number of hashes, a function is used here as dirrectly writing out what this program does here would make the program very obese
        PrintThing(x, StartC, EndC, Height);
        printf("\n");
    }
}

// Function Definitions
void PrintThing(int x, char _StartC, char _EndC, int _Height)
{
    // This program largely follows what is shown in Problem 1 the changes will be outlined
    for (int i = 1; i < x; i++)
    {
        printf("%c", _StartC);
    }
    for (int i = _Height; i >= x; i--)
    {
        printf("%c", _EndC);
    }
    // This line is used to show the space in between the lines in the hashes.
    printf("  ");
    // This program has been changed to print the hashes first, I do not require the spaces as they would fill empty space that is not read either.
    for (int i = _Height; i >= x; i--)
    {
        printf("%c", _EndC);
    }
}
