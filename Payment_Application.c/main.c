/*


Author  : Ibrahim AboElhassan
Date    : 5/2024
purpose : Transaction processing application 

*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "Card_M.h"
#include "Terminal_M.h"
#include "Server_M.h"
#include "Application.h"


int main()
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
    static uint8_t machine_program_state = 0;

    while (1)
    {
        printf("\n 1. Make new transaction");
        printf("\n 2. Inquire balance");
        printf("\n 3. Exit");
        printf("\n >_  ");
        machine_program_state = getch();

        switch (machine_program_state)
        {
        case '1':
            system("cls");
            fflush(stdin);
            appStart();
            break;
        case '2':
            system("cls");
            inquireBalance(Accounts_dataBase);
            break;
        case '3':
            system("cls");
            return 1;
        default:
            system("cls");
            printf("\n Invalid input.");
            break;
        }
    }

    printf("\n Thanks for using my application.");
    return 0;
}



