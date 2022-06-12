/*
 * Passenger.c
 *
 *  Created on: 19 may. 2022
 *      Author: Maru
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Passenger.h"
#include "utn.h"

Passenger* Passenger_new(){
	Passenger* passengerBuff=NULL;
	passengerBuff=(Passenger*) malloc(sizeof(Passenger));
	if(passengerBuff==NULL){
		exit(1);
	}
	if ( Passenger_setId(passengerBuff, 0)
	||Passenger_setNombre(passengerBuff, " ")
	||Passenger_setApellido(passengerBuff, " ")
	||Passenger_setPrecio(passengerBuff, 1.0)
	||Passenger_setTipoPasajero(passengerBuff, 1)
	||Passenger_setCodigoVuelo(passengerBuff, " ")
	||Passenger_setEstadoVuelo(passengerBuff, " ")
	||Passenger_setIsEmpty(passengerBuff, 1) )
	{
		Passenger_delete(passengerBuff);
		passengerBuff=NULL;
	}
	return passengerBuff;
}

Passenger* Passenger_newParametros(int id,char* nombre,char* apellido,float precio,int tipoPasajero,char* codigoVuelo,char* estadoVuelo){
	Passenger* passengerBuff=NULL;
	passengerBuff=Passenger_new();
	if(	Passenger_setId(passengerBuff, id)
		||Passenger_setNombre(passengerBuff, nombre)
		||Passenger_setApellido(passengerBuff, apellido)
		||Passenger_setPrecio(passengerBuff, precio)
		||Passenger_setTipoPasajero(passengerBuff, tipoPasajero)
		||Passenger_setCodigoVuelo(passengerBuff, codigoVuelo)
		||Passenger_setEstadoVuelo(passengerBuff, estadoVuelo)
		||Passenger_setIsEmpty(passengerBuff, 0))
	{
		Passenger_delete(passengerBuff);
		passengerBuff=NULL;
	}
	return passengerBuff;
}

void Passenger_delete(Passenger* this){
	if(this!=NULL){
		free(this);
	}
}

void Passenger_printHeader(int qty){
	printf("PASAJEROS EN SISTEMA: %d\n", qty);
	printf("ID              APELLIDO                NOMBRE                  PRECIO                  TIPO            CODIGO                  ESTADO\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int Passenger_mostrarPasajero(Passenger* this){
	int retorno=-1;
	int id;
	char codigo[9];
	char nombre[50];
	char apellido[50];
	float precio;
	char tipo[25];
	char estado[25];
	if(this!=NULL){
		Passenger_getId(this, &id);
		printf("%-4d\t\t", id);
		Passenger_getApellido(this, apellido);
		printf("%-12s\t\t", apellido);
		Passenger_getNombre(this, nombre);
		printf("%-12s\t\t", nombre);
		Passenger_getPrecio(this, &precio);
		printf("%-8.2f\t\t", precio);
		Passenger_getTipoPasajeroStr(this, tipo);
		printf("%-10s\t\t", tipo);
		Passenger_getCodigoVuelo(this, codigo);
		printf("%-9s\t\t", codigo);
		Passenger_getEstadoVuelo(this, estado);
		printf("%-8s\t\t\n", estado);
		retorno=0;
	}
	return retorno;
}

int Passenger_getPassengerById(LinkedList* pArrayListPassenger, int id){
	int retorno=-1;
	Passenger* pasajero=NULL;
	int idAux;
	if(pArrayListPassenger!=NULL&&id>0){
		retorno=0;
		for(int i=0;i<ll_len(pArrayListPassenger);i++){
			pasajero=ll_get(pArrayListPassenger, i);
			Passenger_getId(pasajero, &idAux);
			if(pasajero==NULL){
				retorno=-1;
				break;
			} else if(idAux == id){
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

// -----

int Passenger_setId(Passenger* this,int id){
	int retorno=-1;
	if(this!=NULL&&id>=0&&id<9999){
		this->id=id;
		retorno=0;
	}
	return retorno;
}
int Passenger_getId(Passenger* this,int* id){
	int retorno=-1;
	if(this!=NULL){
		*id=this->id;
	}
	return retorno;
}

int Passenger_setNombre(Passenger* this,char* nombre){
	int retorno=-1;
	if(this!=NULL&&nombre!=NULL){
		strcpy(this->nombre, nombre);
		retorno=0;
	}
	return retorno;
}
int Passenger_getNombre(Passenger* this,char* nombre)
{
	int retorno=-1;
	if(this!=NULL&&nombre!=NULL){
		strcpy(nombre, this->nombre);
		retorno=0;
	}
	return retorno;
}

int Passenger_setApellido(Passenger* this,char* apellido){
	int retorno=-1;
	if(this!=NULL&&apellido!=NULL){
		stringToUpper(apellido, 1);
		strcpy(this->apellido, apellido);
		retorno=0;
	}
	return retorno;
}
int Passenger_getApellido(Passenger* this,char* apellido){
	int retorno=-1;
	if(this!=NULL&&apellido!=NULL){
		strcpy(apellido, this->apellido);
		retorno=0;
	}
	return retorno;
}

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo){
	int retorno=-1;
	if(this!=NULL&&codigoVuelo!=NULL){
		strcpy(this->codigoVuelo, codigoVuelo);
		retorno=0;
	}
	return retorno;
}
int Passenger_getCodigoVuelo(Passenger* this,char* codigoVuelo){
	int retorno=-1;
	if(this!=NULL&&codigoVuelo!=NULL){
		strcpy(codigoVuelo, this->codigoVuelo);
		retorno=0;
	}
	return retorno;
}

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero){
	int retorno=-1;
	if(this!=NULL&&tipoPasajero>0){
		this->tipoPasajero=tipoPasajero;
		retorno=0;
	}
	return retorno;
}

int Passenger_setTipoPasajeroStr(Passenger* this,char* tipoPasajero){
	int retorno=-1;
	if(this!=NULL&&tipoPasajero!=NULL){
		if(strcmp(tipoPasajero, "FirstClass")==0){
			this->tipoPasajero=1;
			retorno=0;
		} else if(strcmp(tipoPasajero, "ExecutiveClass")==0){
			this->tipoPasajero=2;
			retorno=0;
		} else if(strcmp(tipoPasajero, "EconomyClass")==0){
			this->tipoPasajero=3;
			retorno=0;
		}
	}
	return retorno;
}

int Passenger_getTipoPasajeroStr(Passenger* this, char* tipoPasajero){
	int retorno=-1;
	if(this!=NULL&&tipoPasajero!=NULL){
		switch(this->tipoPasajero){
		case 1:
			strcpy(tipoPasajero,"FirstClass");
			break;
		case 2:
			strcpy(tipoPasajero,"ExecutiveClass");
			break;
		case 3:
			strcpy(tipoPasajero,"EconomyClass");
			break;
		}
	}
	return retorno;
}

int Passenger_getTipoPasajero(Passenger* this,int* tipoPasajero){
	int retorno=-1;
	if(this!=NULL){
		*tipoPasajero=this->tipoPasajero;
		retorno=0;
	}
	return retorno;
}

int Passenger_setPrecio(Passenger* this,float precio){
	int retorno=-1;
	if(this!=NULL&&precio>0&&precio<350000){
		this->precio=precio;
		retorno=0;
	}
	return retorno;
}
int Passenger_getPrecio(Passenger* this,float* precio){
	int retorno=-1;
	if(this!=NULL){
		*precio=this->precio;
		retorno=0;
	}
	return retorno;
}

int Passenger_setEstadoVuelo(Passenger* this,char* estado){
	int retorno=-1;
	if(this!=NULL&&estado!=NULL){
		strcpy(this->estadoVuelo, estado);
		retorno=0;
	}
	return retorno;
}
int Passenger_getEstadoVuelo(Passenger* this,char* estado){
	int retorno=-1;
	if(this!=NULL&&estado!=NULL){
		strcpy(estado, this->estadoVuelo);
		retorno=0;
	}
	return retorno;
}

int Passenger_setIsEmpty(Passenger* this,int estado){
	int retorno=-1;
	if(this!=NULL&&(estado==1 || estado==0)){
		this->isEmpty=estado;
		retorno=0;
	}
	return retorno;
}
int Passenger_getIsEmpty(Passenger* this){
	int retorno=-1;
	if(this!=NULL){
		retorno=this->isEmpty;
	}
	return retorno;
}

int Passenger_sortById(void* arg1, void* arg2){
	int retorno=0;
	int idArg1, idArg2;
	if(arg1!=NULL&&arg2!=NULL){
		Passenger_getId((Passenger*)arg1, &idArg1);
		Passenger_getId((Passenger*)arg2, &idArg2);
		if(idArg1>idArg2){
			retorno=1;
		} else if(idArg1<idArg2){
			retorno=-1;
		}
	}
	return retorno;
}

int Passenger_sortByLastName(void* arg1, void* arg2){
	int retorno=0;
	char apellido1[50], apellido2[50];
	if(arg1!=NULL&&arg2!=NULL){
		Passenger_getApellido((Passenger*)arg1, apellido1);
		Passenger_getApellido((Passenger*)arg2, apellido2);
		if(strncmp(apellido2,apellido1,4)<0){
			retorno=1;
		} else if(strncmp(apellido2,apellido1,4)>0){
			retorno=-1;
		}
	}
	return retorno;
}
