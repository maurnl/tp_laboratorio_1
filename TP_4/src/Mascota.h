/*
 * Mascota.h
 *
 *  Created on: 18 jun. 2022
 *      Author: Mauro
 */
#include "LinkedList.h"
#ifndef MASCOTA_H_
#define MASCOTA_H_

typedef struct{
	int id;
	char nombre[25];
	char apellidoDuenio[25];
	int edad;
	int vacunasAplicadas;
	int estaEsterilizado;
	int costoTratamiento;
}Mascota;

#endif /* MASCOTA_H_ */

Mascota* Mascota_new();
Mascota* Mascota_newParametros(int id, char* nombre,char* apellidoDuenio,int edad,int vacunasAplicadas,int estaEsterilizado,int costoTratamiento);
void Mascota_delete(Mascota* this);

int Mascota_setId(Mascota* this, int id);
int Mascota_getId(Mascota* this, int* id);

int Mascota_setNombre(Mascota* this, char* nombre);
int Mascota_getNombre(Mascota* this, char* nombre);

int Mascota_setApellidoDuenio(Mascota* this, char* apellidoDuenio);
int Mascota_getApellidoDuenio(Mascota* this, char* apellidoDuenio);

int Mascota_setEdad(Mascota* this, int edad);
int Mascota_getEdad(Mascota* this, int* edad);

int Mascota_setVacunasAplicadas(Mascota* this, int vacunasAplicadas);
int Mascota_getVacunasAplicadas(Mascota* this, int* vacunasAplicadas);

int Mascota_setEstaEsterilizado(Mascota* this, int estaEsterilizado);
int Mascota_getEstaEsterilizado(Mascota* this, int* estaEsterilizado);

int Mascota_setCostoTratamiento(Mascota* this, int costoTratamiento);
int Mascota_getCostoTratamiento(Mascota* this, int* costoTratamiento);

int Mascota_mostrarMascota(Mascota* this);
int Mascota_getIndexById(LinkedList* pArrayListMascota, int id);
int Mascota_compareById(void* arg1, void* arg2);
int Mascota_compareByName(void* arg1, void* arg2);
void Mascota_mapCosto(void* arg);

int Mascota_filtrarPorEsterilizado(void* arg);
int Mascota_filtrarPorTodasLasVacunas(void* arg);
int Mascota_filtrarPorCostoAlto(void* arg);
