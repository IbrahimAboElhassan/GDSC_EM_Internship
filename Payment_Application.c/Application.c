
#include <stdio.h>
#include <stdint.h>

#include "Card_M.h"
#include "Terminal_M.h"
#include "Server_M.h"
#include "Application.h"


void appStart(void)
{
  ST_CardData_t cardData;
  ST_terminalData_t termData;
  EN_terminalError_t terminalError;
  EN_serverError_t serverError;
  ST_transaction_t *transData;
  EN_transState_t transError;

ST_accountsDB_t Accounts_dataBase[mAXACCOUNTS_DB] =
{
    {5100.5  , RUNNING  , "5078031014041793"},
    {10000.1 , BLOCKED  , "5078013579246801"},
    {62000.2 , RUNNING  , "5078543210987654"},
    {7500.4  , RUNNING  , "5078654345098765"},
    {9150.7  , BLOCKED  , "5078346802468137"},
    {3555.6  , RUNNING  , "5078376514436098"}

};
    int indexOfCurrentAccount = -1;
    float remainingBalance;
/* *****************************************************************
                  Test Card Validation
    ***************************************************************** */

    terminalError = getCardPAN(&cardData);
    printf("\n");
    if (terminalError != TERMINAL_OK)
    {
        printf("\nError: Invalid Card PAN \n\n");
        return;
    }

    serverError = isValidAccount(&cardData, Accounts_dataBase);
    if (serverError == BLOCKED_ACCOUNT)
    {
        printf("Error!! Your PAN card is blocked.\n\n");
        return;
    } else if (serverError != SERVER_OK )
    {
        printf("Error!! Unable to find PAN card in the database.\n\n");
        return;
    }

     for (int i = 0; i < mAXACCOUNTS_DB; i++)
     {
        if (strcmp(cardData.PrimaryAccountNumber, Accounts_dataBase[i].primaryAccountNumber) == 0)
        {
            indexOfCurrentAccount = i;
            break;
        }
     }

    if (indexOfCurrentAccount == -1)
    {
        printf("\nError!! Unable to find PAN card in the database.\n\n");
        return;
    }

    terminalError = getCardHolderName(&cardData);
    printf("\n");
    if (terminalError != TERMINAL_OK)
    {
        printf("Error!! Invalid Card Holder Name \n\n");
        return;
    }

    terminalError = getCardExpirationDate(&cardData);
    printf("\n");
    if (terminalError != TERMINAL_OK)
    {
        printf("Error!! Invalid Card Expiration Date \n\n");
        return;
    }
/* *****************************************************************
                 Test Terminal Validation
   ***************************************************************** */

    terminalError = getTransactionDate(&termData);
    printf("\n");
    if (terminalError != TERMINAL_OK)
    {
        printf("Error!! Invalid Transaction Date \n\n");
        return;
    }

    terminalError = isCardExpired(cardData, termData);
    if (terminalError == EXPIRED_CARD)
    {
        printf("\nError!! Card is expired.\n\n");
        return;
    }

    terminalError = setMaxAmount(&termData);
    printf("\n");
    if (terminalError != TERMINAL_OK)
    {
        printf("Error!! Invalid Max Transaction Amount \n\n");
        return;
    }

    terminalError = getTransactionAmount(&termData);
    printf("\n");
    if (terminalError != TERMINAL_OK)
    {
        printf("Error!! Invalid Transaction Amount \n\n");
        return;
    }

    for (int i = 0; i < mAXACCOUNTS_DB; i++)
    {
        if (strcmp(cardData.PrimaryAccountNumber, Accounts_dataBase[i].primaryAccountNumber) == 0)
        {
            if(termData.transAmount > Accounts_dataBase[i].balance)
            {
                printf("Error!! NOT Enough balance\n\n");
                return;
            }
        }
    }

    terminalError = isBelowMaxAmount(&termData);

    if (terminalError == EXCEED_MAX_AMOUNT)
    {
        printf("\nError!! Transaction amount exceeds maximum.\n\n");
        return;
    }
/* *****************************************************************
                 Validate card and process transaction
    ***************************************************************** */

    transError = receiveTransactionData(&transData);
    if (transError == DECLINED_STOLEN_CARD) {
        printf("\nError!! Card is stolen.\n\n");
        return;
    } else if (transError == DECLINED_INSUFFEIENT_FUND) {
        printf("\nError!! Insufficient funds.\n\n");
        return;
    } else if (transError == INTERNAL_SERVER_ERROR) {
        printf("\nError!! Internal server error.\n\n");
        return;
    }



    printf("\n      ==> Successfully Transaction  <==      \n\n");

    remainingBalance = Accounts_dataBase[indexOfCurrentAccount].balance - termData.transAmount;
    printf("Transaction done by PAN card : %s \n",Accounts_dataBase[indexOfCurrentAccount].primaryAccountNumber);
    printf("Remaining balance            : $%.2f \n",remainingBalance);
    printf("\n      *** Thanks for using my application ***");
    printf("\n_______________________________________________\n\n");

}


void inquireBalance(ST_accountsDB_t *accountsData)
{
    ST_accountsDB_t Accounts_dataBase[mAXACCOUNTS_DB] =
{
    {5100.5  , RUNNING  , "5078031014041793"},
    {10000.1 , BLOCKED  , "5078013579246801"},
    {62000.2 , RUNNING  , "5078543210987654"},
    {7500.4  , RUNNING  , "5078654345098765"},
    {9150.7  , BLOCKED  , "5078346802468137"},
    {3555.6  , RUNNING  , "5078376514436098"}

};
    char panCard[20];
    printf("Enter your PAN card number: ");
    gets(panCard);

    for (int i = 0; i < mAXACCOUNTS_DB; i++)
     {
        if (strcmp(panCard, Accounts_dataBase[i].primaryAccountNumber) == 0)
        {
            float balance = Accounts_dataBase[i].balance;
            printf("\nYour current balance is: $%.2f\n\n", balance);
            return;
        }
    }
    printf("\nError!! PAN card not found in the database.\n");
}

















