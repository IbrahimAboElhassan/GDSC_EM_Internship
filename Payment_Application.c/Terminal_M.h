
#ifndef Terminal_M_H
#define Terminal_M_H

#include <stdint.h>
#include "Card_M.h"


typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];

}ST_terminalData_t;


ST_terminalData_t *termData;

typedef enum EN_terminalError_t
{
    TERMINAL_OK,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT,

}EN_terminalError_t;



// *******************************************
//              APIs
// *******************************************

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_CardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_CardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

int Length_String(char str);

#endif // Terminal_M_H
