/*
Name: Luhn's algorithm.
Function: Validating Credit card Numbers
Language: C
Date: May 12, 2018

-- Comment --
All tests passed except for the following input format:  3782-822-463-10005
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// function prototypes
int firstTwoDigits(long long int card_number);
char* determineCardType(long long int card_number);
int getPower(long long int card_number);
char* numberToString(long long int card_number, int power);
int luhnAlgorithm(char* str_card_no, int power);

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


/*
Gets the first two digits of the credit card number.
If the credit card number is less than thirteen digits long, 0 is returned
*/
int firstTwoDigits(long long int card_number) {
    long long int divider;
    long long int dividend;
    
    divider   = pow(10,13);
    dividend  = (card_number - (card_number % divider)) / divider;

    if (dividend > 0 && dividend < 100)
        return dividend;
    else if (dividend >= 100 && dividend < 1000)
        return (dividend - (dividend % 10)) / 10;
    else if (dividend >= 1000 && dividend < 10000)
        return (dividend - (dividend % 100)) / 100;
    else
        return 0;
}

/*
Determines the type of card.
If the card number starts with 4 or is 13 or 16  digits long, it is a Visa Card
If it starts with 34 or 37 it is an American Express card
If it starts with a number between 52 and 55 (inclusive), it is a Naster Card
*/
char* determineCardType(long long int card_number) {
    int first = firstTwoDigits(card_number);

    if (first < 10) {
        if (first == 4)
            return "VISA";
        else
            return "";
    }

    else {
        if (first == 34 || first == 37)
            return "AMEX";
        else if (first >= 51 && first <= 55)
            return "MASTER";
        else if (first >= 40 && first < 49)
            return "VISA";
        else
            return "";

    }
}

/*
Gets the factor of 10 of the total value of the first digit
Example. in 567, 2 is returned. 
500 = pow(10,2)
For a 13 digit number, 12 is returned
*/
int getPower(long long int card_number) {
    int found = 0;
    int power = 15;
    long long int divider, rem;

    while (found == 0) {
        divider = pow(10, power);
        rem = (card_number - (card_number % divider)) / divider;
        if (rem != 0) {
            found = 1;
            break;
        }
        power--;        
    }

    return power;

}

/*
Returns the card number as a string.
This is for easy looping in Luhn's algorithm
*/

char* numberToString(long long int card_number, int power) {
    int length = power + 2;
    char* str = malloc(length);
    snprintf(str, length, "%lli", card_number);
    // free(str);
    return str;
}

/*
Carries out the Luhn's algorithm.
Ref : https://docs.cs50.net/2018/x/psets/1/credit/credit.html
------------------
1.  Multiply every other digit by 2,
    starting with the number’s second-to-last digit, 
    and then add those products' digits together.

2. Add the sum to the sum of the digits that weren’t multiplied by 2.

------------------

The answer of step one is stored in step_one_answer
The answer of step two is stored in step_two_answer
The function returns the sum of the two, which is tested in the main function
*/
int luhnAlgorithm(char* str_card_no, int power) {
    int length = power + 1;
    int product = 0;
    int step_one_answer = 0;
    int step_two_answer = 0;
    int c;
    for (int i = 0; i < length; i++) {
        c = str_card_no[i] - '0';
        
        if (i % 2 == 1) {
            product = c * 2;        
            if (product < 0) {
                step_one_answer += product;
            }
            else {
                int ones = product % 10;
                int tens = (product - ones) / 10;
                step_one_answer += (tens + ones);
            }
        }
        else {
            step_two_answer += c;
        }
    }
    return step_one_answer + step_two_answer;
}