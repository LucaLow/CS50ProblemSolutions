// Library definitions
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Function declarations
int CalculateCipherKey(string Num);
string CipherCode(string PlainText, int Key);
// Program start point
int main(int argc, string argv[])
{
    int CipherKey;

    if(argc != 2) // Checks that the key was entered as a command line argument
    {
        return 1; // Returns an error if incorrect number of command line arguments where entered, this does not check for numerical validity
    }

    for(int x = 0, length = strlen(argv[1]); x < length; x++) // This loop check the validity of the numbers entered as command line arguments
    {
        if(x != 0){
            if(argv[1][x] < 48 || argv[1][x] > 57) // Checks if the numbers entered are outside of ASKI number bounds
            {
                printf("Usage: ./caesar key\n"); // prints propper usage reminder if incorrectly entered
                return 1;  // Returns an error
            }
        }
        else
        {
            if(argv[1][x] != 45)
            {
                if(argv[1][x] < 48 || argv[1][x] > 57) // Checks if the numbers entered are outside of ASKI number bounds
                {
                    printf("Usage: ./caesar key\n"); // prints propper usage reminder if incorrectly entered
                    return 1;  // Returns an error
                }
            }
        }
    }

    CipherKey = CalculateCipherKey(argv[1]); // Calculate Cipher Key from command line arguments
    printf("Key: %i\n", CipherKey); // Print Cipher Key

    string PlainText;
    PlainText = get_string("What would you like to be encrypted? "); // Get user input for encryption
    //printf("PlainText: %s\n", PlainText); // Print plain text before encryption

    printf("ciphertext: "); // Print Cipher After Encryption
    printf("%s\n", CipherCode(PlainText, CipherKey));
}


int CalculateCipherKey(string Num){
    bool Negative = false;
    int CipherKey = 0; // This will end up being the return int.
    for(int x = 0, length = strlen(Num); x < length; x++) // Loop through each char in input
    {

        if(x != 0)
        {
            CipherKey *= 10; // make 0 the character in the ones place
            CipherKey += (Num[x] % 48);  // make x the character in the ones place
        }
        else
        {
            if(Num[x] != 45)
            {
                CipherKey += Num[x] % 48;
            }
            else
            {
                Negative = true;
            }
        }
    }

    if(Negative == true)
    {
        CipherKey *= -1; // If number is found to be negative, * -1
    }
    return CipherKey;
}


string CipherCode(string _PlainText, int Key)
{

    bool IsCap[strlen(_PlainText)];
    for (int x = 0, Length = strlen(_PlainText); x < Length; x++) // Loops through all string elements and checks if capitalized against aski chart.
    {
        if(_PlainText[x] >= 65 && _PlainText[x] <= 90)
        {
            IsCap[x] = true; // sets value of is capitalized array.
            _PlainText[x] += 32; // makes value lower case
        }
        else
        {
            IsCap[x] = false;
        }
    }


    for (int x = 0, Length = strlen(_PlainText); x < Length; x++)
    {
        if(_PlainText[x] >= 97 && _PlainText[x] <= 122)
        {
            _PlainText[x] += Key;
            while(_PlainText[x] < 97) // as per the specifications from CS50 I loop through each character as an int untill it is within ASKI requirments.
            {
                _PlainText[x] = _PlainText[x] - 26; // For some fucking reason -= and the current equation return 2 different outputs. This would have been helpful to know 3 hours ago
            }
            while(_PlainText[x] > 122)
            {
                _PlainText[x] = _PlainText[x] - 26; // Perform an operation on the character to keep it within ASKI alphabetical constraints, this means whatever the key this program will return the desired result
            }
        }
    }


    for (int x = 0, Length = strlen(_PlainText); x < Length; x++) // apply capitalisation to the apropriate characters refferencing before mentioned bool array for capitalisation.
    {
        if(IsCap[x] == true)
        {
            _PlainText[x] -= 32;
        }
    }

    return _PlainText;
}
