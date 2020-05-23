#include <stdio.h>
#include "boolib.h"
#include "valib.h"

void getIntCheck(int* intNum,char* mesage,int* options, int optionsLen)
{
    int rightEntry, trys = 5, numb;
    printf(mesage);
    rightEntry=scanf("%d",&numb);
    fflush(stdin);
    while( (not(rightEntry) || validarInt(numb, options, optionsLen)) && trys > 0 )
    {
        printf("\nIntentos restantes: %d",trys);
        if (not(rightEntry))
        {
            printf("\nError, lo ingresado no es un numero");
            printf(mesage);
            rightEntry=scanf("%d",&numb);
            fflush(stdin);
        }
        if (validarInt(numb, options, optionsLen))
        {
            printf("\nError, lo ingresado no corresponde con ninguna de las opciones esperadas");
            printf(mesage);
            rightEntry=scanf("%d",&numb);
            fflush(stdin);
        }
        trys--;
    }
    if (trys == 0)
    {
        numb=-1;
    }
    *intNum=numb;
}

void getInt(int* intNum,char mesage[])
{
    int rightEntry;
    int numb;
    printf(mesage);
    rightEntry=scanf("%d",&numb);
    fflush(stdin);
    while(not(rightEntry))
    {
        printf("\nError, lo ingresado no es un numero");
        printf(mesage);
        rightEntry=scanf("%d",&numb);
        fflush(stdin);
    }
    *intNum=numb;
}

void getFloat(float* floatNum,char mesage[])
{
    int rightEntry;
    float floatPoint;
    printf(mesage);
    rightEntry=scanf("%f",&floatPoint);
    fflush(stdin);
    while(not(rightEntry))
    {
        printf("Lo ingresado no es un decimal.\n");
        printf(mesage);
        rightEntry=scanf("%f",&floatPoint);
        fflush(stdin);
    }
    *floatNum=floatPoint;
}

void getChar(char* character,char mesage[],char error[], char options[])
{
    int rightEntry;
    char characterI;
    printf(mesage);
    rightEntry=scanf("%c",&characterI);
    fflush(stdin);
    while(not(rightEntry)||validarChar(characterI,options))
    {
        printf(error);
        printf(mesage);
        rightEntry=scanf("%c",&characterI);
        fflush(stdin);
    }
    *character=characterI;
}

void myFgets(char* to, int len)
{
    char auxString[len];
    fgets(auxString,len,stdin);
    for ( int i = 0 ; i < len ; i++)
    {
        if ( auxString[i] != '\n')
        {
            to[i]=auxString[i];
        }
    }
}

void getFloatCheck(float* floatNum,char* mesage,float* options, int optionsLen)
{
    int rightEntry;
    float numb;
    printf(mesage);
    rightEntry=scanf("%f",&numb);
    fflush(stdin);
    while( not(rightEntry) || validarFloat(numb, options, optionsLen) )
    {
        if (not(rightEntry))
        {
            printf("\nError, lo ingresado no es un numero decimal");
            printf(mesage);
            rightEntry=scanf("%f",&numb);
            fflush(stdin);
        }
        else
        {
            printf("\nError, lo ingresado no corresponde con ninguna de las opciones esperadas");
            printf(mesage);
            rightEntry=scanf("%f",&numb);
            fflush(stdin);
        }
    }
    *floatNum=numb;
}
