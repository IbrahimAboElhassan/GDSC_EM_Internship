#ifndef Card_M_H_
#define Card_M_H_

typedef enum EN_CardError_t
{
    Card_Ok,
    Wrong_Name,
    Wrong_Exp_Data,
    Wrong_Pan

}EN_CardError_t;

typedef struct ST_CardData_t
{
    char Card_HolderName[25];
    char PrimaryAccountNumber[20];
    char CardExpirationDate[6];

}ST_CardData_t;

ST_CardData_t *CardData;



// *******************************************
//              APIs
// *******************************************

EN_CardError_t getCardHolderName(ST_CardData_t *CardData);
EN_CardError_t getCardExpirationDate(ST_CardData_t *CardData);
EN_CardError_t getCardPAN(ST_CardData_t *CardData);


#endif // Card_H_
