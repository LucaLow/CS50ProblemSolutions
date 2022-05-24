#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = 52;
    int *p = &x;

    printf("Memory Location Is %p \nInt value = %i\n", p, *p);
    /*
        The first argument, p is a pointer indicated by the line above that, the pointer is printed with %p,
        the second argument, *p reads the information stored at the pointer p, this differs from the first argument
        is as the * reads from the given location.

        That use case is seperate from the one above where *p is defined as &x, the *p before the declaration(line 7)
        indicates that the assigned value will be a pointer to an int.

        The &x in line 7 asigns the memory location of x to p.

        in line 9 the second given argument(*p) reads the information stored at location p and outputs that to an int as deffined
        in the print function, this is also why the on line 7 an int is declared, so that when that pointer is used it will know where,
        how much and the format the information stored will be.
    */
    int j = *p; // This shows how a pointer can be used to read a memory location and output a value.
    printf("Demo for int to pointer to int, value = %i\n", j);
    /*
        I am starting to see how this can be used to create data types where the number of elements is changing, such as a linked list.
    */
    // The next lines will be used to see how this idea interacts with other data types.
    string l = "Yo, my name is Luca!";
    string *z = &l; // I'm starting to run out of letters
    string f = "Hi";
    f = *z; // I have a suspicion this will not return what is expected
    printf("String = %s, \nString to pointer = %p, \nString to pointer to string = %s\n", l, p, f);
    /*
        This was a nice suprise!
        I suspected that setting the value of a string in this manner would cause some sort of overflow as the string took up more characters
        than where intially allocated to it, causing a stack over flow (ha ha) turns out this returns:
            String = Yo, my name is Luca!,
            String to pointer = 0x7fff9e67dbfc,
            String to pointer to string = Yo, my name is Luca!

        having seen this I suspect a string is an array of pointers, not actual characters pointing and setting the value of f only changed the pointers
        being referenced.
    */
}
