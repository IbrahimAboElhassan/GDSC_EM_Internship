
#ifndef SERVER_M_H_
#define SERVER_M_H_

#include "Card_M.h"
#include "Terminal_M.h"

#include <stdint.h>

#define mAXACCOUNTS_DB     255
#define mAXTRANSACTION_DB  255


typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFEIENT_FUND,
    DECLINED_STOLEN_CARD,
    FRAUD_CARD,
    INTERNAL_SERVER_ERROR,

}EN_transState_t;


typedef struct ST_transaction_t
{
    ST_CardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;

}ST_transaction_t;


typedef enum EN_serverError_t
{
    SERVER_OK,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE,
    BLOCKED_ACCOUNT,

}EN_serverError_t;


typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;


typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];

}ST_accountsDB_t;



// *******************************************
//              APIs
// *******************************************

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_CardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);


#endif // SERVER_M_H_
