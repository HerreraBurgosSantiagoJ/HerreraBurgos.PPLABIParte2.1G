#include <string.h>

int lengthArrayC(char lista[])
{
    return strlen(lista);
}

int lengthArrayI(int lista[])
{
    int length=0;
    int tamanio=sizeof (lista);
    while (tamanio!=0)
    {
        tamanio-=sizeof (lista[length]);
        length++;
    }
    return length;
}
