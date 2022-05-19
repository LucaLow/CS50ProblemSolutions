// Library deffinition
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Method declarations
int CountLetters(string s);
int CountWords(string s);
int CountSentences(string s);
string CalculateYearLevel(int SentenceCount, int WordCount, int LetterCount, string s);

// Program start point
int main(void)
{
    string plainText = get_string("Text: ");
    int numberOfSentences = CountSentences(plainText); // A sentence is any sequence of characters seperated by a full stop, exclamation mark or question mark.
    int numberOfWords = CountWords(plainText); // Any sequence of characters seperated by a space is to be considered a word
    int numberOfLetters = CountLetters(plainText); // A letter is a - z lower and upper case.
    string YearLevel = CalculateYearLevel(numberOfSentences, numberOfWords, numberOfLetters, plainText); // Calculates year level with rounding for input.
    //printf("Sentence Count: %i\n", numberOfSentences);
    //printf("Word Count: %i\n", numberOfWords);
    //printf("Letter Count: %i\n", numberOfLetters);
    //printf("%s\n", YearLevel);

}
int CountSentences(string s){
    char Buffer[3] = {'.', '!', '?'};
    int SentenceCount = 0;
    for (int x = 0, Length = strlen(s); x < 3; x++)
    {
        for(int z = 0; z <= Length; z++)
        {
            if (s[z] == Buffer[x])
            {
                SentenceCount++;
            }
        }
    }
return SentenceCount;
}
int CountWords(string s)
{
    char Buffer = ' ';
    int WordCount = 1;
    for (int x = 0, Length = strlen(s); x <= Length; x++)
    {
        if (s[x] == Buffer)
        {
            WordCount++;
        }
    }
return WordCount;
}
int CountLetters(string s)
{
    int LetterCount = 0;
    for (int x = 0, Length = strlen(s); x <= Length; x++)
    {
        if (s[x] >= 97 && s[x] <= 122)
        {
            LetterCount++;
        }
        else if(s[x] >= 65 && s[x] <= 90)
        {
            LetterCount++;
        }
    }
    return LetterCount;
}
string CalculateYearLevel(int SentenceCount, int WordCount, int LetterCount, string s)
{
    int L = LetterCount * 100 / WordCount;
    int S = SentenceCount * 100 / WordCount;
    float YearLevel = 0.0588 * L - 0.296 * S - 15.8 - 0.04;
    if (YearLevel < 1)
    {
        printf("Before Grade 1\n");
        return "Before Grade 1";
    }
    else if (YearLevel >= 16)
    {
        printf("Grade 16+\n");
        return "Grade 16+";
    }
    else
    {
        printf("%f\n", YearLevel);
        int x = round(YearLevel);
        printf("Grade %i\n", x);
    }
    return "Grade";
}
