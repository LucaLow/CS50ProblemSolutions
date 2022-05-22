/*
The selection sort is one of the less efficient sorting algorithms but was very
easy for my first sorting algorithm attempt

The way I have written this algorithm was almost as efficient as possible.
The time space complexity for the selection sort is: O(n ^ 2/2 + n/2) or more simply O(n^2),
this algorithm will act the same regardless of whether or not the given array is sorted and so the
Omega of this algorith is the same as the big O. This makes the algorithm 
*/

// Library deffinitions
#include <stdio.h>

// Array to be sorted
int SortArray[] = {12, 34, 69, 84, 0, 9, 50, 450};

// program start point
int main(void)
{
    for(int x = 0, length = sizeof(SortArray)/sizeof(SortArray[0]); x < length; x++) // for more information on selection sorting visit: https://www.geeksforgeeks.org/selection-sort/
    {
        int lowestRecordedNumber; // Record what the lowest number found was
        int recordedPosition; // We need to record where the lowest number was found and so is stored here

        for(int j = x; j < length; j++) // For a cool visualisation of this visit: https://www.youtube.com/watch?v=92BfuxHn2XE
        {
            if(j == x) // set initial value otherwise both numbers will defult to 0 leading to an error when
            {
                lowestRecordedNumber = SortArray[j];
                recordedPosition = j;
            }

            if(SortArray[j] < lowestRecordedNumber)
            {
                lowestRecordedNumber = SortArray[j];
                recordedPosition = j;
            }
        }
        SortArray[recordedPosition] = SortArray[x];
        SortArray[x] = lowestRecordedNumber;
    }

    for(int x = 0, length = sizeof(SortArray)/sizeof(SortArray[0]); x < length; x++) // Print sorted array
    {
        printf("%i ", SortArray[x]);
    }
    printf("\n");
}
