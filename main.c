/*
Name: Luhn's algorithm.
Function: Validating Credit card Numbers
Language: C
Date: May 12, 2018

-- Comment --
All tests passed except for the following input format:  3782-822-463-10005
*/

#include <stdio.h>
#include "luhn.h"

int main() {
    char* card_type;
    char* str_card_no;
    int power;
    int luhn;
    long long int card_number;
    int valid = 0;

    printf("Number: ");
    scanf("%lli", &card_number);

    if (card_number < pow(10,12)) {
        printf ("INVALID");
        return 0;
    }
    
    while (1) {
         // determine the type of the card
        card_type = determineCardType(card_number);
        // get the power of 10 of the first digit of the card number
        power = getPower(card_number);
        // convert the card number into a string
        str_card_no =  numberToString(card_number, power);
        // get the result of the Luhn's algorithm
        luhn = luhnAlgorithm(str_card_no, power);
        // Determine whether the card is valid/invalid from Luhn's algorithm
        if (luhn % 10 == 0) {
            printf("%s\n", card_type);
            break;
        }

        printf("Number: ");
        scanf("%lli", &card_number);

        if (card_number < pow(10,12)) {
            printf ("INVALID");
            return 0;
        }
    }
   
   
    return 0;
}
