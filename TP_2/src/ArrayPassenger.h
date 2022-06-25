/*
 * ArrayPassenger.h
 *
 *  Created on: 25 jun. 2022
 *      Author: Mauro
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

typedef struct{
	int typeId;
	char typeDescription[25];

}TypePassenger;

typedef struct{
	int id;
	char name[51];
	char lastName[51];
	float price;
	char flycode[10];
	TypePassenger typePassenger;
	int statusFlight;
	int isEmpty;
}Passenger;

#endif /* ARRAYPASSENGER_H_ */

int passengerListIsEmpty(Passenger* list, int len);
int initPassengers(Passenger* list, int len);
int addPassengers(Passenger* list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[],int statusFlight);
int findPassengerById(Passenger* list, int len, int id);
int removePassenger(Passenger* list, int len, int id);
int sortPassengers(Passenger* list,int len, int order);
int printPassengers(Passenger* list, int len);
int sortPassengersByFlycode(Passenger* list, int len, int order);
int nextPassengerId(void);

int getEmptyPassengerIndex(Passenger* list, int len);
int typePassengerStrToInt(char* type);
void printPassenger(Passenger passenger);
int typePassengerToStr(int typeId, char* typeDesc);
int getPassengersAverageAndTotalPrice(Passenger* list, int len, float* average, float* total);
int printHigherThanAveragePassengers(Passenger* list, int len);
void hardcodePassengers(Passenger* list, int len);
