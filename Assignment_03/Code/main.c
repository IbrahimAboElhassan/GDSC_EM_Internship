/* ********************************************/
/* Author      : Ibrahim Mohamed
/* Created on  : Mar 8 , 2024
/* Description : EX4: write a program to check whether any digits in a number appears more than once.
/* ********************************************/


#include <stdio.h>

int main()
{

    unsigned int Number, res, counter =0 , arr[50], found=0;

    printf("Enter a Number: ");
    scanf("%d",&Number);

    while(Number!=0)
    {
        res = Number%10;        // To get the last digit in the number.
        arr[counter] = res;     // Put in array for search.
        counter ++;
        Number /= 10;           // Remove the last number.
    }

    for (int i=0; i<counter-1; i++)   // Nested loop, [1st] for to pass through all values, [2nd] to check if it repeated.
    {
        for(int j=i+1; j<counter; j++)
        {
            if (arr[i] == arr[j])
            found = 1;
        }
        if (found)
            break;
    }

    if (found == 1)
        printf("Yes, There are digits appear more than once.\n");
    else
        printf("No, There aren't digits appear more than once .\n");

}

