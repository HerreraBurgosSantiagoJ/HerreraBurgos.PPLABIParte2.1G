#include <string.h>
#include <ctype.h>

int validarChar(char ingreso,char opciones[])
{
    int i=0;
    int booleano=1;
    if(ingreso<141)
    {
        ingreso=tolower(ingreso);
    }
    while(opciones[i]!='\0')
    {
        if (ingreso==opciones[i])
        {
            booleano=0;
        }
        i++;
    }
    return booleano;
}

int validarInt(int ingreso, int opciones[], int len)
{
    int booleano=1;
    for (int i = 0 ; i < len ; i++)
    {
        if (ingreso==opciones[i])
        {
            booleano=0;
        }
    }
    return booleano;
}

int validarFloat(float ingreso, float opciones[], int len)
{
    int booleano=1;
    for (int i = 0 ; i < len ; i++)
    {
        if (ingreso==opciones[i])
        {
            booleano=0;
        }
    }
    return booleano;
}
