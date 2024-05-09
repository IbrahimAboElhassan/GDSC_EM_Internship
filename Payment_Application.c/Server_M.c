
#include "Server_M.h"
#include "Card_M.h"
#include "Terminal_M.h"

#include <string.h>

ST_transaction_t Transactions_dataBase[mAXTRANSACTION_DB] = {0};


ST_accountsDB_t Accounts_dataBase[mAXACCOUNTS_DB] =
{
    {5100.5  , RUNNING  , "5078031014041793"},
    {10000.1 , BLOCKED  , "5078013579246801"},
    {62000.2 , RUNNING  , "5078543210987654"},
    {7500.4  , RUNNING  , "5078654345098765"},
    {9150.7  , BLOCKED  , "5078346802468137"},
    {3555.6  , RUNNING  , "5078376514436098"}

};

uint16_t indexOfCurrentAccount = 0;


EN_transState_t receiveTransactionData(ST_transaction_t *transData)
{
    EN_transState_t ErrorState = APPROVED;

    EN_serverError_t accountError = isValidAccount(&(transData->cardHolderData), Accounts_dataBase);
    if (accountError == ACCOUNT_NOT_FOUND) {
        ErrorState = FRAUD_CARD;
    } else if (accountError == BLOCKED_ACCOUNT) {
        ErrorState = DECLINED_STOLEN_CARD;
    }

    if (ErrorState == APPROVED)
    {
        EN_serverError_t amountError = isAmountAvailable(&(transData->terminalData));

        if (amountError == LOW_BALANCE)
        {
            ErrorState = DECLINED_INSUFFEIENT_FUND;
        }
    }

    if (ErrorState == APPROVED)
    {
        EN_serverError_t saveError = saveTransaction(transData);
        if (saveError == SAVING_FAILED)
        {
            ErrorState = INTERNAL_SERVER_ERROR;
        } else
        {
            Accounts_dataBase[indexOfCurrentAccount].balance -= transData->terminalData.transAmount;
        }
    }

    return ErrorState;
}


EN_serverError_t isValidAccount(ST_CardData_t *cardData, ST_accountsDB_t *accountReference)
{
    EN_serverError_t ErrorState = ACCOUNT_NOT_FOUND;

    for (int i = 0; i < mAXACCOUNTS_DB; i++)
    {
        if (strcmp(cardData->PrimaryAccountNumber, accountReference[i].primaryAccountNumber) == 0)
        {
            if (accountReference[i].state == BLOCKED)
            {
                ErrorState = BLOCKED_ACCOUNT;
            } else
            {
                ErrorState = SERVER_OK;
                indexOfCurrentAccount = i;
            }
            break;
        }
    }
    return ErrorState;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    EN_serverError_t ErrorState = SERVER_OK;

    if (termData->transAmount > Accounts_dataBase[indexOfCurrentAccount].balance)
    {
        ErrorState = LOW_BALANCE;
    }
    return ErrorState;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t ErrorState = SERVER_OK;

    uint32_t transactionSequenceNumber = 0;

    if(transactionSequenceNumber >= mAXTRANSACTION_DB)
    {
        ErrorState = SAVING_FAILED;
    }

    transData->transactionSequenceNumber = transactionSequenceNumber;

    Transactions_dataBase[transactionSequenceNumber].cardHolderData = transData->cardHolderData;
    Transactions_dataBase[transactionSequenceNumber].terminalData = transData->terminalData;
    Transactions_dataBase[transactionSequenceNumber].transState = transData->transState;

    transactionSequenceNumber++;


    return ErrorState;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    EN_serverError_t ErrorState = SERVER_OK;

    if(transactionSequenceNumber >= mAXTRANSACTION_DB)
    {
        ErrorState = TRANSACTION_NOT_FOUND;
    }else
    {
        transData->cardHolderData = Transactions_dataBase[transactionSequenceNumber].cardHolderData;
        transData->terminalData = Transactions_dataBase[transactionSequenceNumber].terminalData;
        transData->transState = Transactions_dataBase[transactionSequenceNumber].transState;
        transData->transactionSequenceNumber = transactionSequenceNumber;
    }

    return ErrorState;
}




