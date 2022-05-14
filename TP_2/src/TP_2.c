/*
 ============================================================================
 Name        : TP_2.c
 Author      : LUCIANO, Mauro Nicolas (DIV J)
 Version     : laqueanda
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "ArrayPassenger.h"
#include "funciones.h"
#include <string.h>
#define PSGR_LEN 300
#define TYPES_LEN 3
#define FLIGHT_LEN 4
#define STR_LEN 51
int main(void) {
	setbuf(stdout, NULL);
	// Variables para control de menú
	int opcion;
	int subOpcion;
	int salida;
	// Variables para ABM
	int passengerCounter;
	int activePassengers;
	char nameTmp[STR_LEN];
	char lastNameTmp[STR_LEN];
	float priceTmp;
	int typePassengerTmp;
	char flycodeTmp[10];
	int idTmp;
	int indexTmp;
	// Declaración de lista de pasajeros
	Passenger ePassengerList[PSGR_LEN];
	TypePassenger eTypeList[] = {{1, "Ejecutivo"},{2, "Primera Clase"},{3, "Turista"}};
	Flight eFlightList[] = {{"D0ASC9","INACTIVO"},{"3D9MCA","ACTIVO"},{"0DC931", "ACTIVO"},{"D9M3FC","INACTIVO"}};
	// Inicialización variables contadores
	passengerCounter=1;
	activePassengers=0;
	// Llamada a initPassengers (Inicialización)
	initPassengers(ePassengerList, PSGR_LEN);
	do {
		printf("----------------------------------------------------------\n\n");
		printf("		    ** MENU PRINCIPAL **\n\n"
				"			1. ALTAS.\n"
				"			2. MODIFICAR.\n"
				"			3. BAJA.\n"
				"			4. INFORMAR.\n"
				"			5. ALTA FORZADA DE PASAJEROS.\n"
				"			6. SALIR.\n\n");
		printf("----------------------------------------------------------\n");
		getPositiveInt("INGRESE OPCION:  ",&opcion, 6);
		if(opcion>1 && opcion<5 && activePassengers==0) {
			printf("- DEBE DAR DE ALTA AL MENOS UN PASAJERO ANTES DE CONTINUAR.\n");
			while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
			opcion=1;
		}
		switch(opcion){
			case 1:
				printf("- ALTAS. \n");
				do {
					subOpcion=0;
					if(getEmptyIndex(ePassengerList, PSGR_LEN)==-1) {
						printf("NO HAY ESPACIO LIBRE. \n");
					} else {
						printf("\t\t**REGISTRAR NUEVO PASAJERO**\n");
						getAlphabeticText("- INGRESE NOMBRE: ", nameTmp, STR_LEN);
						getAlphabeticText("- INGRESE APELLIDO: ", lastNameTmp, STR_LEN);
						getPositiveFloat("- INGRESE PRECIO DEL VUELO (MENOR A $500000: ", &priceTmp, 500000.0);
						getPositiveInt("- INGRESE TIPO DE PASAJERO: \n\t1. EJECUTIVO.\n\t2. PRIMERA CLASE.\n\t3. TURISTA.\n", &typePassengerTmp, 3);
						printFlights(eFlightList, FLIGHT_LEN);
						getAlphanumericText("- INGRESE CODIGO DE VUELO: ", flycodeTmp, 10);
						printPassenger(eTypeList, TYPES_LEN, 0, nameTmp, lastNameTmp, priceTmp, flycodeTmp, typePassengerTmp, 1);
						subOpcion = confirm("- CONFIRME ALTA NUEVO PASAJERO (S/N): ");
						if(subOpcion==1) {
							salida = addPassenger(ePassengerList, PSGR_LEN, passengerCounter, nameTmp, lastNameTmp, priceTmp, typePassengerTmp, flycodeTmp);
							if(salida==-1) {
								printf("- ERROR DEL PROGRAMA.\n");
							} else {
								activePassengers++;
								passengerCounter++;
								subOpcion = confirm("- ALTA COMPLETADA. DESEA DAR DE ALTA UN NUEVO PASAJERO (S/N)?");
							}
						} else {
							subOpcion = confirm("- ALTA CANCELADA. DESEA VOLVER A INTENTAR (S/N)?");
						}
					}
				}while(subOpcion==1);
				break;
			case 2:
				printPassengers(ePassengerList, eTypeList, PSGR_LEN, TYPES_LEN);
				getPositiveInt("- INGRESE ID A BUSCAR EN EL SISTEMA: ", &idTmp, passengerCounter);
				indexTmp = findPassengerById(ePassengerList, PSGR_LEN, idTmp);
				if(indexTmp==-1) {
					printf("- ID PASAJERO %d NO SE ENCONTRO EN EL SISTEMA.\n", idTmp);
				} else {
					do {
						printf("                           ** PASAJERO ENCONTRADO **\n");
						printPassenger(eTypeList, TYPES_LEN, ePassengerList[indexTmp].id, ePassengerList[indexTmp].name, ePassengerList[indexTmp].lastName, ePassengerList[indexTmp].price, ePassengerList[indexTmp].flycode, ePassengerList[indexTmp].typePassenger, 1);
						getPositiveInt("- INGRESE DATO A MODIFICAR: \n"
									   "1. NOMBRE\n"
									   "2. APELLIDO\n"
									   "3. PRECIO\n"
									   "4. CODIGO\n"
										"5. TIPO DE PASAJERO\n"
										"6. VOLVER\n", &subOpcion, 6);
						switch(subOpcion) {
							case 1:
								getAlphabeticText("-INGRESE NOMBRE NUEVO: ", nameTmp, STR_LEN);
								printf("- NOMBRE NUEVO: %s\n", nameTmp);
								if(confirm("- CONFIRMAR MODIFICACION DE NOMBRE: (S/N)")==1) {
									strcpy(ePassengerList[indexTmp].name, nameTmp);
									printf("- MODIFICACION EXITOSA.\n");
								}
								break;
							case 2:
								getAlphabeticText("- INGRESE APELLIDO NUEVO: ", lastNameTmp, STR_LEN);
								printf("- APELLIDO NUEVO: %s\n", lastNameTmp);
								if(confirm("- CONFIRMAR MODIFICACION DE APELLIDO: (S/N)")==1) {
									strcpy(ePassengerList[indexTmp].lastName, lastNameTmp);
									printf("- MODIFICACION EXITOSA.\n");
								}
								break;
							case 3:
								getPositiveFloat("- INGRESE PRECIO NUEVO: ", &priceTmp, 500000);
								printf("- PRECIO NUEVO: %.2f", priceTmp);
								if(confirm("- CONFIRMAR MODIFICACION DE PRECIO: (S/N)")==1) {
									ePassengerList[indexTmp].price = priceTmp;
									printf("- MODIFICACION EXITOSA.\n");
								}
								break;
							case 4:
								getAlphanumericText("- INGRESE CODIGO DE VUELO NUEVO: ", flycodeTmp, 10);
								printf("- CODIGO DE VUELO NUEVO: %s", flycodeTmp);
								if(confirm("- CONFIRMAR MODIFICACION DE CODIGO: (S/N)")==1) {
									strcpy(ePassengerList[indexTmp].flycode, flycodeTmp);
									printf("- MODIFICACION EXITOSA.\n");
								}
								break;
							case 5:
								getPositiveInt("- INGRESE TIPO DE PASAJERO NUEVO: ", &typePassengerTmp, 3);
								printf("- TIPO DE PASAJERO NUEVO: %d", typePassengerTmp);
								if(confirm("- CONFIRMAR MODIFICACION DE TIPO DE PASAJERO: (S/N)")==1) {
									ePassengerList[indexTmp].typePassenger = typePassengerTmp;
									printf("- MODIFICACION EXITOSA.\n");
								}
								break;
							case 6:
								break;
							default:
								printf("- OPCION INGRESADA INVALIDA. \n");
								break;
						}
						if(confirm("- DESEA MODIFICAR OTRO DATO (S/N)?")==0){
							subOpcion = 6;
						}
					}while(subOpcion!=6);
				}
				break;
			case 3:
				do {
					printf("- BAJA DE PASAJEROS.\n");
					printPassengers(ePassengerList, eTypeList, PSGR_LEN, TYPES_LEN);
					getPositiveInt("- INGRESE ID A BUSCAR EN EL SISTEMA: ", &idTmp, passengerCounter);
					indexTmp = findPassengerById(ePassengerList, PSGR_LEN, idTmp);
					if(indexTmp==-1) {
						printf("- ID PASAJERO %d NO SE ENCONTRO EN EL SISTEMA.\n", idTmp);
					} else {
						printPassenger(eTypeList, TYPES_LEN, ePassengerList[indexTmp].id, ePassengerList[indexTmp].name, ePassengerList[indexTmp].lastName, ePassengerList[indexTmp].price, ePassengerList[indexTmp].flycode, ePassengerList[indexTmp].typePassenger, 1);
						if(confirm("- CONFIRME BAJA DE PASAJERO (S/N): ")==1) {
							removePassenger(ePassengerList, PSGR_LEN, idTmp);
							activePassengers--;
							printf("- PASAJERO ID %d DADO DE BAJA CON EXITO.\n", idTmp);
						}
					}
					if(activePassengers>0) {
						subOpcion = confirm("- DESEA DAR DE BAJA OTRO PASAJERO (S/N)?");
					} else {
						printf("- SE HAN ELIMINADO TODOS LOS PASAJEROS DEL SISTEMA. VOLVIENDO AL MENÚ.\n");
						while(confirm("- << PRESIONE ENTER PARA CONTINUAR... >>"));
					}
				}while(subOpcion==1 && activePassengers>0);
				break;
			case 4:
				printf("- INFORMES.\n");
				getPositiveInt("- 1. LISTAR TODOS LOS PASAJEROS ALFABETICAMENTE (A-Z).\n"
							   "- 2. LISTAR TODOS LOS PASAJEROS ALFABETICAMENTE (Z-A).\n"
						       "- 3. LISTAR TOTAL Y PROMEDIO DE PRECIOS Y PASAJEROS POR ENCIMA DEL PROMEDIO.\n"
						       "- 4. LISTAR TODOS LOS PASAJEROS ORDENADOS POR CODIGO Y ESTADO DEL VUELO.\n"
						       "- 5. VOLVER.", &subOpcion,5);
				switch(subOpcion){
					case 1:
						sortPassengers(ePassengerList, PSGR_LEN, 1);
						printPassengers(ePassengerList, eTypeList, PSGR_LEN, TYPES_LEN);
						while(confirm("- << PRESIONE ENTER PARA VOLVER AL MENÚ... >>"));
						break;
					case 2:
						sortPassengers(ePassengerList, PSGR_LEN, 0);
						printPassengers(ePassengerList, eTypeList, PSGR_LEN, TYPES_LEN);
						while(confirm("- << PRESIONE ENTER PARA VOLVER AL MENÚ... >>"));
						break;
					case 3:
						printHigherThanAveragePassengers(ePassengerList, PSGR_LEN);
						while(confirm("- << PRESIONE ENTER PARA VOLVER AL MENÚ... >>"));
						break;
					case 4:
						sortPassengersByCode(ePassengerList, eFlightList, PSGR_LEN, FLIGHT_LEN);
						printPassengersByCode(ePassengerList, eFlightList, PSGR_LEN, FLIGHT_LEN);
						while(confirm("- << PRESIONE ENTER PARA VOLVER AL MENÚ... >>"));
						break;
					case 5:
						break;
					default:
						printf("OPCION INVALIDA.\n");
				}
				break;
			case 5:
				printf("- ALTA FORZADA DE PASAJEROS.\n");
				if(confirm("- DESEA REALIZAR UN ALTA FORZADA DE 10 PASAJEROS(S/N)?")==1){
					altaForzada(ePassengerList, PSGR_LEN, &activePassengers, &passengerCounter);
					printf("- ALTA DE 10 PASAJEROS REALIZADA CON EXITO.\n");
				} else {
					printf("- ALTA CANCELADA.\n");
				}
				while(confirm("- << PRESIONE ENTER PARA VOLVER AL MENÚ... >>"));
				break;
			case 6:
				break;
			default:
				printf("OPCION INVALIDA.\n");
				break;
		}

	} while(opcion!=6);

	return EXIT_SUCCESS;
}
