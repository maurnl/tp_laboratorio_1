/*
 ============================================================================
 Name        : TP1.c
 Author      : LUCIANO, Mauro Nicolas
 Version     : la que funciona
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

void imprimirMenu(float km,float precio1,float precio2);

int main(void) {
	setbuf(stdout, NULL);

	// Variables de control
	int opcion;
	int subOpcion;
	// Valores
	float precioDebitoAerolineas;
	float precioCreditoAerolineas;
	float precioBTCAerolineas;
	float precioUnitarioAerolineas;
	float precioDebitoLatam;
	float precioCreditoLatam;
	float precioBTCLatam;
	float precioUnitarioLatam;
	float diferenciaPrecios;
	float km = 0;
	float precioAerolineas = 0;
	float precioLatam = 0;
	// Banderas
	int flagKilometros = 0;
	int flagAerolineas = 0;
	int flagLatam = 0;
	int flagCalculos = 0;

	do {
		// Imprimir menú y pedir opción
		imprimirMenu(km, precioAerolineas, precioLatam);
		opcion = pedirIntPositivo("Ingrese una opción: ");
		switch(opcion) {
			case 1:
				// Pedir kilómetros y levantar bandera
				printf("Opcion 1. Ingresar kilómetros.\n");
				printf("Kilómetros actual: %.2f km\n", km);
				if(preguntar("Desea ingresar kilómetros nuevos? (s/n)")) {
					km = pedirFloatPositivo("Ingrese kilómetros de viaje: \n");
				}
				flagKilometros = 1;
				break;
			case 2:
				// Pedir precio de vuelos con submenú
				printf("Opcion 2. Ingresar Precio de Vuelos.\n");
				printf("Precio vuelos Aerolineas actual: $ %.2f \n", precioAerolineas);
				printf("Precio vuelos Latam actual: $ %.2f \n", precioLatam);
				if(preguntar("Desea ingresar precios de vuelo nuevos? (s/n)")) {
					printf("Ingresar precio a cambiar: \n");
					printf("1. Aerolineas.\n");
					printf("2. Latam\n");
					printf("3. Ambos\n");
					subOpcion = pedirIntPositivo(" ");
					switch(subOpcion) {
						case 1:
							precioAerolineas = pedirFloatPositivo("Ingrese precio Aerolineas nuevo: \n");
							flagAerolineas = 1;
							break;
						case 2:
							precioLatam = pedirFloatPositivo("Ingrese precio Latam nuevo: \n");
							flagLatam = 1;
							break;
						case 3:
							precioAerolineas = pedirFloatPositivo("Ingrese precio Aerolineas nuevo: \n");
							flagAerolineas = 1;
							precioLatam = pedirFloatPositivo("Ingrese precio Latam nuevo: \n");
							flagLatam = 1;
							break;
						default:
							printf("Opción no válida. \n");
							break;
					}
				}
				break;
			case 3:
				if(flagLatam && flagAerolineas && flagKilometros) {
					printf("Opcion 3. Calcular todos los costos.\n");
					//Calculos para Aerolineas -------
					// Debito
					aplicarPorcentaje(precioAerolineas, -10, &precioDebitoAerolineas);
					// Credito
					aplicarPorcentaje(precioAerolineas, 25, &precioCreditoAerolineas);
					// BTC
					pesoABtc(precioAerolineas, &precioBTCAerolineas);
					// Unitario
					precioUnitario(precioAerolineas, km, &precioUnitarioAerolineas);
					// Calculos para Latam ------
					// Debito
					aplicarPorcentaje(precioLatam, -1, &precioDebitoLatam);
					// Credito
					aplicarPorcentaje(precioLatam, 25, &precioCreditoLatam);
					// BTC
					pesoABtc(precioLatam, &precioBTCLatam);
					// Unitario
					precioUnitario(precioLatam, km, &precioUnitarioLatam);
					// Diferencia de precio
					diferenciaPrecios = precioLatam - precioAerolineas;
					// Bandera ------
					//
					flagCalculos = 1;
				} else {
					printf("Ingrese todos los datos primero.\n");
				}
				break;
			case 4:
				if(flagCalculos) {
					do {
						printf("KMs Ingresados: %.2f \n\n", km);
						printf("Precio Aerolineas: $%.2f \n", precioAerolineas);
						printf("a) Precio con tarjeta de debito: $ %.2f \n", precioDebitoAerolineas);
						printf("b) Precio con tarjeta de credito: $ %.2f \n", precioCreditoAerolineas);
						printf("c) Precio pagando con bitcoin: %.2f BTC \n", precioBTCAerolineas);
						printf("d) Mostrar precio unitario: $ %.2f \n\n", precioUnitarioAerolineas);
						printf("Precio Latam: $%.2f \n", precioLatam);
						printf("a) Precio con tarjeta de debito: $ %.2f \n", precioDebitoLatam);
						printf("b) Precio con tarjeta de credito: $ %.2f \n", precioCreditoLatam);
						printf("c) Precio pagando con bitcoin: %.2f BTC \n", precioBTCLatam);
						printf("d) Mostrar precio unitario: $ %.2f \n\n", precioUnitarioLatam);
						printf("Diferencia de precios: $ %.2f \n", diferenciaPrecios);
					} while (preguntar("Continuar? (s/n)")!=1);
				} else {
					printf("Calcule primero.\n");
				}
				break;
			case 5:
				printf("Opcion 5. Carga forzada de datos.\n");
				// Cargar valores
				km = 7090;
				precioAerolineas = 162965;
				precioLatam = 159339;
				// Levantar banderas
				flagKilometros = 1;
				flagAerolineas = 1;
				flagLatam = 1;
				flagCalculos = 1;
				// Hacer cálculos ...
				//Calculos para Aerolineas -------
				// Debito
				aplicarPorcentaje(precioAerolineas, -10, &precioDebitoAerolineas);
				// Credito
				aplicarPorcentaje(precioAerolineas, 25, &precioCreditoAerolineas);
				// BTC
				pesoABtc(precioAerolineas, &precioBTCAerolineas);
				// Unitario
				precioUnitario(precioAerolineas, km, &precioUnitarioAerolineas);
				// Calculos para Latam ------
				// Debito
				aplicarPorcentaje(precioLatam, -1, &precioDebitoLatam);
				// Credito
				aplicarPorcentaje(precioLatam, 25, &precioCreditoLatam);
				// BTC
				pesoABtc(precioLatam, &precioBTCLatam);
				// Unitario
				precioUnitario(precioLatam, km, &precioUnitarioLatam);
				// Diferencia de precio
				diferenciaPrecios = precioLatam - precioAerolineas;
				// Mostrar
				do {
					printf("KMs Ingresados: %.2f \n\n", km);
					printf("Precio Aerolineas: $%.2f \n", precioAerolineas);
					printf("a) Precio con tarjeta de debito: $ %.2f \n", precioDebitoAerolineas);
					printf("b) Precio con tarjeta de credito: $ %.2f \n", precioCreditoAerolineas);
					printf("c) Precio pagando con bitcoin: %.2f BTC \n", precioBTCAerolineas);
					printf("d) Mostrar precio unitario: $ %.2f \n\n", precioUnitarioAerolineas);
					printf("Precio Latam: $%.2f \n", precioLatam);
					printf("a) Precio con tarjeta de debito: $ %.2f \n", precioDebitoLatam);
					printf("b) Precio con tarjeta de credito: $ %.2f \n", precioCreditoLatam);
					printf("c) Precio pagando con bitcoin: %.2f BTC \n", precioBTCLatam);
					printf("d) Mostrar precio unitario: $ %.2f \n\n", precioUnitarioLatam);
					printf("Diferencia de precios: $ %.2f \n", diferenciaPrecios);
				} while (preguntar("Continuar? (s/n)")!=1);
				break;
			case 6:
				printf("SALIR.\n");
				break;
			default:
				printf("Opción no válida.\n");
				break;
		}

	} while (opcion != 6);

	return EXIT_SUCCESS;
}

void imprimirMenu(float km, float precio1, float precio2) {
	printf("1. Ingresar Kilómetros: (km= %.2f km) \n"
	 "2. Ingresar Precio de Vuelos: (Aerolíneas= $ %.2f, Latam= $ %.2f ) \n"
	 "3. Calcular todos los costos: \n"
	 "\ta) Tarjeta de débito (descuento 10 porciento ) \n"
	 "\tb) Tarjeta de crédito (interés 25 porciento ) \n"
	 "\tc) Bitcoin (1BTC -> 4538021.05 Pesos Argentinos) \n"
	 "\td) Mostrar precio por km (precio unitario) \n"
	 "\te) Mostrar diferencia de precio ingresada (Latam - Aerolíneas) \n"
	 "4. Informar Resultados \n"
	 "5. Carga forzada de datos \n"
	 "6. Salir \n", km, precio1, precio2);
}
