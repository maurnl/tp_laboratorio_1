/*
 * utn.c
 *
 *  Created on: 4 jun. 2022
 *      Author: Mauro
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int confirm(char mensaje[]) {
	int retorno;
	char respuesta;
	retorno = -1;
	if(mensaje!= NULL) {
		printf("%s \n", mensaje);
		fflush(stdin);
		respuesta = getchar();
		respuesta = toupper(respuesta);
		while((respuesta != 'S') && (respuesta != 'N') && (respuesta != '\n')) {
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

int stringIsInt(char string[]){
	int retorno=1;
	int i;
	if(string!=NULL){
		for(i=0;i<strlen(string)-1;i++){
			if(isdigit(string[i])==0){
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

int getPositiveInt(char mensaje[], int* resultado, int min, int max) {
	char buffer[9];
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
			if(!stringIsInt(buffer)){
				flagError=1;
			} else {
				numero=atoi(buffer);
			}
		}while(flagError==1 || (numero<min || numero>max));
		retorno=0;
		*resultado = numero;
	}
	return retorno;
}

int stringIsFloat(char string[]){
	int retorno=1;
	int i;
	int dot=0;
	if(string!=NULL){
		for(i=0;i<strlen(string)-1;i++){
			if(isdigit(string[i])==0){
				if(string[i]=='.'&&dot<1){
					dot++;
				} else {
					retorno=0;
					break;
				}
			}
		}
	}
	return retorno;
}

int getPositiveFloat(char mensaje[], float* resultado, float min, float max) {
	char buffer[9];
	int flagError;
	int retorno;
	float numero;
	retorno = -1;
	if(resultado != NULL && mensaje != NULL) {
		do {
			flagError=0;
			printf("%s \n", mensaje);
			fflush(stdin);
			fgets(buffer,9,stdin);
			if(!stringIsFloat(buffer)){
				flagError=1;
			} else {
				numero=atof(buffer);
			}
		}while(flagError==1 || (numero<min || numero>max));
		retorno=0;
		*resultado = numero;
	}
	return retorno;
}

int stringIsAlphabetic(char string[]){
	int retorno=1;
	int i;
	if(string!=NULL){
		for(i=0;i<strlen(string)-1;i++){
			if(isalpha(string[i])==0 && string[i]!=' '){
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

int getAlphabeticText(char mensaje[], char destino[], int len) {
	int retorno;
	int flagError;
	retorno=-1;
	if(mensaje!=NULL && destino!=NULL && len>0) {
		do {
			flagError=0;
			printf("%s \n", mensaje);
			fflush(stdin);
			fgets(destino,len,stdin);
			if(!stringIsAlphabetic(destino)){
				flagError=1;
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

int stringIsPath(char string[]){
	int retorno=1;
	int i;
	if(string!=NULL){
		for(i=0;i<strlen(string);i++){
			if(string[i]==' '){
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

int stringToUpper(char* string, int qty){
	int retorno=-1;
	int i;
	if(string!=NULL&&qty>0&&qty<strlen(string)){
		for(i=0;i<qty;i++){
			*(string+i)=toupper(*(string+i));
		}
		retorno=0;
	}
	return retorno;
}
