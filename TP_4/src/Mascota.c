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

/**
 * Retorna un puntero a una nueva entidad Mascota en memoria dinamica
 * @return NULL si no hay memoria disponible o Mascota* Puntero a Mascota si funciono
 */
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
/**
 * Retorna un puntero a una nueva entidad Mascota en memoria dinamica
 * @param id int
 * @param nombre char*
 * @param apellidoDuenio char*
 * @param edad int
 * @param vacunasAplicadas int
 * @param estaEsterilizado int
 * @param costoTratamiento int
 * @return NULL si no hay memoria disponible o Mascota* Puntero a Mascota si funciono
 */
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
/**
 * Libera la memoria ocupada por un puntero a estructura Mascota en memoria dinamica
 * @param this Mascota* puntero a mascota
 */
void Mascota_delete(Mascota* this){
	if(this!=NULL){
		free(this);
	}
}
/**
 * Muesta la informacion de una mascota
 * @param this Mascota* puntero a mascota
 * @return -1 si puntero NULL o 0 si funciono
 */
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
/**
 * Busca una mascota por id y retorna el indice donde se encuentra
 * @param pArrayListMascota LinkedList* puntero a LinkedList
 * @param id int id a buscar
 * @return -1 si puntero a NULL o el indice si funciono
 */
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
/**
 * Funcion criterio. Compara dos mascotas por id
 * @param arg1 void*
 * @param arg2 void*
 * @return 0 si error (punteros NULL) o 1 si id de arg1 es mayor que id de arg2 o -1 si id de arg2 es mayor que id de arg1
 */
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
/**
 * Funcion criterio. Compara dos mascotas por nombre
 * @param arg1 void*
 * @param arg2 void*
 * @return 0 si error (punteros NULL) o 1 si nombre de arg1 es mayor que nombre de arg2 o -1 si nombre de arg2 es mayor que nombre de arg1
 */
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
/**
 * Funcion map. Calcula el campo costoTratamiento de Mascota
 * @param arg Mascota*
 */
void Mascota_mapCosto(void* arg){
	Mascota* this=(Mascota*)arg;
	int vacunas, esterilizado;
	Mascota_getVacunasAplicadas(this, &vacunas);
	Mascota_getEstaEsterilizado(this, &esterilizado);
	Mascota_setCostoTratamiento(this, vacunas*2500 + esterilizado*4000);
}
/**
 * Funcion filtro. Campo estaEsterilizado=1
 * @param arg Mascota*
 * @return 0 si puntero NULL o -1 si no cumple criterio o 1 si cumple criterio
 */
int Mascota_filtrarPorEsterilizado(void* arg){
	int retorno=-1;
	int esterilizado;
	if(arg!=NULL){
		retorno=0;
		Mascota_getEstaEsterilizado((Mascota*)arg, &esterilizado);
		if(esterilizado)
			retorno=1;
	}
	return retorno;
}
/**
 * Funcion filtro. Campo vacunasAplicadas>2
 * @param arg Mascota*
 * @return 0 si puntero NULL o -1 si no cumple criterio o 1 si cumple criterio
 */
int Mascota_filtrarPorTodasLasVacunas(void* arg){
	int retorno=-1;
	int vacunas;
	if(arg!=NULL){
		retorno=0;
		Mascota_getVacunasAplicadas((Mascota*)arg, &vacunas);
		if(vacunas>2)
			retorno=1;
	}
	return retorno;
}
/**
 * Funcion filtro. Campo costoTratamiento>10000
 * @param arg Mascota*
 * @return 0 si puntero NULL o -1 si no cumple criterio o 1 si cumple criterio
 */
int Mascota_filtrarPorCostoAlto(void* arg){
	int retorno=-1;
	int costo;
	if(arg!=NULL){
		retorno=0;
		Mascota_getCostoTratamiento((Mascota*)arg, &costo);
		if(costo>10000)
			retorno=1;
	}
	return retorno;
}
