/*
I did not like this project, it did not fully understand what some functions
and variables did.
I must say this project was very difficult, the theory behind the tideman project was confusing
and the difficult bits where much more around tideman ellection theory issues.
I must confess, for some of the answer I took inspiration from: https://joseph28robinson.medium.com/cs50-pset3-tideman-87f22f0f0bc3

I did use the bubble sorting algortim for part of this project, I developed this in a seperate file and copied it over,
found here: https://github.com/LucaLow/CS50ProblemSolutions/blob/main/Week3/SortingAlgorithms/BubbleSort.c
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle(int end, int start);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[]) // this was very confussing, what they want is to know what candidate number ranks[rank] is.
{
    for(int x = 0, length = candidate_count; x < length; x++)
    {
        if(strcmp(name, candidates[x]) == 0) // strcmp is used to compare strings
        {
            ranks[rank] = x; // x is the candidate number for ranks[rank]
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0, length = candidate_count; i < length - 1; i++)
    {
        int over = ranks[i];
        for (int j = i + 1; j < length; j++)
        {
            int under = ranks[j];
            preferences[over][under] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0, length = candidate_count; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            int temp1 = preferences[i][j];
            int temp2 = preferences[j][i];

            if (temp1 > temp2)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if(temp1 < temp2)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    /*
    The function should sort the pairs array in decreasing order of strength of victory, where strength of
    victory is defined to be the number of voters who prefer the preferred candidate.
    If multiple pairs have the same strength of victory, you may assume that the order does not matter.
    */
    int NumberOfChanges;
    do
    {
        NumberOfChanges = 0;
        for (int x = 1, length = pair_count; x < length; x++)
        {
            if(preferences[pairs[x].winner][pairs[x].loser] > preferences[pairs[x-1].winner][pairs[x-1].loser])
            {
                NumberOfChanges = NumberOfChanges + 1;
                pair temp = pairs[x];
                pairs[x] = pairs[x - 1];
                pairs[x - 1] = temp;
            }
        }
    }
    while (NumberOfChanges != 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        // If cycle function returns false, lock the pair
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool cycle(int end, int start)
{ // This function will check if there is a cycle using recursion
    // Return true if there is a cycle created (Recursion base case)
    if (end == start)
    {
        return true;
    }
    // Loop through candidates (Recursive case)
    for (int x = 0; x < candidate_count; x++)
    {
        if (locked[end][x])
        {
            if (cycle(x, start))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
