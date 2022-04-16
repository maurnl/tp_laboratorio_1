/*
 * funciones.c
 *
 *  Created on: 1 abr. 2022
 *      Author: Mauro
 */
#define PRECIO_BTC 4538021.05
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

float aplicarPorcentaje(float precioBase, float porcentaje, float* resultado) {
	int retorno=-1;

	if(precioBase > 0) {
		*resultado = precioBase + ((precioBase * porcentaje) / 100);
		retorno=1;
	}

	return retorno;
}

float pesoABtc(float precio, float* resultado) {
	int retorno=-1;

	if(precio>0) {
		*resultado = precio / PRECIO_BTC;
		retorno=1;
	}

	return retorno;
}

float precioUnitario(float precioTotal, float unidades, float* resultado) {
	int retorno=-1;

	if(precioTotal > 0 && unidades > 0) {
		*resultado = precioTotal / unidades;
		retorno = 1;
	}

	return retorno;
}

float pedirFloat(char mensaje[]) {
	float numero;

	printf(mensaje);
	scanf("%f", &numero);
	while(numero < 0) {
		printf("Numero no válido.\n");
		printf(mensaje);
		scanf("%f", &numero);
	}

	return numero;
}
