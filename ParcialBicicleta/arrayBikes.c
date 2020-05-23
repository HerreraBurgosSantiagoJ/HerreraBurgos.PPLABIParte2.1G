#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "utn.h"

typedef struct{
    int id;
    char name[20];
    char sex;
}cClient;

typedef struct{
    int id;
    char tradeMark[20];
    int idType;
    int idColor;
    float wheelSize;
    int idClient;
    int isEmpty;
}bBike;

typedef struct{
    int id;
    char description[20];
}tType;

typedef struct{
    int id;
    char colorName[20];
}cColor;

typedef struct{
    int id;
    char description[25];
    float price;
}sService;

typedef struct{
    int day;
    int month;
    int year;
}dDate;

typedef struct{
    int id;
    int idBike;
    int idService;
    dDate date;
    int isEmpty;
}wWork;

/*cliente: con campo id, nombre, sexo.*/


void myStrcpy(char to[],char from[])
{
    int i = 0;
    while ( from[i] != '\0')
    {
        to[i]=from[i];
        i++;
    }
}

void bikeSwap(bBike bikeA, bBike bikeB )
{
    bBike auxbike;
    auxbike = bikeA;
    bikeA = bikeB;
    bikeB = auxbike;
}

int initBikes(bBike* list, int len)
{
    int isError = -1;
    if ( len > 0 && list != NULL )
    {
        for (int i = 0 ; i < len ; i++)
        {
            list[i].isEmpty = 1;
        }
        isError=0;
    }
    return isError;
}

int initWorks(wWork* list, int len)
{
    int isError = -1;
    if ( len > 0 && list != NULL )
    {
        for (int i = 0 ; i < len ; i++)
        {
            list[i].isEmpty = 1;
        }
        isError=0;
    }
    return isError;
}

int addBike(bBike* list, int len, int id, char tradeMark[],int idType,int idColor, int wheelSize, int idClient, char* name, char sex, cClient* clients)
{
    int i,isError = -1;
    if( len > 0 && list != NULL )
    {
        for( i = 0 ; i < len ; i++ )
        {
            if(list[i].isEmpty == 1)
            {
                list[i].id=id;
                myStrcpy(list[i].tradeMark, tradeMark);
                list[i].idType=idType;
                list[i].idColor=idColor;
                list[i].wheelSize=wheelSize;
                list[i].isEmpty=0;
                clients[i].id=idClient;
                myStrcpy(clients[i].name, name);
                clients[i].sex = sex;
                isError=0;
                break;
            }
        }
    }
    return isError;
}

int findBikeById(bBike* list, int len,int id)
{
    int i, ifIndex = -1;
    if ( len > 0 && list != NULL)
    {
        for ( i = 0 ; i < len ; i++ )
        {
            if ( list[i].id == id && list[i].isEmpty == 0 )
            {
                ifIndex = i;
                break;
            }
        }
    }
    return ifIndex;
}

int findClientById(cClient* list, int len,int id)
{
    int i, ifIndex = -1;
    if ( len > 0 && list != NULL)
    {
        for ( i = 0 ; i < len ; i++ )
        {
                ifIndex = i;
                break;
        }
    }
    return ifIndex;
}

int removeBike(bBike* list, int len, int id)
{
    int i, isError = -1;
    if ( len > 0 && list != NULL )
    {
        for ( i = 0 ; i < len ; i++ )
        {
            if ( list[i].id == id )
            {
                list[i].isEmpty = 1;
                isError = 0;
                break;
            }
        }
    }
    return isError;
}


int sortBikes(bBike* list, int len, int order)
{
    int isError = -1;
    if ( len > 0 && list != NULL )
    {
        for ( int i = 0 ; i < len ; i++ )
        {
            for ( int j = i + 1 ; j < len ; j++ )
            {
                if ( order )
                {
                    if (list[i].idType > list[j].idType)
                    {
                        bikeSwap(list[i],list[j]);
                    }
                    if ( list[i].wheelSize > list[j].wheelSize )
                    {
                        bikeSwap(list[i],list[j]);
                    }
                }
                else
                {
                    if ( list[i].idType < list[j].idType )
                    {
                        bikeSwap(list[i],list[j]);
                    }
                    if ( list[i].wheelSize < list[j].wheelSize )
                    {
                        bikeSwap(list[i],list[j]);
                    }
                }
            }
        }
        isError = 0;
    }
    return isError;
}

int generateID(bBike* list, int len)
{
    int newID = 0;
    for ( int i = 0 ; i < len ; i++ )
    {
        if ( list[i].id > newID && list[i].isEmpty == 0 )
        {
            newID = list[i].id;
        }
    }
    newID++;
    return newID;
}

int generateWorkID(wWork* list, int len)
{
    int newID = 0;
    for ( int i = 0 ; i < len ; i++ )
    {
        if ( list[i].id > newID && list[i].isEmpty == 0 )
        {
            newID = list[i].id;
        }
    }
    newID++;
    return newID;
}

int bikeHasSpace(bBike* list, int len)
{
    char boolean = 0 ;
    for ( int i = 0 ; i < len ; i++ )
    {
        if ( list[i].isEmpty == 1)
        {
            boolean = 1;
            break;
        }
    }
    return boolean;
}

int getIdIndex(bBike* list, int len)
{
    int id,indexOrEr,trys = 5;
    getInt(&id,"\nIngrese el ID de la bicicleta: ");
    indexOrEr = findBikeById(list,len,id);
    if (indexOrEr == -1)
    {
        while ( id != -1 && trys > 0 )
        {
            printf("\nEl ID ingresado no corresponde con un ID en el sistema, para cancelar la busqueda ingrese \"-1\"");
            printf("\n Intentos restantes: %d",trys);
            getInt(&id,"\nIngrese el ID dela bicicleta: ");
            indexOrEr = findBikeById(list,len,id);
            trys--;
        }
    }
    return indexOrEr;
}

int addWork(wWork* list, int len, int id, int idBike, int idService, dDate date)
{
    int i,isError = -1;
    if( len > 0 && list != NULL )
    {
        for( i = 0 ; i < len ; i++ )
        {
            if (list[i].isEmpty==1)
            {
                list[i].id=id;
                list[i].idBike=idBike;
                list[i].idService=idService;
                list[i].date=date;
                list[i].isEmpty=0;
                isError=0;
                break;
            }
        }
    }
    return isError;
}

int findTypeById(tType* list, int len,int id)
{
    int i, ifIndex = -1;
    if ( len > 0 && list != NULL)
    {
        for ( i = 0 ; i < len ; i++ )
        {
            if ( list[i].id == id )
            {
                ifIndex = i;
                break;
            }
        }
    }
    return ifIndex;
}

int findColorById(cColor* list, int len,int id)
{
    int i, ifIndex = -1;
    if ( len > 0 && list != NULL)
    {
        for ( i = 0 ; i < len ; i++ )
        {
            if ( list[i].id == id )
            {
                ifIndex = i;
                break;
            }
        }
    }
    return ifIndex;
}

int findServiceById(sService* list, int len,int id)
{
    int i, ifIndex = -1;
    if ( len > 0 && list != NULL )
    {
        for ( i = 0 ; i < len ; i++ )
        {
            if ( list[i].id == id )
            {
                ifIndex = i;
                break;
            }
        }
    }
    return ifIndex;
}

int printWorks(wWork* list, int length, bBike* bikes, int bikesLen, tType* types, int typesLen, sService* services, int servicesLen)
{
    int i, isError = -1, cDay, cMonth, cYear, cBikeIndex, cTypeIndex, cServiceIndex, noWork=1; //"c" from Current
    printf("\n     ID        Tipo de Bicicleta        Servicio      Precio     Fecha\n");
    printf("-------------------------------------------------------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        if (list[i].isEmpty == 0)
        {
            cBikeIndex = findBikeById(bikes,bikesLen,list[i].idBike);
            cTypeIndex = findTypeById(types,typesLen,bikes[cBikeIndex].idType);
            cServiceIndex = findServiceById(services,servicesLen,list[i].idService);
            cDay = list[i].date.day;
            cMonth = list[i].date.month;
            cYear = list[i].date.year;
            printf("%07d|%19s|%19s|%.2f|%02d/%02d/%04d\n", list[i].id, types[cTypeIndex].description, services[cServiceIndex].description, services[cServiceIndex].price, cDay, cMonth, cYear);
            printf("-------------------------------------------------------------------------------\n");
            isError = 0;
            noWork=0;
        }
    }
    if(noWork)
    {
        printf("No hay trabajos en la base de datos");
    }
    return isError;
}

void fillBikePosibilities(bBike* list, int len, int* array, int* newLen)
{
    int lenMes = 0;
    for (int i = 0; i<len; i++)
    {
        if ( list[i].isEmpty == 0 )
        {
            array[lenMes] = list[i].id;
            lenMes++;
        }
    }
    *newLen = lenMes;
}

void fillColorsPosibilities(cColor* list, int len, int* array)
{
    for (int i = 0; i<len; i++)
    {
        array[i] = list[i].id;
    }
}

void fillTypesPosibilities(tType* list, int len, int* array)
{
    for (int i = 0; i<len; i++)
    {
        array[i] = list[i].id;
    }
}

void fillServicesPosibilities(sService* list, int len, int* array)
{
    for (int i = 0; i<len; i++)
    {
        array[i] = list[i].id;
    }
}

int printTypes(tType* list, int length)
{
    int i, isError = -1;
    printf("\n     ID           Tipo\n");
    printf("----------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        printf("%07d|%19s\n", list[i].id, list[i].description);
        printf("----------------------------------\n");
        isError = 0;
    }
    return isError;
}

int printColors(cColor* list, int length)
{
    int i, isError = -1;
    printf("\n     ID           Color\n");
    printf("----------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        printf("%07d|%19s\n", list[i].id, list[i].colorName);
        printf("----------------------------------\n");
        isError = 0;
    }
    return isError;
}

int printServices(sService* list, int length)
{
    int i, isError = -1;
    printf("\n     ID          Service          Precio\n");
    printf("------------------------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        printf("%07d|%19s|%.2f\n", list[i].id, list[i].description, list[i].price);
        printf("------------------------------------------------\n");
        isError = 0;
    }
    return isError;
}

int printBikes(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int i, isError = -1, typeIndex, colorIndex, clientIndex,noBikes = 1;
    printf("\n     ID      Cliente       Marca          Tipo           Color            Rodado\n");
    printf("----------------------------------------------------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        if ( list[i].isEmpty == 0 )
        {
            typeIndex = findTypeById(types,typesLen,list[i].idType);
            colorIndex = findColorById(colors,colorsLen,list[i].idColor);
            clientIndex = findClientById(clients,clientsLen, list[i].idClient);
            printf("%07d|%19s|%19s|%19s|%19s|%.1f\n", list[i].id, clients[clientIndex].name, list[i].tradeMark,types[typeIndex].description, colors[colorIndex].colorName, list[i].wheelSize);
            printf("----------------------------------------------------------------------------\n");
            noBikes=0;
        }
        isError = 0;
    }
    if(noBikes)
    {
        printf("No hay bicicletas en la base de datos");
    }
    return isError;
}
