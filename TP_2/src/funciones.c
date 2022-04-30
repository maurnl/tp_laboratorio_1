/*
 * funciones.c
 *
 *  Created on: 29 abr. 2022
 *      Author: Mauro
 */
#include <stdio.h>
#include <stdlib.h>

int preguntar(char mensaje[]) {
	int retorno;
	char respuesta;
	retorno = -1;
	if(mensaje!= NULL) {
		respuesta = getchar();
		respuesta = toupper(respuesta);
		while((respuesta != 'S') & (respuesta != 'N')) {
			puts(mensaje);
			respuesta = getchar();
			respuesta = toupper(respuesta);
		}

		if (respuesta == 'S') {
			retorno = 1;
		} else {
			retorno = 0;
		}
	}

	return retorno;
}

float pedirFloatPositivo(char mensaje[], float* resultado) {
	int retorno;
	float numero;
	retorno = -1;
	if(resultado != NULL && mensaje != NULL) {
		printf(mensaje);
		scanf("%f", &numero);
		while(numero < 0) {
			printf("Numero no válido.\n");
			printf(mensaje);
			scanf("%f", &numero);
		}
		retorno = 0;
		*resultado = numero;
	}
	return retorno;
}

int pedirIntPositivo(char mensaje[], int* resultado) {
	int retorno;
	int numero;
	retorno = -1;
	if(resultado != NULL && mensaje != NULL) {
		printf(mensaje);
		scanf("%d", &numero);
		while(numero < 0) {
			printf("Numero no válido.\n");
			printf(mensaje);
			scanf("%d", &numero);
		}
		retorno = 0;
		*resultado = numero;
	}
	return retorno;
}
