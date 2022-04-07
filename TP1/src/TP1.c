/*
 ============================================================================
 Name        : TP1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void imprimirMenu(void);

int main(void) {
	setbuf(stdout, NULL);

	int opcion;
	float km = 0;
	float precioAerolineas = 0;
	float precioLatam = 0;
	int flagOpUno = 0;
	int flagOpDos = 0;
	int flagOpTres = 0;

	do {
		imprimirMenu();
		scanf("%d", &opcion);
		switch(opcion) {
			case 1:
				printf("Opcion 1. Ingresar kilómetros.\n");
				printf("Kilómetros actual: %.2f km\n", km);
				if(preguntar("Desea ingresar kilómetros nuevos? (s/n)")) {
					printf("Ingrese kilómetros de viaje: \n");
					scanf("%f", &km);
				}
				flagOpUno = 1;
				break;
			case 2:
				printf("Opcion 2. Ingresar Precio de Vuelos.\n");
				printf("Precio vuelos Aerolineas actual: $ %.2f \n", precioAerolineas);
				printf("Precio vuelos Latam actual: $ %.2f \n", precioLatam);
				if(preguntar("Desea ingresar precios de vuelo nuevos? (s/n)")) {
					precioAerolineas = pedirFloat("Ingrese precio Aerolineas nuevo: \n");
					precioLatam = pedirFloat("Ingrese precio Latam nuevo: \n");
					flagOpDos = 1;
				}
				break;
			case 3:
				if(flagOpDos && flagOpUno) {
					printf("Opcion 3. Calcular todos los costos.\n");
					flagOpTres = 1;
				} else {
					printf("Ingrese datos válidos primero.\n");
				}
				break;
			case 4:
				if(flagOpTres) {
					printf("Opcion 4. Informar resultados.\n");
				} else {
					printf("Calcule primero.\n");
				}
				break;
			case 5:
				printf("Opcion 5. Carga forzada de datos.\n");
				flagOpUno = 1;
				flagOpDos = 1;
				break;
			case 6:
				printf("SALIR.\n");
				break;
			default:
				printf("Opción no válida.\n");
				break;
		}

	} while (opcion != 6);
}

void imprimirMenu(void) {
	printf("MENU PRINCIPAL.\n"
	"ELIGA UNA OPCION:\n"
	"1. Ingresar kilómetros.\n"
	"2. Ingresar Precio de Vuelos.\n"
	"3. Calcular todos los costos.\n"
	"4. Informar resultados.\n"
	"5. Carga forzada de datos.\n"
	"6. Salir.\n");
}
