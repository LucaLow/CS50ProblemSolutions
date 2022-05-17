#include <stdio.h>
#include <cs50.h>

string name;
int main(void){
    name = get_string("What is your name? ");
    printf("Hello, %s.\n", name);
}
