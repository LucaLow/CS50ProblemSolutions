#include <stdio.h>

void swap(int* x, int* y);
int main(void)
{
    int x = 1;
    int y = 2;

    printf("x = %i, y = %i\n", x, y);
    swap(&x, &y); // & returns pointer to variable
    printf("x = %i, y = %i\n", x, y);
}

void swap(int* x, int* y)
{
    int temp = *x; // temp = value of x, not pointer to x
    *x = *y; // value of x = value of y
    *y = temp; // value of y = temp
}
