/*
 ============================================================================
 Name        : TP_2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ArrayPassenger.h"
#include "menu.h"
#include "controller.h"
#define PASSENGER_LEN 2000
int main(void) {
	setbuf(stdout, NULL);
	int opcion,salida;
	Passenger listPassengers[PASSENGER_LEN];
	initPassengers(listPassengers, PASSENGER_LEN);
	// Hardcodeo de 10 pasajeros con nombres y codigos variados a modo de prueba. Descomentar para usar.
	//hardcodePassengers(listPassengers,PASSENGER_LEN);
	do{
		opcion=menu();
		switch(opcion){
		case 1:
			salida=controller_addPassenger(listPassengers, PASSENGER_LEN);
			switch(salida){
				case 0:
					printf("- PASAJERO DADO DE ALTA CORRECTAMENTE.\n");
				break;
				case 1:
					printf("- ALTA CANCELADA CORRECTAMENTE.\n");
					break;
				case -1:
					printf("- DATO INVALIDO. PORFAVOR REINTENTE.\n");
					break;
				case -2:
					printf("- NO HAY ESPACIO DISPONIBLE.\n");
					break;
				case -3:
					printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
					break;
			}
			break;
		case 2:
			salida=controller_editPassenger(listPassengers, PASSENGER_LEN);
			switch(salida){
			case -1:
				printf("- ID DE PASAJERO NO ENCONTRADO.\n");
				break;
			case -2:
				printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
				break;
			}
			break;
		case 3:
			salida=controller_removePassenger(listPassengers, PASSENGER_LEN);
			switch(salida){
			case -3:
				printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
				break;
			case -2:
				printf("- ID DE PASAJERO NO ENCONTRADO.\n");
				break;
			case -1:
				printf("- BAJA CANCELADA CORRECTAMENTE.\n");
				break;
			case 0:
				printf("- PASAJERO DADO DE BAJA CORRECTAMENTE.\n");
			}
			break;
		case 4:
			salida=controller_listPassenger(listPassengers, PASSENGER_LEN);
			if(salida==-2){
				printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
			}
			break;
		case 5:
			break;
		}
	}while(opcion!=5);
	return EXIT_SUCCESS;
}
