#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main (void)
{
    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1); // plus 1 to account for end string char
    for (int i = 0, length = strlen(s) + 1; i < length; i++)
    {
        t[i] = s[i];
    }

    t[0] = toupper(t[0]);

    printf("%s\n", s);
    printf("%s\n", t);
    free(t);
    //free(s); // s was already freed by cs50
    // IF you call maloc you should call free!
    // to check if a pointer is valid check if pointer == NULL most often used in a maloc fail

}
