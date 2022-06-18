/*
 * Mascota.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Mauro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Mascota.h"
#include "utn.h"

Mascota* Mascota_new(){
	Mascota* mascotaBuff=NULL;
	mascotaBuff=(Mascota*) malloc(sizeof(Mascota));
	if ( mascotaBuff==NULL
	||Mascota_setId(mascotaBuff, 0)
	||Mascota_setCostoTratamiento(mascotaBuff, 0)
	||Mascota_setNombre(mascotaBuff, " ")
	||Mascota_setApellidoDuenio(mascotaBuff, " ")
	||Mascota_setEdad(mascotaBuff, 0)
	||Mascota_setVacunasAplicadas(mascotaBuff, 0)
	||Mascota_setEstaEsterilizado(mascotaBuff, 0))
	{
		Mascota_delete(mascotaBuff);
		mascotaBuff=NULL;
	}
	return mascotaBuff;
}

Mascota* Mascota_newParametros(int id, char* nombre,char* apellidoDuenio,int edad,int vacunasAplicadas,int estaEsterilizado,int costoTratamiento){
	Mascota* mascotaBuff=NULL;
	mascotaBuff=Mascota_new();
	if(	Mascota_setId(mascotaBuff, id)
		||Mascota_setNombre(mascotaBuff,nombre)
		||Mascota_setApellidoDuenio(mascotaBuff, apellidoDuenio)
		||Mascota_setEdad(mascotaBuff, edad)
		||Mascota_setVacunasAplicadas(mascotaBuff, vacunasAplicadas)
		||Mascota_setCostoTratamiento(mascotaBuff, costoTratamiento)
		||Mascota_setEstaEsterilizado(mascotaBuff, estaEsterilizado))
	{
		Mascota_delete(mascotaBuff);
		mascotaBuff=NULL;
	}
	return mascotaBuff;
}

void Mascota_delete(Mascota* this){
	if(this!=NULL){
		free(this);
	}
}

int Mascota_mostrarMascota(Mascota* this){
	int retorno=-1;
	int id;
	int costoTratamiento;
	char nombre[25];
	char apellidoDuenio[25];
	int edad;
	int vacunasAplicadas;
	int estaEsterilizado;
	if(this!=NULL){
		Mascota_getId(this, &id);
		printf("%-4d\t\t", id);
		Mascota_getNombre(this, nombre);
		printf("%-12s\t\t", nombre);
		Mascota_getApellidoDuenio(this, apellidoDuenio);
		printf("%-16s\t\t", apellidoDuenio);
		Mascota_getEdad(this, &edad);
		printf("%-3d\t\t", edad);
		Mascota_getVacunasAplicadas(this, &vacunasAplicadas);
		printf("%d de 3\t\t", vacunasAplicadas);
		Mascota_getEstaEsterilizado(this, &estaEsterilizado);
		if(estaEsterilizado){
			printf("Si\t\t");
		} else {
			printf("No\t\t");
		}
		Mascota_getCostoTratamiento(this, &costoTratamiento);
		printf("$%-8d\t\t\n", costoTratamiento);
		retorno=0;
	}
	return retorno;
}

int Mascota_getIndexById(LinkedList* pArrayListMascota, int id){
	int retorno=-1;
	int idAux;
	if(pArrayListMascota!=NULL&&id>0){
		for(int i=0;i<ll_len(pArrayListMascota);i++){
			Mascota_getId(ll_get(pArrayListMascota, i), &idAux);
			if(idAux==id){
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

int Mascota_setId(Mascota* this, int id){
	int retorno=-1;
	if(this!=NULL&&id>=0&&id<9999){
		this->id=id;
		retorno=0;
	}
	return retorno;
}
int Mascota_getId(Mascota* this, int* id){
	int retorno=-1;
	if(this!=NULL&&id!=NULL){
		*id=this->id;
		retorno=0;
	}
	return retorno;
}

int Mascota_setCostoTratamiento(Mascota* this, int costoTratamiento){
	int retorno=-1;
	if(this!=NULL&&costoTratamiento>-1){
		this->costoTratamiento=costoTratamiento;
		retorno=0;
	}
	return retorno;
}
int Mascota_getCostoTratamiento(Mascota* this, int* costoTratamiento){
	int retorno=-1;
	if(this!=NULL&&costoTratamiento!=NULL){
		*costoTratamiento=this->costoTratamiento;
		retorno=0;
	}
	return retorno;
}

int Mascota_setNombre(Mascota* this, char* nombre){
	int retorno=-1;
	if(this!=NULL&&nombre!=NULL){
		strcpy(this->nombre, nombre);
		retorno=0;
	}
	return retorno;
}
int Mascota_getNombre(Mascota* this, char* nombre){
	int retorno=-1;
	if(this!=NULL&&nombre!=NULL){
		strcpy(nombre, this->nombre);
		retorno=0;
	}
	return retorno;
}

int Mascota_setApellidoDuenio(Mascota* this, char* apellidoDuenio){
	int retorno=-1;
	if(this!=NULL&&apellidoDuenio!=NULL){
		strcpy(this->apellidoDuenio, apellidoDuenio);
		retorno=0;
	}
	return retorno;
}
int Mascota_getApellidoDuenio(Mascota* this, char* apellidoDuenio){
	int retorno=-1;
	if(this!=NULL&&apellidoDuenio!=NULL){
		strcpy(apellidoDuenio, this->apellidoDuenio);
		retorno=0;
	}
	return retorno;
}

int Mascota_setEdad(Mascota* this, int edad){
	int retorno=-1;
	if(this!=NULL&&edad>=0&&edad<150){
		this->edad=edad;
		retorno=0;
	}
	return retorno;
}
int Mascota_getEdad(Mascota* this, int* edad){
	int retorno=-1;
	if(this!=NULL&&edad!=NULL){
		*edad=this->edad;
		retorno=0;
	}
	return retorno;
}

int Mascota_setVacunasAplicadas(Mascota* this, int vacunasAplicadas){
	int retorno=-1;
	if(this!=NULL&&vacunasAplicadas>=0&&vacunasAplicadas<4){
		this->vacunasAplicadas=vacunasAplicadas;
		retorno=0;
	}
	return retorno;
}
int Mascota_getVacunasAplicadas(Mascota* this, int* vacunasAplicadas){
	int retorno=-1;
	if(this!=NULL&&vacunasAplicadas!=NULL){
		*vacunasAplicadas=this->vacunasAplicadas;
		retorno=0;
	}
	return retorno;
}

int Mascota_setEstaEsterilizado(Mascota* this, int estaEsterilizado){
	int retorno=-1;
	if(this!=NULL&&(estaEsterilizado==1||estaEsterilizado==0)){
		this->estaEsterilizado=estaEsterilizado;
		retorno=0;
	}
	return retorno;
}
int Mascota_getEstaEsterilizado(Mascota* this, int* estaEsterilizado){
	int retorno=-1;
	if(this!=NULL&&estaEsterilizado!=NULL){
		*estaEsterilizado=this->estaEsterilizado;
		retorno=0;
	}
	return retorno;
}

int Mascota_compareById(void* arg1, void* arg2){
	int retorno=0;
	int idArg1, idArg2;
	if(arg1!=NULL&&arg2!=NULL){
		Mascota_getId((Mascota*)arg1, &idArg1);
		Mascota_getId((Mascota*)arg2, &idArg2);
		if(idArg1>idArg2){
			retorno=1;
		} else if(idArg1<idArg2){
			retorno=-1;
		}
	}
	return retorno;
}

int Mascota_compareByName(void* arg1, void* arg2){
	int retorno=0;
	char nombre1[50], nombre2[50];
	if(arg1!=NULL&&arg2!=NULL){
		Mascota_getNombre((Mascota*)arg1, nombre1);
		Mascota_getNombre((Mascota*)arg2, nombre2);
		if(strncmp(nombre2,nombre1,4)<0){
			retorno=1;
		} else if(strncmp(nombre2,nombre1,4)>0){
			retorno=-1;
		}
	}
	return retorno;
}

void Mascota_mapCosto(void* arg){
	Mascota* this=(Mascota*)arg;
	this->costoTratamiento=this->vacunasAplicadas*2500 + this->estaEsterilizado*4000;
}

int Mascota_filtrarPorEsterilizado(void* arg){
	int retorno=-1;
	if(arg!=NULL){
		retorno=0;
		if(((Mascota*)arg)->estaEsterilizado)
			retorno=1;
	}
	return retorno;
}

int Mascota_filtrarPorTodasLasVacunas(void* arg){
	int retorno=-1;
	if(arg!=NULL){
		retorno=0;
		if(((Mascota*)arg)->vacunasAplicadas>2)
			retorno=1;
	}
	return retorno;
}

int Mascota_filtrarPorCostoAlto(void* arg){
	int retorno=-1;
	if(arg!=NULL){
		retorno=0;
		if(((Mascota*)arg)->costoTratamiento>10000)
			retorno=1;
	}
	return retorno;
}
