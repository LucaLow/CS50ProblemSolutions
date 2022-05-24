#include <stdio.h>
//#include <cs50.h>
typedef char *string;
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

    /*
        Having fact checked the previous comment and ideas, it turns out a string is a pointer to the first element in a array of chars, this array is sequential
        in memory, this can be repressented by the following code,
    */
    string m = "What do you call some one who is not a dad and makes dad jokes? A pho pa.";
    char *a = &m[0];
    char *k = &m[1];
    printf("\n \n%p, \n%p \n", a, k);
    /*
        The above code returns:
        0x4020b8,
        0x4020b9
        strings and other variables have allocated sections of memory, the hex above is low because the allocated section is low in memory
    */

    /*
        I find this interesting, I can now imagine how the printf("%s") function would work, considering there is a character to signify the end of a string: \0
        I would imagine it would work some what like this
            print information stored at (memory adress)
            memory address ++
            loop back until character signifying end of string is found.
    */

    /*
        A string can be created as a data type via the one line piece of code line(3):
        typedef char *string;

        the typedef keyword indicates that you are creating an alias for a type in other words the lines:
            string x = "Yo dude";
            char *x = "Yo dude";

        are the exact same, the difference being string looks better but has to have the typedef line somewhere,
        this is included in the cs50.h header file somewhere but can be declared by us manually.

        a typedef is written as such: typedef type-definition identifier;

        an alternate use for a typedef is:
            typedef float CarSpeed;

        the string.h header takes char* as input but, because string is an alias for char* they can be used interchangeably

        all this begs the question, what do the double quotes indicate?

        the double quotes indicate to the compiler how to handle memory allocation, so the compiler makes the char memory sequential
    */
   char* b = "Yoo!";
   printf("%c\n", *b);
   printf("%c\n", *(b + 1));
   printf("%c\n", *(b + 2));

   /*
        Above is roughly how I would imagine a print string function would work, until it reaches the aski symbol representing the end of the array
        Result:
        Y
        o
        o
   */
   int y[] = {23, 543, 45, 54, 54}; // Arrays and strings work similar as shown here
   printf("\n%i\n", *b); // Arrays can be treated as a pointer to the first location
   printf("%i\n", *(y + 1));
   printf("%i\n", *(y + 2));
   /*
        malloc gives you a refference to some memory, malloc is a function that takes in the number of bytes you want
        valgrind can check for memory leaks
   */
}
