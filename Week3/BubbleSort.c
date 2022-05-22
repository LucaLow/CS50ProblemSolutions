/*
This algorithm is called the bubble sort, it compares two numbers and if one is larger than the other,
swaps them, it does this untill it compleates a loop without any swaps it then prints the sorted result.

The current form of this algorithm sorts in largest to smallest fashion, if you would like smallest to largest.

The time complexity is O(N^2) or more exactly O(N^2 + N - 1)
The minimum time complexity of this algorithm is O(n) this will only happen if the numbers are already sorted.
The space complexity of this algorithm is O(n)
*/
// Library deffinitions
#include <stdio.h>
#include <cs50.h>

// Array to be sorted
int SortArray[] = {12, 34, 69, 84, 0, 9, 50};

// program start point
int main(void)
{
    int NumberOfChanges = 0;
    do
    {
        NumberOfChanges = 0;
        for(int x = 1, length = sizeof(SortArray)/sizeof(SortArray[0]); x < length; x++)
        { // this will move where the pointer for where to compare values are
            if(SortArray[x] < SortArray[x-1]) // to sort smallest to largest chang > to <
            { // if the SortArray[x] is more than  SortArray[x - 1] the values will swap making the larger numbers go to the start, after enough repetitions the array will be ordered.
                NumberOfChanges = NumberOfChanges + 1; // record that a change was made
                int i = SortArray[x];
                SortArray[x] = SortArray[x-1];
                SortArray[x-1] = i;
            }
        }
    }
    while(NumberOfChanges != 0); // While changes are made after a loop of the program

    for(int x = 0, length = sizeof(SortArray)/sizeof(SortArray[0]); x < length; x++) // Print sorted array
    {
        printf("%i ", SortArray[x]);
    }
    printf("\n");
}
