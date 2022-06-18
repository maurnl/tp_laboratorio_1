/*
 * Controller.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Mauro
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "menu.h"
#include "Mascota.h"
#include "parser.h"
#include "utn.h"
/**
 * @brief Obtiene el id máximo de una linkedlist
 * @param LinkedList* pArrayListMascotas
 * @return
 */
int controller_getMaximoId(LinkedList* pArrayListMascotas){
	int retorno=-1;
	int maxId=0;
	int actualId;
	for(int i=0;i<ll_len(pArrayListMascotas);i++){
		Mascota_getId((Mascota*)ll_get(pArrayListMascotas, i), &actualId);
		if(i==0 || maxId<actualId){
			maxId=actualId;
			retorno=maxId;
		}
	}
	return retorno;
}

/**
 * @brief Obtiene el siguiente ID a utilizar para una linkedlist
 * @param LinkedList* pArrayListMascotas
 * @return
 */
int controller_getNextId(LinkedList* pArrayListMascotas){
	int retorno=-1;
	if(pArrayListMascotas!=NULL){
		retorno=1;
		if(!ll_isEmpty(pArrayListMascotas)){
			retorno=controller_getMaximoId(pArrayListMascotas);
			if(retorno!=-1){
				retorno++;
			}
		}
	}
	return retorno;
}

/**
 * @brief Toma los datos de list2 y los agrega al final de list1 respetando el id
 * @param list1 LinkedList* Lista destino
 * @param list2 LinkedList* Lista origen
 * @return
 */
int controller_mergeLinkedList(LinkedList* list1, LinkedList* list2){
	int retorno=-1;
	int nextId;
	Mascota* mascota=NULL;
	if(list1!=NULL&&list2!=NULL){
		nextId=controller_getNextId(list1);
		for(int i=0;i<ll_len(list2);i++){
			mascota=(Mascota*)ll_get(list2, i);
			Mascota_setId(mascota, nextId);
			ll_push(list1, ll_len(list1), mascota);
			nextId++;
		}
		retorno=0;
	}
	return retorno;
}

/** \brief Carga los datos de las mascotas desde el archivo en 'path' (modo texto).
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListMascotas)
{
	int retorno=-2;
	FILE* pArchivo;
	LinkedList* linkedListAux=NULL;
	printf("- INTENTANDO ABRIR ARCHIVO...\n");
	pArchivo=fopen(path,"r");
	if(pArrayListMascotas!=NULL&&stringIsPath(path)&&pArchivo!=NULL){
		printf("- ARCHIVO ENCONTRADO.\n");
		if(ll_isEmpty(pArrayListMascotas)){
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_MascotaFromText(pArchivo, pArrayListMascotas);
		} else if(confirm("- SE DETECTARON MASCOTAS EN EL SISTEMA. DESEA MANTENERLAS (S/N)? (SE GUARDARÁN AL FINAL DEL ARCHIVO CARGADO):")){
			linkedListAux=ll_clone(pArrayListMascotas);
			ll_clear(pArrayListMascotas);
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_MascotaFromText(pArchivo, pArrayListMascotas);
			controller_mergeLinkedList(pArrayListMascotas, linkedListAux);
			ll_deleteLinkedList(linkedListAux);
		} else {
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_MascotaFromText(pArchivo, pArrayListMascotas);
		}
	}
	fclose(pArchivo);
	return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo 'path' (modo binario).
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListMascotas)
{
	int retorno=-2;
	FILE* pArchivo;
	LinkedList* linkedListAux=NULL;
	printf("- INTENTANDO ABRIR ARCHIVO...\n");
	pArchivo=fopen(path,"rb");
	if(pArrayListMascotas!=NULL&&stringIsPath(path)&&pArchivo!=NULL){
		printf("- ARCHIVO ENCONTRADO.\n");
		if(ll_isEmpty(pArrayListMascotas)){
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_MascotaFromBinary(pArchivo, pArrayListMascotas);
		} else if(confirm("- SE DETECTARON MASCOTAS EN EL SISTEMA. DESEA MANTENERLAS (S/N)? (SE GUARDARAN AL FINAL DEL ARCHIVO CARGADO):")){
			linkedListAux=ll_clone(pArrayListMascotas);
			ll_clear(pArrayListMascotas);
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_MascotaFromBinary(pArchivo, pArrayListMascotas);
			controller_mergeLinkedList(pArrayListMascotas, linkedListAux);
			ll_deleteLinkedList(linkedListAux);
		} else {
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_MascotaFromBinary(pArchivo, pArrayListMascotas);
		}
	}
	fclose(pArchivo);
	return retorno;
}

/** \brief Alta de mascotas
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_addMascota(LinkedList* pArrayListMascotas,int* id)
{
	int retorno=-1;
	if(pArrayListMascotas!=NULL&&id!=NULL){
		Mascota* mascotaBuff=NULL;
		char nombreBuff[25];
		char apellidoDuenioBuff[25];
		int edadBuff;
		int vacunasAplicadasBuff;
		int estaEsterilizadoBuff;
		printf("\t\t** CARGA DE MASCOTA **\n");
		retorno=-2;
		if(	!getAlphabeticText("- INGRESE NOMBRE DE LA MASCOTA:", nombreBuff, 25)
			&&!getAlphabeticText("- INGRESE APELLIDO DEL DUENIO:", apellidoDuenioBuff, 25)
			&&!getPositiveInt("- INGRESE EDAD DE LA MASCOTA: ", &edadBuff, 0, 149)
			&&!getPositiveInt("- INGRESE CANT. VACUNAS APLICADAS: ", &vacunasAplicadasBuff, 0,3)
			&&!getPositiveInt("- LA MASCOTA ESTA ESTERILIZADA? \n1. SI\n0. NO: ", &estaEsterilizadoBuff, 0,1) ) {
			mascotaBuff=Mascota_newParametros(*id, nombreBuff, apellidoDuenioBuff, edadBuff, vacunasAplicadasBuff, estaEsterilizadoBuff,0);
			if(mascotaBuff!=NULL){
				ll_add(pArrayListMascotas, mascotaBuff);
				(*id)++;
				retorno=0;
			}
		}
	}
    return retorno;
}

/** \brief Modificar datos de mascota
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_editMascota(LinkedList* pArrayListMascotas)
{
	int retorno=-3;
	Mascota* mascota=NULL;
	int id;
	int indice;
	int subOpcion;
	char nombreBuff[25];
	int edadBuff;
	int vacunasAplicadasBuff;
	int estaEsterilizadoBuff;
	if(pArrayListMascotas!=NULL&&!ll_isEmpty(pArrayListMascotas)){
		printf("\t\t** MODIFICACION DE MASCOTA**\n");
		getPositiveInt("- INGRESE ID A BUSCAR: ", &id, 0, ll_len(pArrayListMascotas));
		indice=Mascota_getIndexById(pArrayListMascotas, id);
		retorno=-2;
		if(indice!=-1){
			mascota=(Mascota*)ll_get(pArrayListMascotas, indice);
			do{
				retorno=Mascota_mostrarMascota(mascota);
				getPositiveInt("- INGRESE DATO A MODIFICAR:\n\t1.NOMBRE\n\t2.EDAD.\n\t3.VACUNAS APLICADAS.\n\t4.ESTADO ESTERILIZACION.\n\t5.SALIR", &subOpcion, 1, 5);
				switch(subOpcion){
				case 1:
					getAlphabeticText("- INGRESE NOMBRE NUEVO: ", nombreBuff, 50);
					Mascota_setNombre(mascota, nombreBuff);
					printf("- MODIFICADO EXISTOSAMENTE.\n");
					break;
				case 2:
					getPositiveInt("- INGRESE EDAD NUEVA: ", &edadBuff, 0,149);
					Mascota_setEdad(mascota, edadBuff);
					printf("- MODIFICADO EXISTOSAMENTE.\n");
					break;
				case 3:
					getPositiveInt("- INGRESE CANT. VACUNAS APLICADAS NUEVA: ", &vacunasAplicadasBuff, 0,3);
					Mascota_setVacunasAplicadas(mascota, vacunasAplicadasBuff);
					printf("- MODIFICADO EXISTOSAMENTE.\n");
					break;
				case 4:
					getPositiveInt("- INGRESE ESTADO ESTERILIZACION NUEVO: \n1. SI\n0. NO", &estaEsterilizadoBuff, 0, 1);
					Mascota_setEstaEsterilizado(mascota, estaEsterilizadoBuff);
					printf("- MODIFICADO EXISTOSAMENTE.\n");
					break;
				case 5:
					break;
				}
				retorno=Mascota_mostrarMascota(mascota);
			}while(confirm("- DESEA MODIFICAR OTRO DATO (S/N)?"));
		}
	}
    return retorno;
}

/** \brief Baja de mascota
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_removeMascota(LinkedList* pArrayListMascotas)
{
	int retorno=-1;
	Mascota* mascota=NULL;
	int id, indice;
	if(pArrayListMascotas!=NULL&&!ll_isEmpty(pArrayListMascotas)){
		printf("\t\t**BAJA DE MASCOTAS**\n");
		do{
			getPositiveInt("- INGRESE ID DE MASCOTA A BUSCAR: ", &id, 0, ll_len(pArrayListMascotas));
			indice=Mascota_getIndexById(pArrayListMascotas, id);
			mascota=(Mascota*)ll_get(pArrayListMascotas, indice);
			if(indice!=-1){
		    	printf("ID              NOMBRE                  APELLIDO DUENIO                 EDAD(ANIOS)     VACUNAS         ESTERILIZADO    COSTO TOTAL\n");
		    	printf("------------------------------------------------------------------------------------------------------------------------------------\n");
				Mascota_mostrarMascota(mascota);
				if(mascota!=NULL&&confirm("- CONFIRME BAJA DE MASCOTA(S/N).")){
					ll_remove(pArrayListMascotas, indice);
					retorno=0;
					printf("- MASCOTA DADA DE BAJA SATISFACTORIAMENTE.\n");
				} else {
					printf("- BAJA CANCELADA.\n");
				}
			} else {
				printf("- MASCOTA NO ENCONTRADA EN EL SISTEMA.\n");
			}
		}while(ll_len(pArrayListMascotas)&&confirm("- DESEA REALIZAR OTRA BAJA(S/N)?"));
	}
	return retorno;
}

/** \brief Listar mascotas
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_ListMascota(LinkedList* pArrayListMascotas)
{
	int retorno=-1;
	Mascota* mascota=NULL;
    if(pArrayListMascotas!=NULL&&!ll_isEmpty(pArrayListMascotas)){
    	printf("ID              NOMBRE                  APELLIDO DUENIO                 EDAD(ANIOS)     VACUNAS         ESTERILIZADO    COSTO TOTAL\n");
    	printf("------------------------------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<ll_len(pArrayListMascotas);i++){
			mascota=(Mascota*)ll_get(pArrayListMascotas,i);
			Mascota_mostrarMascota(mascota);
    	}
		printf("------------------------------------------------------------------------------------------------------------------------------------\n");
		retorno=0;
    }
	return retorno;
}

/** \brief Ordenar mascotas
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_sortMascota(LinkedList* pArrayListMascotas)
{
	int retorno=-1;
	int opcion;
	int (*pFuncion)(void* arg1, void* arg2);
	if(pArrayListMascotas!=NULL&&!ll_isEmpty(pArrayListMascotas)){
		getPositiveInt("CRITERIOS:\n- 1. POR ID.\n- 2. POR NOMBRE.\n INGRESE CRITERIO:", &opcion,1,2);
		if(opcion==1){
			pFuncion=Mascota_compareById;
		} else {
			pFuncion=Mascota_compareByName;
		}
		// 1:Ascendiente
		// 0:Descendiente
		getPositiveInt("ORDEN:\n- 1. ASCENDIENTE.\n- 2. DESCENDIENTE.\n INGRESE ORDEN:", &opcion,1,2);
		if(opcion==1){
			printf("- ORDENANDO MASCOTAS PORFAVOR ESPERE...\n");
			retorno=ll_sort(pArrayListMascotas, pFuncion, 1);
		} else {
			printf("- ORDENANDO MASCOTAS PORFAVOR ESPERE...\n");
			retorno=ll_sort(pArrayListMascotas, pFuncion, 0);
		}
	}
    return retorno;
}

/**
 * map Mascota (calcular costo total) Aplica una función a cada elemento de la linkedList
 * @param pArrayListMascotas
 * @return -2 si puntero a NULL o lista vacia; -1 si se cancelo el map; 0 si funciono
 */
int controller_mapMascota(LinkedList* pArrayListMascotas){
	int retorno=-2;
	void (*pFuncion)(void* arg);
	if(pArrayListMascotas!=NULL&&!ll_isEmpty(pArrayListMascotas)){
		retorno=-1;
		pFuncion=Mascota_mapCosto;
		if(confirm("- DESEA CALCULAR EL COSTO TOTAL DE TRATAMIENDO DE LAS MASCOTAS(S/N)?\n- COSTO POR VACUNA: $2500.\n- COSTO ESTERILIZACION: $4000.")){
			ll_map(pArrayListMascotas, pFuncion);
			retorno=0;
		}
	}
	return retorno;
}

/**
 * filter Mascota Aplica un filtro a traves de ll_filter a una linkedList y la muestra
 * @param pArrayListMascotas
 * @return -3 si puntero a null o lista original vacia; -1 si no hay elementos que cumplan el criterio; 0 si funciono
 */
int controller_filterMascota(LinkedList* pArrayListMascotas){
	int retorno=-3;
	int (*pFuncion)(void* arg);
	int filtro;
	LinkedList* listaFiltrada=NULL;
	if(pArrayListMascotas!=NULL&&!ll_isEmpty(pArrayListMascotas)){
		retorno=-2;
		getPositiveInt("- INGRESE FILTRO A APLICAR:\n\t1. FILTRAR MASCOTAS ESTERILIZADAS.\n\t2. FILTRAR MASCOTAS CON TODAS LAS VACUNAS.\n\t3. FILTRAR COSTO MAYOR A $10000\n",&filtro,1,3);
		switch(filtro){
		case 1:
			pFuncion=Mascota_filtrarPorEsterilizado;
			break;
		case 2:
			pFuncion=Mascota_filtrarPorTodasLasVacunas;
			break;
		case 3:
			pFuncion=Mascota_filtrarPorCostoAlto;
			break;
		}
		if(confirm("- ESTA SEGURO QUE DESEA APLICAR EL FILTRO(S/N)?")){
			listaFiltrada=ll_filter(pArrayListMascotas, pFuncion);
			retorno=controller_ListMascota(listaFiltrada);
			ll_deleteLinkedList(listaFiltrada);
		}
	}
	return retorno;
}

/** \brief Guarda los datos de las mascotas en el archivo 'path' (modo texto).
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListMascotas)
{
	int retorno=-2;
	FILE* pArchivo;
	pArchivo=fopen(path,"w");
	if(pArchivo!=NULL&&stringIsPath(path)&&pArrayListMascotas!=NULL){
			printf("- REALIZANDO ESCRITURA...\n");
			retorno=parser_saveMascotasAsText(pArchivo, pArrayListMascotas);
	}
	fclose(pArchivo);
    return retorno;
}

/** \brief Guarda los datos de las mascotas en el archivo 'path' (modo binario).
 *
 * \param path char*
 * \param pArrayListMascotas LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListMascotas)
{
	int retorno=-2;
	FILE* pArchivo;
	pArchivo=fopen(path,"wb");
	if(pArchivo!=NULL&&stringIsPath(path)&&pArrayListMascotas!=NULL){
		printf("- REALIZANDO ESCRITURA...\n");
		retorno=parser_saveMascotasAsBinary(pArchivo, pArrayListMascotas);
	}
	fclose(pArchivo);
    return retorno;
}





