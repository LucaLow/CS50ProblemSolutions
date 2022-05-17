// Library Declaration
#include <stdio.h>
#include <cs50.h>
//Variable Declaration and Definition
int Height = 106;
char StartC = ' ';
char EndC = '#';
// Program Entry Point
int main(void)
{
    do
    {
        Height = get_int("Line height? ");
    }
    while (Height <= 0 || Height >= 9);

    // This will declare the variable x starting with the value of Height and decrementing in the for loop
    for (int x = Height; x > 0; x--)
    {
        //This will print x number of spaces, x will decrease over time and so the number of spaces will too
        for (int i = 1; i < x; i++)
        {
            printf("%c", StartC);
        }
        // This will print Height - x number of HashTags the number of hashtags will increase over time as the value of x decrements
        for (int i = Height; i >= x; i--)
        {
            printf("%c", EndC);
        }
        // This will create a new line in the console
        printf("\n");
    }
}
