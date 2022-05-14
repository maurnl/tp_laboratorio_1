/*
 * ArrayPassenger.c
 *
 *  Created on: 29 abr. 2022
 *      Author: Mauro
 */
#include "ArrayPassenger.h"
#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFlight(char code[10], char description[10]){
		printf("%-10s\t\t%-8s\n", code, description);
}

int printFlights(Flight* list, int len){
	int retorno;
	int i;
	retorno=-1;
	if(list!=NULL && len>0){
		printf("                           ** LISTADO DE VUELOS DISPONIBLES **\n");
		printf("----------------------------------------------------------------------------------------\n");
		printf("CODIGO      	        ESTADO\n");
		printf("----------------------------------------------------------------------------------------\n");
		for(i=0;i<len;i++){
			printFlight((list + i)->flycode, (list + i)->status);
		}
		retorno=0;
	}
	return retorno;
}

int getTypePassengerByCode(TypePassenger* list, int len, int typePassenger, char description[]){
	int retorno;
	int i;
	retorno=-1;
	if(description!=NULL){
		strcpy(description, "N/A");
		for(i=0;i<len;i++){
			if((list + i)->idTypePassenger==typePassenger) {
				strcpy(description, (list + i)->description);
				break;
			}
		}
	}
	return retorno;
}

int getEmptyIndex(Passenger* list, int len) {
	int retorno;
	int indiceLibre;
	int flagLibre;
	retorno = -1;
	indiceLibre = -1;
	flagLibre = 0;
	if(list!=NULL && len>0) {
		do {
			indiceLibre++;
			if(list[indiceLibre].isEmpty==1) {
				flagLibre=1;
			}
		}while(flagLibre==0 && indiceLibre<len);
		if(flagLibre) {
			retorno = indiceLibre;
		}
	}
	return retorno;
}

int initPassengers(Passenger* list, int len)	{
	int retorno;
	int i;
	retorno=-1;
	if(list!=NULL && len>0) {
		for(i=0;i<len;i++){
			list[i].isEmpty=1;
		}
		retorno=0;
	}
	return retorno;
}

int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[])	{
	int retorno;
	int index;
	retorno=-1;
	index = getEmptyIndex(list, len);
	if(list!=NULL && len>0 && id>0 && name!=NULL && lastName!=NULL && price>0 && typePassenger>0 && flycode!=NULL && index!=-1){
		list[index].id = id;
		strcpy(list[index].name, name);
		strcpy(list[index].lastName, lastName);
		list[index].price = price;
		list[index].typePassenger = typePassenger;
		strcpy(list[index].flycode, flycode);
		list[index].isEmpty=0;
		retorno=0;
	}
	return retorno;
}


int findPassengerById(Passenger* list, int len,int id)	{
	int retorno;
	int indiceId;
	int flagEnctontrado;
	retorno = -1;
	indiceId = -1;
	flagEnctontrado = 0;
	if(list!=NULL && len>0 && id>0) {
		do {
			indiceId++;
			if(list[indiceId].id == id && list[indiceId].isEmpty==0) {
				flagEnctontrado=1;
			}
		}while(flagEnctontrado==0 && indiceId<len);
		if(flagEnctontrado) {
			retorno = indiceId;
		}
	}
	return retorno;
}


int removePassenger(Passenger* list, int len, int id)	{
	int retorno;
	int i;
	retorno=-1;
	if(list!=NULL && len>0 && id>0) {
		for(i=0;i<len;i++) {
			if(list[i].id==id && list[i].isEmpty==0) {
				list[i].isEmpty=1;
				retorno=0;
			}
		}
	}
	return retorno;
}


int sortPassengers(Passenger* list, int len, int order)	{
	int retorno;
	Passenger tmpActual;
	int i;
	int j;
	retorno=-1;
	if(list!=NULL && len>0) {
		for(i=1;i<len;i++) {
			tmpActual = list[i];
			j=i-1;
			if(order==1) {
				while(j>=0 && strcmp(tmpActual.lastName, list[j].lastName)<0) { // Decreciente. Evalua tmpActual con todos los elementos a su izquierda y desplaza a la derecha
					list[j+1] = list[j];
					j--;
				}
				list[j+1]=tmpActual;
			} else {
				while(j>=0 && strcmp(tmpActual.lastName, list[j].lastName)>0) {// Creciente. Evalua tmpActual con todos los elementos a su izquierda y desplaza a la derecha
					list[j+1] = list[j];
					j--;
				}
				list[j+1]=tmpActual;
			}
		}
		for(i=1;i<len;i++) {
			tmpActual = list[i];
			j=i-1;
			if(order==1) {
				while(j>=0 && tmpActual.typePassenger<list[j].typePassenger) { // Decreciente. Evalua tmpActual con todos los elementos a su izquierda y desplaza a la derecha
					list[j+1] = list[j];
					j--;
				}
				list[j+1]=tmpActual;
			} else {
				while(j>=0 && tmpActual.typePassenger>list[j].typePassenger) {// Creciente. Evalua tmpActual con todos los elementos a su izquierda y desplaza a la derecha
					list[j+1] = list[j];
					j--;
				}
				list[j+1]=tmpActual;
			}
		}
		retorno=0;
	}
	return retorno;
}


void printPassenger(TypePassenger* listTypes, int lengthTypes, int id, char lastName[], char name[], float price, char flycode[], int typePassenger, int header){
	char typePassengerDesc[25];
	getTypePassengerByCode(listTypes, lengthTypes, typePassenger, typePassengerDesc);
	if(header==0) {
		printf("%d\t %-10s\t %-8s\t $%-6.2f\t %-4s\t\t %s\n",id, lastName, name, price, flycode, typePassengerDesc);
	} else {
		printf("----------------------------------------------------------------------------------------\n");
		printf("ID       APELLIDO        NOMBRE          PRECIO          CODIGO          TIPO DE PASAJERO\n");
		printf("%d\t %-10s\t %-8s\t $%-6.2f\t %-4s\t\t %s\n",id, lastName, name, price, flycode, typePassengerDesc);
		printf("----------------------------------------------------------------------------------------\n");
	}
}

int printPassengers(Passenger* list, TypePassenger* listTypes,int length, int lengthTypes) {
	int retorno;
	int i;
	retorno=-1;
	if(list!=NULL && length>0) {
		printf("                           ** LISTADO PASAJEROS **\n");
		printf("----------------------------------------------------------------------------------------\n");
		printf("ID       APELLIDO        NOMBRE          PRECIO          CODIGO          TIPO DE PASAJERO\n");
		for(i=0;i<length;i++) {
			if((list+i)->isEmpty==0){
				printPassenger(listTypes, lengthTypes, (list+i)->id, (list+i)->lastName, (list+i)->name, (list+i)->price, (list+i)->flycode, (list + i)->typePassenger, 0);
			}
		}
		printf("----------------------------------------------------------------------------------------\n");
		retorno=0;
	}
	return retorno;
}

int printPassengersByCode(Passenger* list, Flight* listFlight,int length, int lengthFlight) {
	int retorno;
	int i;
	char status[10];
	retorno=-1;
	if(list!=NULL && length>0) {
		printf("                           ** LISTADO PASAJEROS **\n");
		printf("----------------------------------------------------------------------------------------\n");
		printf("ID       APELLIDO        NOMBRE          PRECIO          CODIGO          ESTADO DE VUELO\n");
		for(i=0;i<length;i++) {
			if((list+i)->isEmpty==0){
				getFlightStatusByCode(listFlight, lengthFlight, (list+i)->flycode, status);
				printf("%d\t %-10s\t %-8s\t $%-6.2f\t %-4s\t\t %s\n",(list+i)->id, (list+i)->lastName, (list+i)->name, (list+i)->price, (list+i)->flycode, status);
			}
		}
		printf("----------------------------------------------------------------------------------------\n");
		retorno=0;
	}
	return retorno;
}

int getFlightStatusByCode(Flight* list, int len, char code[], char status[]){
	int retorno;
	int i;
	retorno=-1;
	if(list!=NULL && code!=NULL && status!=NULL){
		strcpy(status,"N/A");
		for(i=0;i<len;i++){
			if(strcmp((list+i)->flycode, code)==0){
				strcpy(status, (list+i)->status);
			}
		}
		retorno=0;
	}
	return retorno;
}

int sortPassengersByCode(Passenger* list, Flight* flycodeList, int len, int flycodeLen)	{
	int retorno;
	Passenger tmpActual;
	int i;
	int j;
	char statusActual[10];
	char statusComp[10];
	retorno=-1;
	if(list!=NULL && len>0) {
		for(i=1;i<len;i++) {
			tmpActual = list[i];
			j=i-1;
			while(j>=0 && strcmp(tmpActual.flycode, list[j].flycode)<0) { // Decreciente. Evalua tmpActual con todos los elementos a su izquierda y desplaza a la derecha
				list[j+1] = list[j];
				j--;
			}
			list[j+1]=tmpActual;
		}
		for(i=1;i<len;i++) {
			tmpActual = list[i];
			getFlightStatusByCode(flycodeList, flycodeLen, list[i].flycode, statusActual);
			j=i-1;
			getFlightStatusByCode(flycodeList, flycodeLen, list[j].flycode, statusComp);
			while(j>=0 && strcmp(statusActual, statusComp)<0) { // Decreciente. Evalua tmpActual con todos los elementos a su izquierda y desplaza a la derecha
				list[j+1] = list[j];
				j--;
				getFlightStatusByCode(flycodeList, flycodeLen, list[j].flycode, statusComp);
			}
			list[j+1]=tmpActual;
		}
		retorno=0;
	}
	return retorno;
}

int getAveragePrice(Passenger* list, int len, float* average, float* total){
	int retorno;
	int contador;
	int i;
	float acumulador;
	acumulador=0;
	contador=0;
	retorno=-1;
	if(list!=NULL && len>0 && average!=NULL && total!=NULL){
		for(i=0;i<len;i++) {
			if((list + i)->isEmpty==0) {
				acumulador=acumulador + ((list + i)->price);
				contador++;
			}
		}
		*average=acumulador/contador;
		*total=acumulador;
		retorno=0;
	}
	return retorno;
}

int printHigherThanAveragePassengers(Passenger* list, int len){
	int retorno;
	int i;
	float promedio;
	float total;
	retorno=-1;
	if(list!=NULL && len>0){
		getAveragePrice(list, len, &promedio, &total);
		printf("**         TOTAL DE PASAJES: $%.2f        **\n", total);
		printf("** LISTADO PASAJEROS CON PRECIO MAYOR A $%.2f  **\n", promedio);
		printf("-----------------------------------------------------\n");
		printf("ID       APELLIDO        NOMBRE          PRECIO \n");
		printf("-----------------------------------------------------\n");
		for(i=0;i<len;i++){
			if((list + i)->isEmpty==0 && (list + i)->price > promedio) {
				printf("%d\t %-10s\t %-8s\t $%-6.2f\n", (list + i)->id, (list + i)->name, (list + i)->lastName, (list + i)->price);
			}
		}
		printf("-----------------------------------------------------\n");
		retorno=0;
	}
	return retorno;
}

void altaForzada(Passenger* list, int len, int* activePassengers, int* passengerCounter){
	addPassenger(list, len, *passengerCounter, "Esteban", "Gonzalez", 31200, 1, "3D9MCA");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Carlos", "Nuñez", 21000.5, 3, "3D9MCA");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Alberto", "Perez", 31099.5, 1, "3D9MCA");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Santiago", "Sanchez", 25000.5, 3, "D9M3FC");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Germán", "Diaz", 47400.5, 2, "0DC931");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Yanina", "Ruiz", 27000.5, 1, "D0ASC9");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Leandro", "Torres", 23000.5, 1, "D0ASC9");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Malena", "Monet", 17000.5, 3, "D9M3FC");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Mirta", "Vivian", 49500.5, 2, "D9M3FC");
	*activePassengers = *activePassengers + 1;
	*passengerCounter = *passengerCounter + 1;
	addPassenger(list, len, *passengerCounter, "Sandra", "Edin", 17000.5, 1, "D0ASC9");
	*passengerCounter = *passengerCounter + 1;
	*activePassengers = *activePassengers + 1;
}
