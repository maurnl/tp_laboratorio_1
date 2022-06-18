#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Mascota.h"
#include "menu.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de las mascotas desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int parser_MascotaFromText(FILE* pArchivo, LinkedList* pArrayListMascotas)
{
	int retorno=0;
	int leido;
	char buffers[7][50];
	char fantasma[50];
	Mascota* mascotaBuff=NULL;
	// Lectura fantasma
	fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", fantasma, fantasma, fantasma, fantasma, fantasma, fantasma, fantasma);
	while(!feof(pArchivo)){
		leido=fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffers[0], buffers[1], buffers[2], buffers[3], buffers[4], buffers[5], buffers[6]);
		if(leido==7){
			mascotaBuff=Mascota_newParametros(atoi(buffers[0]),buffers[1],buffers[2],atoi(buffers[3]),atoi(buffers[4]),atoi(buffers[5]), atoi(buffers[6]));
			if(mascotaBuff!=NULL){
				ll_add(pArrayListMascotas, mascotaBuff);
			}
		} else if(!feof(pArchivo)){
			retorno=-1;
			break;
		}
	}
    return retorno;
}

/** \brief Parsea los datos de las mascotas desde el archivo 'path' (modo binario).
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int parser_MascotaFromBinary(FILE* pArchivo , LinkedList* pArrayListMascotas)
{
	int retorno=-1;
	int leido;
	Mascota mascotaLectura;
	Mascota* mascotaBuff=NULL;
	while(!feof(pArchivo)){
		leido=fread(&mascotaLectura, sizeof(mascotaLectura), 1, pArchivo);
		if(leido==1){
			mascotaBuff=Mascota_newParametros(mascotaLectura.id,mascotaLectura.nombre, mascotaLectura.apellidoDuenio, mascotaLectura.edad, mascotaLectura.vacunasAplicadas, mascotaLectura.estaEsterilizado, mascotaLectura.costoTratamiento);
			if(mascotaBuff!=NULL){
				ll_add(pArrayListMascotas, mascotaBuff);
			}
		} else if(feof(pArchivo)){
			retorno=0;
			break;
		} else {
			break;
		}
	}
    return retorno;
}
/**
 * @brief Guarda los datos de una lista de mascotas en modo binario
 * @param pArchivo Puntero a archivo
 * @param pArrayListMascotas LinkedList*
 * @return
 */
int parser_saveMascotasAsBinary(FILE* pArchivo, LinkedList* pArrayListMascotas){
	int retorno=0;
	int escrito;
	Mascota* mascotaAux=NULL;
	for(int i=0;i<ll_len(pArrayListMascotas);i++){
		mascotaAux=ll_get(pArrayListMascotas, i);
		escrito=fwrite(mascotaAux, sizeof(Mascota), 1, pArchivo);
		if(escrito<1){
			retorno=-1;
			break;
		}
	}
	return retorno;
}

/**
 * @brief Guarda los datos de una lista de mascotas en modo texto
 * @param pArchivo Puntero a archivo
 * @param pArrayListMascotas LinkedList*
 * @return
 */
int parser_saveMascotasAsText(FILE* pArchivo, LinkedList* pArrayListMascotas){
	int retorno=0;
	Mascota* mascotaAux=NULL;
	int idAux, edadAux, vacunasAux, esterilizadoAux, costoAux;
	char nombreAux[25], apellidoDuenioAux[25];
	fprintf(pArchivo, "id,nombre,apellidoDuenio,edad,vacunasAplicadas,estaEsterilizado,costoTratamiento\n");
	for(int i=0;i<ll_len(pArrayListMascotas);i++){
		mascotaAux=ll_get(pArrayListMascotas, i);
		if(mascotaAux!=NULL){
			Mascota_getId(mascotaAux, &idAux);
			Mascota_getNombre(mascotaAux, nombreAux);
			Mascota_getEdad(mascotaAux, &edadAux);
			Mascota_getVacunasAplicadas(mascotaAux, &vacunasAux);
			Mascota_getEstaEsterilizado(mascotaAux, &esterilizadoAux);
			Mascota_getCostoTratamiento(mascotaAux, &costoAux);
			fprintf(pArchivo, "%d,%s,%s,%d,%d,%d,%d\n", idAux, nombreAux, apellidoDuenioAux, edadAux,vacunasAux, esterilizadoAux, costoAux);
		}  else {
			retorno=-1;
			break;
		}
	}
	return retorno;
}
