#include <stdio.h>
#include <stdlib.h>
#include "mesure.h"

void progHeader(char title[])
{
    int largo=lengthArrayC(title);
    int largoRenglon=largo*3;
    int i;
    system("cls");
    for (i = 0; i<largoRenglon;i++)
    {
        printf("=");
    }
    printf("\n");
    for (i = 0; i<largo;i++)
    {
        printf(" ");
    }
    printf("%s",title);
    for (i = 0; i<largo;i++)
    {
        printf(" ");
    }
    printf("\n");
    for (i = 0; i<largoRenglon;i++)
    {
        printf("=");
    }
}

void subHeader(char sub[])
{
    int largo=lengthArrayC(sub);
    printf("\n%s\n",sub);
    for (int i = 0; i<largo;i++)
    {
        printf("-");
    }
    printf("\n");
}
