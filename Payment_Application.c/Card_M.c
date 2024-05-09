#include "Card_M.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern ST_CardData_t *CardData;

/*
This function prompts the user to input the card holder's name and stores it in structure.
It performs validation to ensure that the input meets the specified criteria:
>> the name should be between 20 and 24 characters long and consist only of alphabetic characters.
If the input is invalid,it returns an error code Wrong_Name, otherwise, it returns Card_Ok.
*/

EN_CardError_t getCardHolderName(ST_CardData_t *CardData)
{
    uint8_t Card_HolderName[25] = {0};

    printf("Enter a Card Holder Name: ");
    gets(Card_HolderName);


    uint8_t Num_Characters = strlen(Card_HolderName);


    if(24 < Num_Characters || 20 > Num_Characters || Card_HolderName == NULL )
    {
        return Wrong_Name;
    }else
    {
        strcpy(CardData->Card_HolderName , Card_HolderName);
    }

    return Card_Ok;
}


/*
This function prompts the user to input the card's expiration date in the format "MM/YY" and stores it in structure.
It performs validation to ensure that the input is exactly 5 characters long and formatted correctly.
If the input is invalid, it returns an error code Wrong_Exp_Date, otherwise, it returns Card_Ok.
*/

EN_CardError_t getCardExpirationDate(ST_CardData_t *CardData)
{
    uint8_t cardExpirationDate[10] = {0};

    printf("Enter a Card Expiration Date(MM/YY): ");
    gets(cardExpirationDate);

    int Num_Characters = strlen(cardExpirationDate);

    if(Num_Characters != 5 || cardExpirationDate[2] != '/')
    {
        return Wrong_Exp_Data;
    }
    else
    {
        int expMonth, expYear;
        sscanf(cardExpirationDate, "%d/%d", &expMonth, &expYear);
        if (expMonth > 12)
        {
            return Wrong_Exp_Data;
        }
        strcpy(CardData->CardExpirationDate, cardExpirationDate);
    }

    return Card_Ok;
}



/*
This function prompts the user to input the card's Primary Account Number (PAN) and stores it in structure.
It performs validation to ensure that the input is between 16 and 19 characters long and consists only of numerical characters.
If the input is invalid, it returns an error code Wrong_Pan, otherwise, it returns Card_Ok.
*/

EN_CardError_t getCardPAN(ST_CardData_t *CardData)
{
    uint8_t cardPAN[19] = {0};

    printf("Enter a Primary Account Number of Card: ");
    gets(cardPAN);

    int Num_Characters = strlen(cardPAN);

    if(16 > Num_Characters || 19 < Num_Characters || cardPAN == NULL)
    {
        return Wrong_Pan;
    }else
    {
        strcpy(CardData->PrimaryAccountNumber , cardPAN);
    }

    return Card_Ok;
}


