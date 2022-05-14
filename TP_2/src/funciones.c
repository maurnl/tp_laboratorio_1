/*
 * funciones.c
 *
 *  Created on: 29 abr. 2022
 *      Author: Mauro
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayPassenger.h"

int getPositiveFloat(char mensaje[], float* resultado, float max) {
	char floatBuffer[16];
	char floatAux[16];
	int retorno;
	float numero;
	int i;
	int indiceBuffer;
	int indiceAux;
	int flagPunto;
	int indicePunto;
	int contadorPunto;
	retorno = -1;
	if(resultado != NULL && mensaje != NULL) {
			do {
				flagPunto=0;
				contadorPunto=0;
				indicePunto=0;
				indiceBuffer=0;
				indiceAux=0;
				for(i=0;i<16;i++){
					floatBuffer[i]=0;
					floatAux[i]=0;
				}
				printf("%s \n", mensaje);
				fflush(stdin);
				fgets(floatBuffer, 16, stdin);
				do {
					if(isdigit(floatBuffer[indiceBuffer])){
						floatAux[indiceAux] = floatBuffer[indiceBuffer];
						indiceBuffer++;
						indiceAux++;
					} else {
						if(floatBuffer[indiceBuffer]=='.' && flagPunto==0){
							indicePunto = indiceBuffer;
							flagPunto = 1;
							indiceBuffer++;
							contadorPunto++;
						} else {
							contadorPunto++;
							indiceBuffer++;
						}
					}
				}while(indiceBuffer<16 && floatBuffer[indiceBuffer]!='\n');
				if(contadorPunto==1) {
					indicePunto = indiceBuffer - indicePunto;
					numero = atof(floatAux);
					for(i=0;i<indicePunto-1;i++) {
						numero=numero/10;
					}
					*resultado = numero;
				} else {
					numero=atof(floatAux);
					*resultado = numero;
				}
				retorno = 0;
			}while(contadorPunto>1 || numero>max);
	}
	return retorno;
}


int getPositiveInt(char mensaje[], int* resultado, int max) {
	char buffer[9];
	int i;
	int flagError;
	int retorno;
	int numero;
	retorno = -1;
	if(resultado != NULL && mensaje != NULL) {
		do {
			flagError=0;
			printf("%s \n", mensaje);
			fflush(stdin);
			fgets(buffer,9,stdin);
			for(i=0;i<strlen(buffer)-1;i++){
				if(isalpha(buffer[i])){
					flagError=1;
					break;
				}
			}
		}while(flagError==1);
		numero = atoi(buffer);
		retorno = 0;
		*resultado = numero;
	}
	return retorno;
}

int confirm(char mensaje[]) {
	int retorno;
	char respuesta;
	retorno = -1;
	if(mensaje!= NULL) {
		printf("%s \n", mensaje);
		fflush(stdin);
		respuesta = getchar();
		respuesta = toupper(respuesta);
		while((respuesta != 'S') & (respuesta != 'N') & (respuesta != '\n')) {
			printf("%s \n", mensaje);
			fflush(stdin);
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

int getAlphabeticText(char mensaje[], char destino[], int len) {
	int retorno;
	int i;
	int flagError;
	retorno=-1;
	if(mensaje!=NULL && destino!=NULL && len>0) {
		do {
			flagError=0;
			printf("%s \n", mensaje);
			fflush(stdin);
			fgets(destino,len,stdin);
			for(i=0;i<strlen(destino)-1;i++){
				if(isalpha(destino[i])==0){
					flagError=1;
					break;
				}
			}
		}while(flagError==1);
		destino[strlen(destino)-1]='\0';
		retorno=0;
	}
	return retorno;
}

int getAlphanumericText(char mensaje[], char destino[], int len) {
	int retorno;
	retorno=-1;
	if(mensaje!=NULL && destino!=NULL && len>0) {
		printf("%s \n", mensaje);
		fflush(stdin);
		fgets(destino,len,stdin);
		destino[strlen(destino)-1]='\0';
		retorno=0;
	}

	return retorno;
}
