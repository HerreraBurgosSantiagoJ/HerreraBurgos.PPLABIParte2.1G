#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

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

#define MAXEMP 1000


#endif // ARRAYEMPLOYEES_H_INCLUDED

//Grups functions that allow working on data, stored in structure bBike.

/** \brief To indicate that all position in the array are empty,
 * this function set the flag (isEmpty) in TRUE in all
 * position of the array
 * \param list Employee* Pointer to array of employees
 * \param len int Array length
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int initBikes(bBike* list, int len);


/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
*/

int addBike(bBike* list, int len, int id, char tradeMark[],int idType,int idColor, int wheelSize, int idClient, char* name, char sex, cClient* clients);


/** \brief find an Employee by Id en returns the index position in array.
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
 *
 */

int findBikeById(bBike* list, int len,int id);



/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
 *
 * \param list Employee*
 * \param len int
 * \param id int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
 *
 */

int removeBike(bBike* list, int len, int id);



/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
 *
 * \param list Employee*
 * \param len int
 * \param order int [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int sortBikes(bBike* list, int len, int order);



/** \brief print the content of employees array
 *
 * \param list Employee*
 * \param length int
 * \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
 *
 */

int printBikes(bBike* list, int length, tType* types, int typesLen, cColor* colors, int colorsLen, cClient* clients, int clientsLen);



/** \brief Copies the string from on the string to
 *
 * \param to Char array where the data will be copied
 * \param from Char array containing the data to be copied
 *
 */

void myStrcpy(char to[],char from[]);



/** \brief Generates an ID adding one to the last ID created
 *
 * \param list Struct array to check the last ID created
 * \param len Length of list
 * \return New ID
 *
 */

int generateID(bBike* list, int len);



/** \brief Logicaly checks if the emp list has free space
 *
 * \param list To be checked
 * \param len Length of list
 * \return index (1) if yes, (0) otherwise
 *
 */

int bikeHasSpace(bBike* list, int len);



/** \brief Find index of given ID
 *
 * \param list To be checked
 * \param len Length of list
 * \return index if ID exists, (-1) if user cancels search or search doesn't hit on given trys
 *
 */

int getIdIndex(bBike* list, int len);

int printTypes(tType* list, int length);

int printColors(cColor* list, int length);

int printServices(sService* list, int length);

int addWork(wWork* list, int len, int id, int idBike, int idService, dDate date);

int findTypeById(tType* list, int len,int id);

int findServiceById(sService* list, int len,int id);

int printWorks(wWork* list, int length, bBike* bikes, int bikesLen, tType* types, int typesLen, sService* services, int servicesLen);

void fillBikePosibilities(bBike* list, int len, int* array, int* newLen);

void fillColorsPosibilities(cColor* list, int len, int* array);

void fillTypesPosibilities(tType* list, int len, int* array);

void fillServicesPosibilities(sService* list, int len, int* array);

int generateWorkID(wWork* list, int len);

int findClientById(cClient* list, int len,int id);

int findColorById(cColor* list, int len,int id);

int initWorks(wWork* list, int len);
