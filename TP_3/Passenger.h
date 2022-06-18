/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */
#include "LinkedList.h"

#ifndef PASSENGER_H_
#define PASSENGER_H_

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	int tipoPasajero;
	char codigoVuelo[9];
	char estadoVuelo[25];
	int isEmpty;
}Passenger;

Passenger* Passenger_new();
//Passenger* Passenger_newParametros(char* idStr,char* nombreStr,char* tipoPasajeroStr);
Passenger* Passenger_newParametros(int id,char* nombre,char* apellido,float precio,int tipoPasajero,char* codigoVuelo,char* estadoVuelo);
void Passenger_delete();

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this,int* id);

int Passenger_setNombre(Passenger* this,char* nombre);
int Passenger_getNombre(Passenger* this,char* nombre);

int Passenger_setApellido(Passenger* this,char* apellido);
int Passenger_getApellido(Passenger* this,char* apellido);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_setTipoPasajeroStr(Passenger* this,char* tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero);
int Passenger_getTipoPasajeroStr(Passenger* this, char* tipoPasajero);

int Passenger_setPrecio(Passenger* this,float precio);
int Passenger_getPrecio(Passenger* this,float* precio);

int Passenger_setEstadoVuelo(Passenger* this,char* estado);
int Passenger_getEstadoVuelo(Passenger* this,char* estado);

int Passenger_setIsEmpty(Passenger* this, int estado);
int Passenger_getIsEmpty(Passenger* this);

int Passenger_mostrarPasajero(Passenger* this);
void Passenger_printHeader(int qty);
int Passenger_getPassengerById(LinkedList* pArrayListPassenger, int id);
int Passenger_compareById(void* arg1, void* arg2);
int Passenger_compareByLastName(void* arg1, void* arg2);

#endif /* PASSENGER_H_ */
