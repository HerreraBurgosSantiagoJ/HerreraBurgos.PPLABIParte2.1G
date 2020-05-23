#include <stdio.h>
#include <stdlib.h>
#include "arrayBikes.h"
#include "utn.h"
#include "steart.h"
#include "valib.h"

#define MAXCOLOR 5
#define MAXTYPE 4
#define MAXSERVICE 4
#define MAXBIKES 500
#define MAXWORKS 500
#define MAXCLIENTS 500

void initHardcoding(tType* typeList, int typeLen, cColor* colorList, int colLen, sService* serviceList, int serLen);
void mainMenuLogic(bBike* list, int len, tType* types, int typesLen,cColor* colors, int colorsLen, sService* services, int servicesLen,wWork* works, int worksLen, cClient* clients, int clientsLen);

int main()
{
    tType types[MAXTYPE];
    cColor colors[MAXCOLOR];
    sService services[MAXSERVICE];
    bBike bikes[MAXBIKES];
    wWork workList[MAXWORKS];
    cClient clients[MAXCLIENTS];
    initBikes(bikes,MAXBIKES);
    initWorks(workList,MAXWORKS);
    initHardcoding(types,MAXTYPE,colors,MAXCOLOR,services,MAXSERVICE);
    mainMenuLogic(bikes,MAXBIKES,types,MAXTYPE,colors,MAXCOLOR,services,MAXSERVICE,workList,MAXWORKS,clients,MAXCLIENTS);
    return 0;
}

void initHardcoding(tType* typeList, int typeLen, cColor* colorList, int colLen, sService* serviceList, int serLen)
{
    int typeMin = 1000, colorMin = 5000, serviMin = 20000, i;
    char types[4][20]={"Rutera","Carrera","Mountain","BMX"}, colors[5][20]={"Gris","Negro","Blanco","Azul","Rojo"},services[4][20]={"Limpieza","Parche","Centrado","Cadena"};
    float servicesPrices[4]={250,300,400,350};

    for (i = 0; i<typeLen ; i++ )
    {
        myStrcpy(typeList[i].description,types[i]);
        typeList[i].id=typeMin+i;
        typeMin++;
    }

    for (i = 0; i<colLen ; i++)
    {
        myStrcpy(colorList[i].colorName,colors[i]);
        colorList[i].id=colorMin+i;
        colorMin++;
    }

    for (i = 0; i<serLen ; i++)
    {
        myStrcpy(serviceList[i].description,services[i]);
        serviceList[i].price=servicesPrices[i];
        serviceList[i].id=serviMin+i;
        serviMin++;
    }
}

void bikeEntree(bBike* list, int len, cClient* clients, int clientsLen)
{
    int id, idType, idColor, posibleTypes[4] = {1000, 1001, 1002, 1003}, idClient;
    int posibleColors[5] = {5000, 5001, 5002, 5003, 5005};
    float wheelSize, posibleWheels[4] = {20, 26, 27.5, 29};
    char tradeMark[20], sex, posibleSex[2] = "mf", name[21];

    progHeader("Administracion de Bicicleteria");
    subHeader("Alta Bicicleta");
    id = generateID(list,len);
    printf("El ID de la bicicleta nueva sera: %d",id);
    printf("\nIngrese la marca de la bicicleta: ");
    myFgets(tradeMark,20);
    getIntCheck(&idType, "\nIngrese el numero de tipo\n(1000) Rutera\n(1001) Carrera\n(1002) Mountain\n(1003) BMX\nTipo ID: ", posibleTypes, 4);
    getIntCheck(&idColor, "\nIngrese el id del color\n(5000) Gris\n(5001) Negro\n(5002) Blanco\n(5003) Azul\n(5004) Rojo\nColor ID: ", posibleColors, 5);
    getFloatCheck(&wheelSize,"\nIngrese el rodado de la bicicleta (20, 26, 27.5, 29): ",posibleWheels, 4);
    printf("\nIngrese el nombre del cliente: ");
    myFgets(name,21);
    getChar(&sex,"\nIngrese el sexo del cliente (m/f): ","\nError, lo ingresado no es un sexo valido",posibleSex);
    printf("Ingrese los ultimos 3 digitos del DNI del cliente: ");
    scanf("%03d",&idClient);
    fflush(stdin);
    addBike(list,len,id,tradeMark,idType,idColor,wheelSize,idClient,name,sex,clients);
}

int findFreeSpace(bBike* list, int len)
{
    int indexOrEr = -1;
    for (int i = 0;i<len;i++)
    {
        if (list[i].isEmpty == 1)
        {
            indexOrEr = i;
            break;
        }
    }
    return indexOrEr;
}

void modifyBike(bBike* list, int len, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int indexOrEr, id, posibleBikes[len], posibleBikesLen, posibleTypes[typesLen], typeIndex;
    char option = 'd', options[3] = "abc";
    float posibleWheels[4] = {20, 26, 27.5, 29};
    fillBikePosibilities(list, len, posibleBikes, &posibleBikesLen);
    fillTypesPosibilities(types,typesLen,posibleTypes);
    progHeader("Administracion de Bicicleteria");
    subHeader("Modificar Bicicleta");
    printBikes(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
    getIntCheck(&id,"\nQue bicicleta desea modificar? (#ID sin los 0s a la izquierda):", posibleBikes, posibleBikesLen);
    indexOrEr = findBikeById(list,len,id);
    typeIndex = findTypeById(types,typesLen,list[indexOrEr].idType);
    while ( option != 'c' && indexOrEr != -1 )
    {
        do
        {
            progHeader("Administracion de Bicicleteria");
            subHeader("Modificar Bicicleta");
            printf("\nTipo: %s\nRodado %.1f\n", types[typeIndex].description, list[indexOrEr].wheelSize);
            getChar(&option,"\na) Modificar Tipo\nb) Modificar Rodado\nc) Volver Menu Principal\nQue desea hacer? (# opcion): ","Error, lo ingresado no es una opcion valida",options);
        }while ( validarChar(option, options) );
        switch (option)
        {
            case 'a':
                progHeader("Administracion de Bicicleteria");
                subHeader("Modificar Bicicleta");
                printTypes(types,typesLen);
                getIntCheck(&list[indexOrEr].idType,"\nIngrese el nuevo tipo", posibleTypes,typesLen);
                break;
            case 'b':
                progHeader("Administracion de Bicicleteria");
                subHeader("Modificar Bicicleta");
                getFloatCheck(&list[indexOrEr].wheelSize, "\nIngrese el nuevo rodado: ", posibleWheels, 4);
                break;
        }
    }
}

void eraseBike(bBike* list, int len, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int id, posibleBikes[len], posibleBikesLen;
    fillBikePosibilities(list, len, posibleBikes, &posibleBikesLen);
    progHeader("Administracion de Bicicleteria");
    subHeader("Borrar Bicicleta");
    printBikes(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
    getIntCheck(&id,"\nQue bicicleta desea borrar? (#ID sin los 0s a la izquierda):", posibleBikes, posibleBikesLen);
    if(id!=-1)
    {
        removeBike(list,len,id);
        printf("Bicicleta borrada");
    }
    else
    {
        printf("No se borro ninguna bicicleta");
    }
}

void workEntree(wWork* list, int len, bBike* bikes, int bikesLen, tType* types, int typesLen, cColor* colors, int colorsLen, sService* services, int servicesLen, cClient* clients, int clientsLen)
{
    int id, idBike, idService, posibleBikes[len], posibleBikesLen, posibleServices[servicesLen];
    dDate date;
    fillBikePosibilities(bikes,bikesLen,posibleBikes,&posibleBikesLen);
    fillServicesPosibilities(services,servicesLen,posibleServices);
    progHeader("Administracion de Bicicleteria");
    subHeader("Alta de Trabajo");
    id = generateWorkID(list,len);
    printf("El ID del trabajo nuevo sera: %d",id);
    printBikes(bikes,bikesLen,types,typesLen,colors,colorsLen,clients,clientsLen);
    getIntCheck(&idBike, "\nIngrese el ID de la bicicleta sobre la que se trabajará: ", posibleBikes, posibleBikesLen);
    if (idBike!=-1)
    {
        printServices(services,servicesLen);
        getIntCheck(&idService, "\nIngrese el ID del servicio que se aplicará: ", posibleServices, servicesLen);
        if(idService!=-1)
        {
            printf("Ingrese la fecha de hoy: ");
            scanf("%02d/%02d/%04d",&date.day,&date.month,&date.year);
            addWork(list,len,id,idBike,idService,date);
            printf("Se guardo el nuevo trabajo");
        }
        else
        {
            printf("Trabajo cancelado");
        }
    }
    else
    {
        printf("Trabajo cancelado");
    }
}

void firstInform(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int i, typeIndex, colorIndex, clientIndex, posibleColors[colorsLen], noBikes = 1;
    progHeader("Administracion de Bicicleteria");
    subHeader("Mostrar Bicicletas por color");
    printColors(colors,colorsLen);
    fillColorsPosibilities(colors,colorsLen,posibleColors);
    getIntCheck(&colorIndex,"Color de las bicicletas quedesea ver: (#ID sin los 0s a la izquierda)",posibleColors,colorsLen);
    printf("\n     ID      Cliente       Marca          Tipo           Color            Rodado\n");
    printf("----------------------------------------------------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        if ( list[i].isEmpty == 0 && list[i].idColor == colorIndex )
        {
            typeIndex = findTypeById(types,typesLen,list[i].idType);
            clientIndex = findClientById(clients,clientsLen, list[i].idClient);
            printf("%07d|%19s|%19s|%19s|%19s|%.1f\n", list[i].id, clients[clientIndex].name, list[i].tradeMark,types[typeIndex].description, colors[colorIndex].colorName, list[i].wheelSize);
            printf("----------------------------------------------------------------------------\n");
            noBikes = 0;
        }
    }
    if(noBikes)
    {
        printf("No se encontraron bicicletas de ese color");
    }
}

void secondInform(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int i, typeIndex, colorIndex, clientIndex, posibleTypes[typesLen], noBikes = 1;
    progHeader("Administracion de Bicicleteria");
    subHeader("Mostrar Bicicletas por Tipo");
    printTypes(types,typesLen);
    fillTypesPosibilities(types,typesLen,posibleTypes);
    getIntCheck(&typeIndex,"Tipo de bicicletas quedesea ver: (#ID sin los 0s a la izquierda)",posibleTypes,typesLen);
    printf("\n     ID      Cliente       Marca          Tipo           Color            Rodado\n");
    printf("----------------------------------------------------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        if ( list[i].isEmpty == 0 && list[i].idType == typeIndex )
        {
            colorIndex = findColorById(colors,colorsLen,list[i].idColor);
            clientIndex = findClientById(clients,clientsLen, list[i].idClient);
            printf("%07d|%19s|%19s|%19s|%19s|%.1f\n", list[i].id, clients[clientIndex].name, list[i].tradeMark,types[typeIndex].description, colors[colorIndex].colorName, list[i].wheelSize);
            printf("----------------------------------------------------------------------------\n");
            noBikes = 0;
        }
    }
    if(noBikes)
    {
        printf("No se encontraron bicicletas de ese tipo");
    }
}

void thirdInform(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int i, typeIndex, colorIndex, clientIndex, noBikes;
    float minorWheelSize;
    progHeader("Administracion de Bicicleteria");
    subHeader("Mostrar Bicicletas por Tipo");
    for(int i = 0; i<length; i++)
    {
        if(i==0||minorWheelSize>list[i].wheelSize)
        {
            minorWheelSize=list[i].wheelSize;
        }
    }
    printf("\n     ID      Cliente       Marca          Tipo           Color            Rodado\n");
    printf("----------------------------------------------------------------------------\n");
    for ( i = 0 ; i < length ; i++ )
    {
        if ( list[i].isEmpty == 0 && list[i].wheelSize == minorWheelSize)
        {
            typeIndex = findTypeById(types,typesLen,list[i].idType);
            colorIndex = findColorById(colors,colorsLen,list[i].idColor);
            clientIndex = findClientById(clients,clientsLen, list[i].idClient);
            printf("%07d|%19s|%19s|%19s|%19s|%.1f\n", list[i].id, clients[clientIndex].name, list[i].tradeMark,types[typeIndex].description, colors[colorIndex].colorName, list[i].wheelSize);
            printf("----------------------------------------------------------------------------\n");
            noBikes=0;
        }
    }
    if(noBikes)
    {
        printf("No hay bicicletas en la base de datos");
    }
}

void forthInform(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen)
{
    int i, j, typeIndex, colorIndex, clientIndex, posibleTypes[typesLen], noBikes;
    progHeader("Administracion de Bicicleteria");
    subHeader("Mostrar Bicicletas Separadas por Tipo");
    fillTypesPosibilities(types,typesLen,posibleTypes);
    printf("\n     ID      Cliente       Marca          Tipo           Color            Rodado\n");
    printf("-------------------------------------------------------------------------------------\n");
    for (j=0;j<typesLen;j++)
    {
        noBikes=1;
        typeIndex=posibleTypes[j];
        printf("-------------------------------------------------------------------------------------\n");
        printf("--------------------------------------%s---------------------------------------\n",types[typeIndex].description);
        printf("-------------------------------------------------------------------------------------\n");
        for ( i = 0 ; i < length ; i++ )
        {
            if ( list[i].isEmpty == 0 && list[i].idType == typeIndex )
            {
                colorIndex = findColorById(colors,colorsLen,list[i].idColor);
                clientIndex = findClientById(clients,clientsLen, list[i].idClient);
                printf("%07d|%19s|%19s|%19s|%19s|%.1f\n", list[i].id, clients[clientIndex].name, list[i].tradeMark,types[typeIndex].description, colors[colorIndex].colorName, list[i].wheelSize);
                printf("-------------------------------------------------------------------------------------\n");
                noBikes = 0;
            }
        }
        if(noBikes)
        {
            printf("No se encontraron bicicletas de ese tipo");
        }
    }
}

void fifthInform(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen)
{
    int i, typeIndex, colorIndex, posibleTypes[typesLen], posibleColors[colorsLen], noBikes = 1,cont=0;
    progHeader("Administracion de Bicicleteria");
    subHeader("Contar Bicicletas por Tipo y Color");
    printTypes(types,typesLen);
    fillTypesPosibilities(types,typesLen,posibleTypes);
    getIntCheck(&typeIndex,"Tipo de bicicletas que desea contar: (#ID sin los 0s a la izquierda)",posibleTypes,typesLen);
    printColors(colors,colorsLen);
    fillColorsPosibilities(colors,colorsLen,posibleColors);
    getIntCheck(&colorIndex,"Color de las bicicletas que desea contar: (#ID sin los 0s a la izquierda)",posibleColors,colorsLen);
    for(i=0;i<length;i++)
    {
        if (list[i].idType==typeIndex && list[i].idColor==colorIndex)
        {
            cont++;
            noBikes=0;
        }
    }
    if(noBikes)
    {
        printf("No se encontraron bicicletas de ese tipo y color");
    }
    else
    {
        printf("En la base de datos hay %d bicicletas del tipo y color indicados",cont);
    }
}
/*Mostrar el o los colores más elegidos por los clientes.*/

void informMenuLogic(bBike* list, int len, tType* types, int typesLen,cColor* colors, int colorsLen, sService* services, int servicesLen,wWork* works, int worksLen, cClient* clients, int clientsLen)
{
    char options[7]="abcdefg", option = 'h';
    while ( option != 'k' )
    {
        progHeader("Administracion de Bicicleteria");
        subHeader("Menu Informes");
        getChar(&option,"\na) Mostrar Bicicletas del color seleccionado\nb) Mostrar bicicletas de un tipo seleccionado\nc) Informar la o las bicicletas de menor rodado\nd) Mostrar un listado de las bicicletas separadas por tipo\ne) Elegir un color y un tipo y contar cuantas bicicletas hay de ese color y ese tipo\nf) Mostrar el o los colores más elegidos por los clientes\ng) Volver al menu principal\nQue desea hacer? (# opcion): ","Error eso no es una opcion valida",options);
        switch (option)
        {
            case 'a':
                firstInform(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                break;
            case 'b':
                secondInform(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                break;
            case 'c':
                thirdInform(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                break;
            case 'd':
                forthInform(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                break;
            case 'e':
                fifthInform(list,len,types,typesLen,colors,colorsLen);
                break;
            case 'f':
                break;
            }
        printf("\nPrecione una tecla para continuar...");
        fflush(stdin);
        getc(stdin);
    }
}

void mainMenuLogic(bBike* list, int len, tType* types, int typesLen,cColor* colors, int colorsLen, sService* services, int servicesLen,wWork* works, int worksLen, cClient* clients, int clientsLen)
{
    int flagTheresBikes = 0, flagTheresWork=0;
    char options[11]="abcdefghijk", option = 'l';
    while ( option != 'k' )
    {
        progHeader("Administracion de Bicicleteria");
        subHeader("Memu Principal");
        getChar(&option,"\na) ALTA BICICLETA\nb) MODIFICAR BICICLETA\nc) BAJA BICICLETA\nd) LISTAR BICICLETAS\ne) LISTAR TIPOS\nf) LISTAR COLORES\ng) LISTAR SERVICIOS\nh) ALTA TRABAJO\ni) LISTAR TRABAJOS\nj) Informes\nK) Cerrar Programa\nQue desea hacer? (# opcion): ","Error eso no es una opcion valida",options);
        switch (option)
        {
            case 'a':
                if ( bikeHasSpace(list, len) )
                {
                    bikeEntree(list,len,clients,clientsLen);
                    flagTheresBikes = 1;
                }
                else
                {
                    printf("\nNo es posible acceder a esta opcion porque no hay mas espacio en la base de datos");
                }
                break;
            case 'b':
                if ( flagTheresBikes == 1 )
                {
                    modifyBike(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                }
                else
                {
                    printf("\nNo es posible acceder a esta opcion porque no hay bicicletas en la base de datos");
                }
                break;
            case 'c':
                if ( flagTheresBikes == 1 )
                {
                    eraseBike(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                }
                else
                {
                    printf("\nNo es posible acceder a esta opcion porque no hay bicicletas en la base de datos");
                }
                break;
            case 'd':
                progHeader("Administracion de Bicicleteria");
                subHeader("Lista de Bicicletas");
                if ( flagTheresBikes == 1 )
                {
                    printBikes(list,len,types,typesLen,colors,colorsLen,clients,clientsLen);
                }
                else
                {
                    printf("\nNo es posible acceder a esta opcion porque no hay bicicletas en la base de datos");
                }
                break;
            case 'e':
                progHeader("Administracion de Bicicleteria");
                subHeader("Lista de Tipos");
                printTypes(types,typesLen);
                break;
            case 'f':
                progHeader("Administracion de Bicicleteria");
                subHeader("Lista de Colores");
                printColors(colors,colorsLen);
                break;
            case 'g':
                progHeader("Administracion de Bicicleteria");
                subHeader("Lista de Servicios");
                printServices(services,servicesLen);
                break;
            case 'h':
                workEntree(works,worksLen,list,len,types,typesLen,colors,colorsLen, services, servicesLen, clients, clientsLen);
                if (flagTheresWork == 0)
                {
                    flagTheresWork=1;
                }
                break;
            case 'i':
                progHeader("Administracion de Bicicleteria");
                subHeader("Lista de Trabajos");
                if ( flagTheresWork == 1 )
                {
                    printWorks(works,worksLen,list,len,types,typesLen,services,servicesLen);
                }
                else
                {
                    printf("\nNo es posible acceder a esta opcion porque no hay trabajos en la base de datos");
                }
                break;
            case 'j':
                progHeader("Administracion de Bicicleteria");
                subHeader("Informes");
                break;
            case 'k':
                system("cls");
                printf("Hasta luego!");
                break;
        }
        printf("\nPrecione una tecla para continuar...");
        fflush(stdin);
        getc(stdin);
    }
}

/*

    H. ALTA TRABAJO: Se dará de alta cada ocurrencia de trabajo pidiéndole al usuario que elija una bicicleta y un Servicio

    I. LISTAR TRABAJOS
*/
