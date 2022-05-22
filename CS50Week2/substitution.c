// Library deffintions
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Function declarations
bool CheckCLAValidity(string Cipher); // This function will ensure that the CLA does not repeat characters and all characters are valid letters
string CipherText(string PlainText, string Key); // This will return a string that is encrypted based upon the plain text input and key
string DeCapitalize(string PlainText); // This will deCapitalize a given string
// Program start point
int main(int argc, string argv[])
{
    // Check for command line argument validity
    if(argc != 2) // Check for correct number of command line arguments
    {
        printf("Usage: ./substitution key\n");
        return 1; // return an error if incorrect number of command line arguments are given
    }

    if(strlen(argv[1]) != 26) // Ensure 26 characters where recieved
    {
        printf("Key must contain 26 characters.\n");
        return 1; // return an error if incorrect characters are given
    }

    if(CheckCLAValidity(argv[1]) == false) // This will return an error if CheckCLAValidity returns false
    {
        printf("Only alphabetical letters may be entered and each letter shall not repeat.\n");
        return 1;
    }

    // User input
    string PlainText = get_string("PlainText: "); // Get user input for plain text
    printf("ciphertext: %s\n", CipherText(PlainText, argv[1])); // This will put the plain text and key into a function that returns the encrypted code this output will then be printed
}

bool CheckCLAValidity(string Cipher) // Validate entered Cipher
{
     for (int x = 0, length = strlen(Cipher); x < length; x++) // Check for non alphabetical numbers
     {
         if (Cipher[x] >= 97 && Cipher[x] <= 122)
         {
         }
         else if (Cipher[x] >= 65 && Cipher[x] <= 90)
         {
             Cipher[x] = Cipher[x] + 32; // make lower case
         }
         else
         {
             return false;
         }
     }

    for (int x = 0, length = strlen(Cipher); x < length; x++) // make sure each letter does not repeat
    {
        for (int i = 0; i < x; i++)
        {
            if(i != x)
            {
                if(Cipher[i] == Cipher[x])
                {
                    return false; // return an error
                }
            }
        }
    }

     return true;
}

string CipherText(string PlainText, string Key) // Encrypt given text with key
{
    DeCapitalize(Key);

    string EncryptedString = PlainText; // This will be the returned value
    bool TextCapitaliaztion[strlen(PlainText)];
    for (int x = 0, length = sizeof(TextCapitaliaztion)/sizeof(TextCapitaliaztion[0]); x < length; x++) // set all TextCapitaliaztion elements to false. Read array bit size and divide by value type
    {
        TextCapitaliaztion[x] = false;
    }

    for (int x = 0, Length = strlen(PlainText); x < Length; x++) // for each plain text letter if capitalized set to lower case, then record this in the bool array
    {
        if (EncryptedString[x] >= 65 && EncryptedString[x] <= 90)
        {
            TextCapitaliaztion[x] = true; // record capitalization
            EncryptedString[x] = EncryptedString[x] + 32; // make capitalized
        }
    }


    for (int x = 0, Length = strlen(PlainText); x < Length; x++)
    {
        if (EncryptedString[x] >= 97 &&  EncryptedString[x] <= 122) // if plain text is a letter remap it from 0 - 25 then set the value to the corrosponding key
        {
            int temp = EncryptedString[x] - 97; // remap 0 - 25
            EncryptedString[x] = Key[temp]; // set char to remaped key value
        }
    }


    for (int x = 0, Length = strlen(PlainText); x < Length; x++) // make capitalized from recorded bool array
    {
        if(TextCapitaliaztion[x] == true)
        {
            EncryptedString[x] = EncryptedString[x] - 32; // make letter capitalized by messing with aski decimal value
        }
    }


    return EncryptedString;
}

string DeCapitalize(string PlainText){ // For every element in this loop if it is capitalized make it uncapitalized, this assumes every character is alphabetical, though does not rely on this fact
    for (int x = 0, length = strlen(PlainText); x < length; x++){
        if(PlainText[x] >= 65 && PlainText[x] <= 90)
        {
            PlainText[x] = PlainText[x] + 32; // make letter capitalized by messing with aski decimal value
        }
    }
    return PlainText;
}
