#include <cs50.h>
#include <stdio.h>
#include <math.h>

long CardNumber = 20968348907823;

// Function Deffinitions
long PersonalFindXDigit(long _CardNumber, int NumberFind);
long OtherFindXDigit(long _CardNumber, int NumberFind);
int IdentifyLengthOfLong(long _CardNumber);
bool VerifyCardNumber(long _CardNumber);
void DetermineCardOwner(long _CardNumber);
bool VisaCheck(long _CardNumber, int CardLength);
bool MasterCardCeck(long _CardNumber, int CardLength);
bool AMEXCheck(long _CardNumber, int CardLength);
// Program Start Point
int main(void)
{
    CardNumber = get_long("What is the card number you need verified? ");
    if(VerifyCardNumber(CardNumber) == true){
        DetermineCardOwner(CardNumber);
    } else {
        printf("INVALID\n");
    }

}
bool VerifyCardNumber(long _CardNumber){

    int LengthOfCN = IdentifyLengthOfLong(_CardNumber); // Finds length of card number using the function below.
    int FormulaPart1 = 0;
    int LastTestedNumber = 0;

    while(LastTestedNumber + 2 <= LengthOfCN){ // This is the key part of the calculation, this is the first part of Luhn's algorithm, research on this law can be found here: https://cs50.stackexchange.com/questions/28830/luhn-algorithm-error-pset1 or https://cs50.harvard.edu/x/2022/psets/1/credit/#luhns-algorithm 
        LastTestedNumber += 2;
        if(OtherFindXDigit(_CardNumber, LastTestedNumber) * 2 >= 10){
            int temp = OtherFindXDigit(_CardNumber, LastTestedNumber) * 2;
            FormulaPart1 += temp % 10;
            FormulaPart1 += OtherFindXDigit(temp, 2);
        } else {
            FormulaPart1 += OtherFindXDigit(_CardNumber, LastTestedNumber) * 2;
            //printf("%li", OtherFindXDigit(_CardNumber, LastTestedNumber) * 2);
        }
    }
    //printf("\nPart1 Total = %i\n", FormulaPart1);

    int LastTestedNumberP2 = -1;
    int FormulaPart2 = 0;

    while(LastTestedNumberP2 + 2 <= LengthOfCN){
        LastTestedNumberP2 = LastTestedNumberP2 + 2;
        FormulaPart2 += OtherFindXDigit(_CardNumber, LastTestedNumberP2);
    }
    //printf("Result: %i\n", FormulaPart2 + FormulaPart1);
    if((FormulaPart2 + FormulaPart1) % 10 == 0)
        return true;
    else
        return false;
}
int IdentifyLengthOfLong(long _CardNumber){ // Calculates the length of the supplied number, this is done by dividing the number ans keeping track of the number of divisions and stops when the value is less than ten. Boom length is calculated.
    int Length = 1;
    while(_CardNumber / 10 >= 1){
        Length++;
        _CardNumber = _CardNumber / 10;
    }
    return Length;
}
long PersonalFindXDigit(long _CardNumber, int NumberFind) // I would comment this code but even I do not understand this monstrosity.
{
        long x = floor(_CardNumber / pow(10, NumberFind));
        x = x * pow(10, NumberFind);
        x = _CardNumber - x;
        x = floor(x / pow(10, NumberFind - 1));
        return x;
}
long OtherFindXDigit(long _CardNumber, int NumberFind) // This is my code which I took inspiration from out of stack overflow, https://stackoverflow.com/questions/3389264/how-to-get-the-separate-digits-of-an-int-number
{
    for (int x = 1; x < NumberFind; x++) // this code loops through your card number deducting 10 from it each time.
    {
        _CardNumber = floor(_CardNumber / 10);
    } // Deaper explanation, imagine you hacve the number 1254 and want to single out the second digit(5), the code written in the loop takes 1254 and divides it by 10 and then floors that number, this leads to 125 and then if you modulus this by 10(125 % 10 = 5), boom, answer. modulus is like division, although where it differs is it provides the remainder not the answer.
    return _CardNumber % 10; // This code takes the cut down version of the previous line and singles out the correct digit.
}

void DetermineCardOwner(long _CardNumber){ // This function leads to others that find out weather the provided card number's details lead to that provider.
    long CardLength = IdentifyLengthOfLong(_CardNumber); // Determines card length so that this function does not need to be repeated, leading to lower efficiency.

    if(AMEXCheck(_CardNumber, CardLength) == true)
    {
        printf("AMEX\n");
        return;
    }
    if(VisaCheck(_CardNumber, CardLength) == true)
    {
        printf("VISA\n");
        return;
    }
    if(MasterCardCeck(_CardNumber, CardLength) == true){
        printf("MASTERCARD\n");
        return;
    }
        printf("INVALID\n");
}
bool AMEXCheck(long _CardNumber, int CardLength){
 int FirstTwoDigits = OtherFindXDigit(_CardNumber, CardLength) * 10; // This returns the last number in the card and creates a new variable the last number is the tens so is multiplied by ten.
     FirstTwoDigits += OtherFindXDigit(_CardNumber, CardLength - 1); // This returns the second last number in the card, being the ones, this is done using the same method as above.
 if(CardLength == 15)
 {
    if(FirstTwoDigits == 34 || FirstTwoDigits == 37)
    {
        return true;
    }
 }
 printf("%i\n", FirstTwoDigits);
 return false;
}
bool MasterCardCeck(long _CardNumber, int CardLength){ // This function is the same as the AMEX with slight changes for the card supplier.
    int FirstTwoDigits = OtherFindXDigit(_CardNumber, CardLength) * 10;
        FirstTwoDigits += OtherFindXDigit(_CardNumber, CardLength - 1);
    if(CardLength == 16)
    {
        if(FirstTwoDigits >= 51 && FirstTwoDigits <= 55)
        {
            return true;
        }
    }
}
bool VisaCheck(long _CardNumber, int CardLength){
    int FirstDigit = OtherFindXDigit(_CardNumber, CardLength);

    if(CardLength == 13 || CardLength == 16)
    {
        if(FirstDigit == 4)
        {
            return true;
        }
    }
    return false;
}
