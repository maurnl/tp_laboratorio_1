/*
 * funciones.c
 *
 *  Created on: 1 abr. 2022
 *      Author: Mauro
 */
#define PRECIO_BTC 4606954.55
#include <stdio.h>
#include <ctype.h>

int preguntar(char mensaje[]) {
	char respuesta;
	respuesta = getchar();
	respuesta = toupper(respuesta);
	while((respuesta != 'S') & (respuesta != 'N')) {
		puts(mensaje);
		respuesta = getchar();
		respuesta = toupper(respuesta);
	}

	if (respuesta == 'S') {
		return 1;
	} else {
		return 0;
	}
}

float aplicarPorcentaje(float precioBase, float porcentaje) {
	float resultado;

	resultado = precioBase + ((precioBase * porcentaje) / 100);

	return resultado;
}

float pesoABtc(float precio) {
	float resultado;

	resultado = precio / PRECIO_BTC;

	return resultado;
}

float precioUnitario(float precioTotal, float unidades) {
	float resultado;

	resultado = precioTotal / unidades;

	return resultado;
}

float pedirFloat(char mensaje[]) {
	float numero;

	printf(mensaje);
	scanf("%f", &numero);

	return numero;
}
