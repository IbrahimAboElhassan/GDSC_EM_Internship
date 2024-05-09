
#include "Terminal_M.h"
#include "Card_M.h"
#include "Server_M.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern ST_terminalData_t *termData;
extern ST_transaction_t *transData;

// This function will ask for the transaction data and store it in terminal data.
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t cardTransactionDate[10] = {0};

    printf("Enter a transaction date (DD/MM/YYYY): ");
    gets(cardTransactionDate);

    int Num_characters = strlen(cardTransactionDate);

    if (Num_characters != 10 || cardTransactionDate[2] != '/' || cardTransactionDate[5] != '/' || cardTransactionDate == NULL)
    {
        return WRONG_DATE;
    }
    else
    {
        int transMonth, transYear,transDay;
        sscanf(cardTransactionDate, "%d/%d/%d",&transDay, &transMonth, &transYear);
        if (transMonth > 12 || transDay > 30)
        {
            return WRONG_DATE;
        }
        strcpy(termData->transactionDate , cardTransactionDate);
    }

    return TERMINAL_OK;
}


// This function compares the card expiry date with the transaction date.
EN_terminalError_t isCardExpired(ST_CardData_t CardData, ST_terminalData_t termData)
{
    int transMonth, transYear, expMonth, expYear;

    sscanf(termData.transactionDate, "%*d/%d/%d",&transMonth, &transYear);

    sscanf(CardData.CardExpirationDate, "%d/%d", &expMonth, &expYear);

    int transYearLastTwoDigits = transYear % 100;

    if (transYearLastTwoDigits > expYear) {
        return EXPIRED_CARD;
    }

    if (transYearLastTwoDigits == expYear)
    {
        if (transMonth > expMonth)
        {
            return EXPIRED_CARD;
        }
    }

    return TERMINAL_OK;
}



EN_terminalError_t isValidCardPAN(ST_CardData_t *cardData)
{
    return TERMINAL_OK;
}

// This function will ask for the transaction amount and save it in terminal data.
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    float transAmount = 0.0;

    printf("Enter Your amount transaction:$");
    scanf("%f", &transAmount);

    if(0.0 >= transAmount)
    {
        return INVALID_AMOUNT;
    }else
    {
        termData->transAmount = transAmount;
    }

    return TERMINAL_OK;
}


// This function compares the transaction amount with MAX transaction amount.
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
   if(termData->transAmount > termData->maxTransAmount)
   {
       return EXCEED_MAX_AMOUNT;
   }

    return TERMINAL_OK;
}

// This function sets the maximum allowed amount into terminal data.
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    float Max_Amount = 0.0;

    printf("Enter transaction max amount:$");
    if (scanf("%f", &Max_Amount) != 1)
    {
        while (getchar() != '\n'); // Clear input buffer
        return INVALID_MAX_AMOUNT;
    }

    if (Max_Amount <= 0.0)
    {
        while (getchar() != '\n');
        return INVALID_MAX_AMOUNT;
    } else
    {
        termData->maxTransAmount = Max_Amount;
    }

    return TERMINAL_OK;
}


































