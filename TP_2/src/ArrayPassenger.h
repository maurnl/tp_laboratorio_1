/*
 * ArrayPassenger.h
 *
 *  Created on: 29 abr. 2022
 *      Author: Mauro
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

typedef struct {
	char flycode[10];
	char status[10];
}Flight;

typedef struct {
	int idTypePassenger;
	char description[21];
}TypePassenger;

typedef struct {
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10]; // Flight FK.
	int typePassenger; // TypePassenger FK.
	int isEmpty;
}Passenger;

#endif /* ARRAYPASSENGER_H_ */
/** \brief To indicate that all position in the array are empty,* this function put the flag (isEmpty) in TRUE in all* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok*
*/
int initPassengers(Passenger* list, int len);

/** \brief add in a existing list of passengers the values received as parameters* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok */
int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[]);

/** \brief find a Passenger by Id en returns the index position in array.*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or NULL pointer received or passenger not found]
*/
int findPassengerById(Passenger* list, int len,int id);

/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't find a passenger] - (0) if Ok
*
*/
int removePassenger(Passenger* list, int len, int id);

/** \brief Sort the elements in the array of passengers, the argument order indicate UP or DOWN order
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok*
*/
int sortPassengers(Passenger* list, int len, int order);
/**
 * @brief Prints a single passenger data
 * @param id
 * @param name
 * @param lastName
 * @param price
 * @param flycode
 * @param typePassenger
 */
void printPassenger(TypePassenger* listTypes, int lengthTypes, int id, char lastName[], char name[], float price, char flycode[], int typePassenger, int header);

/** \brief print the content of passengers array
* \param list Passenger*
* \param length int
* \return int Returns (-1) if Error [NULL *list pointer or invalid length] - (0) if OK
*/
int printPassengers(Passenger* list, TypePassenger* listTypes,int length, int lengthTypes);

/** \brief Sort the elements in the array of passengers, the argument order indicate UP or DOWN order
*
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok*
*/
int sortPassengersByCode(Passenger* list, Flight* flycodeList, int len, int flycodeLen);

/**
 * brief Finds the first empty position in *list and returns it
 * @param *list Passenger* list
 * @param len length of Passenger* list
 * @return Return first empty position index or (-1) if error [NULL *list pointer or invalid length or no free index]
 */
int getEmptyIndex(Passenger* list, int len);

int getTypePassengerByCode(TypePassenger* list, int len, int typePassenger, char description[]);

void printFlight(char code[10], char description[10]);

int printFlights(Flight* list, int len);

int getAveragePrice(Passenger* list, int len, float* average, float* total);

int printHigherThanAveragePassengers(Passenger* list, int len);

int getFlightStatusByCode(Flight* list, int len, char code[], char status[]);

int printPassengersByCode(Passenger* list, Flight* listFlight,int length, int lengthFlight);

void altaForzada(Passenger* list, int len, int* activePassengers, int* passengerCounter);
