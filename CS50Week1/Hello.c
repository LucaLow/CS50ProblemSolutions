// Included libraries
#include <stdio.h>
#include <cs50.h>

// Program entry point
int main(void)
{
    string Name = get_string("What is your name? "); // Get name and print output
    printf("Hello, %s.\n", Name);
}
