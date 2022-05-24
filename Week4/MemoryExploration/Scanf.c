#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x); // scanf, takes type and pointer to variable changes the value of x.
    printf("x: %i\n", x);
  
    char* s = malloc(4); // must be 4 - 1
    printf("s: ");
    
    scanf("%s", s);
    printf("s: %s\n", s);

}
