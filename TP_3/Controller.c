#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "menu.h"
#include "Passenger.h"
#include "parser.h"
#include "utn.h"
/**
 * @brief Obtiene el id máximo de una linkedlist
 * @param LinkedList* pArrayListPassenger
 * @return
 */
int controller_getMaximoId(LinkedList* pArrayListPassenger){
	Passenger* pasajero=NULL;
	int retorno=-1;
	int maxId=0;
	int actualId;
	for(int i=0;i<ll_len(pArrayListPassenger);i++){
		pasajero=(Passenger*) ll_get(pArrayListPassenger, i);
		if(pasajero==NULL){
			retorno=-1;
			break;
		}
		Passenger_getId(pasajero, &actualId);
		if(i==0 || maxId<actualId){
			maxId=actualId;
			retorno=maxId;
		}
	}
	return retorno;
}

/**
 * @brief Obtiene el siguiente ID a utilizar para una linkedlist
 * @param LinkedList* pArrayListPassenger
 * @return
 */
int controller_getNextId(LinkedList* pArrayListPassenger){
	int retorno=-1;
	if(pArrayListPassenger!=NULL){
		if(!ll_isEmpty(pArrayListPassenger)){
			retorno=controller_getMaximoId(pArrayListPassenger);
			if(retorno!=-1){
				retorno++;
			}
		} else {
			retorno=1;
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
	Passenger* pasajero=NULL;
	if(list1!=NULL&&list2!=NULL){
		nextId=controller_getNextId(list1);
		for(int i=0;i<ll_len(list2);i++){
			pasajero=(Passenger*)ll_get(list2, i);
			Passenger_setId(pasajero, nextId);
			ll_push(list1, ll_len(list1), pasajero);
			nextId++;
		}
		retorno=0;
	}
	return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListPassenger)
{
	int retorno=-2;
	FILE* pArchivo;
	LinkedList* linkedListAux=NULL;
	printf("- INTENTANDO ABRIR ARCHIVO...\n");
	pArchivo=fopen(path,"r");
	if(pArrayListPassenger!=NULL&&stringIsPath(path)&&pArchivo!=NULL){
		printf("- ARCHIVO ENCONTRADO.\n");
		if(ll_isEmpty(pArrayListPassenger)){
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_PassengerFromText(pArchivo, pArrayListPassenger);
		} else if(confirm("- SE DETECTARON PASAJEROS EN EL SISTEMA. DESEA MANTENERLOS (S/N)? (SE GUARDARÁN AL FINAL DEL ARCHIVO CARGADO):")){
			linkedListAux=ll_clone(pArrayListPassenger);
			ll_clear(pArrayListPassenger);
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_PassengerFromText(pArchivo, pArrayListPassenger);
			controller_mergeLinkedList(pArrayListPassenger, linkedListAux);
			ll_deleteLinkedList(linkedListAux);
		} else {
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_PassengerFromText(pArchivo, pArrayListPassenger);
		}
	}
	fclose(pArchivo);
	return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListPassenger)
{
	int retorno=-2;
	FILE* pArchivo;
	LinkedList* linkedListAux=NULL;
	printf("- INTENTANDO ABRIR ARCHIVO...\n");
	pArchivo=fopen(path,"rb");
	if(pArrayListPassenger!=NULL&&stringIsPath(path)&&pArchivo!=NULL){
		printf("- ARCHIVO ENCONTRADO.\n");
		if(ll_isEmpty(pArrayListPassenger)){
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_PassengerFromBinary(pArchivo, pArrayListPassenger);
		} else if(confirm("- SE DETECTARON PASAJEROS EN EL SISTEMA. DESEA MANTENERLOS (S/N)? (SE GUARDARAN AL FINAL DEL ARCHIVO CARGADO):")){
			linkedListAux=ll_clone(pArrayListPassenger);
			ll_clear(pArrayListPassenger);
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_PassengerFromBinary(pArchivo, pArrayListPassenger);
			controller_mergeLinkedList(pArrayListPassenger, linkedListAux);
			ll_deleteLinkedList(linkedListAux);
		} else {
			printf("- REALIZANDO LECTURA...\n");
			retorno=parser_PassengerFromBinary(pArchivo, pArrayListPassenger);
		}
	}
	fclose(pArchivo);
	return retorno;
}

/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger,int* id)
{
	int retorno=-1;
	if(pArrayListPassenger!=NULL&&id!=NULL){
		Passenger* passengerBuff=NULL;
		char nombreBuff[50];
		char apellidoBuff[50];
		float precioBuff;
		int tipoBuff;
		char codigoBuff[9];
		char estadoBuff[25];
		printf("\t\t** CARGA DE PASAJERO **\n");
		if(	!(getAlphabeticText("- INGRESE NOMBRE DEL PASAJERO:", nombreBuff, 50)
			||getAlphabeticText("- INGRESE APELLIDO DEL PASAJERO:", apellidoBuff, 50)
			||getPositiveFloat("- INGRESE PRECIO:", &precioBuff, 10000, 250000)
			||getPositiveInt("- INGRESE TIPO DE PASAJERO: ", &tipoBuff, 0, 4)
			||getAlphanumericText("- INGRESE CODIGO DE VUELO: ", codigoBuff, 9)
			||getAlphabeticText("- INGRESE ESTADO DE VUELO: ", estadoBuff, 25)) ) {
			passengerBuff=Passenger_newParametros(*id,nombreBuff, apellidoBuff, precioBuff, tipoBuff, codigoBuff, estadoBuff);
			if(passengerBuff!=NULL){
				ll_add(pArrayListPassenger, passengerBuff);
				(*id)++;
				retorno=0;
			}
		} else {
			retorno=-2;
		}
	}
    return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-3;
	Passenger* pasajero=NULL;
	int id;
	int indice;
	int maxId;
	int subOpcion;
	char nombreBuff[50], apellidoBuff[50], codigoBuff[9];
	float precioBuff;
	int tipoBuff;
	if(pArrayListPassenger!=NULL&&!ll_isEmpty(pArrayListPassenger)){
		maxId=ll_len(pArrayListPassenger);
		getPositiveInt("- INGRESE ID A BUSCAR: ", &id, 0, maxId);
		indice=Passenger_getPassengerById(pArrayListPassenger, id);
		if(indice!=-1){
			pasajero=(Passenger*)ll_get(pArrayListPassenger, indice);
			if(pasajero!=NULL&&!Passenger_getIsEmpty(pasajero)){
				do{
					retorno=Passenger_mostrarPasajero(pasajero);
					getPositiveInt("- INGRESE DATO A MODIFICAR:\n\t1. NOMBRE.\n\t2.APELLIDO\n\t3.PRECIO.\n\t4.TIPO DE PASAJERO.\n\t5.CODIGO DE VUELO", &subOpcion, 1, 5);
					switch(subOpcion){
					case 1:
						getAlphabeticText("- INGRESE NOMBRE NUEVO: ", nombreBuff, 50);
						Passenger_setNombre(pasajero, nombreBuff);
						break;
					case 2:
						getAlphabeticText("- INGRESE APELLIDO NUEVO: ", apellidoBuff, 50);
						Passenger_setApellido(pasajero, apellidoBuff);
						break;
					case 3:
						getPositiveFloat("- INGRESE PRECIO NUEVO: ", &precioBuff, 5000, 500000);
						Passenger_setPrecio(pasajero, precioBuff);
						break;
					case 4:
						getPositiveInt("- INGRESE TIPO DE PASAJERO NUEVO: ", &tipoBuff, 1, 4);
						Passenger_setTipoPasajero(pasajero, tipoBuff);
						break;
					case 5:
						getAlphanumericText("- INGRESE CODIGO DE VUELO NUEVO: ", codigoBuff, 9);
						Passenger_setCodigoVuelo(pasajero, codigoBuff);
						break;
					}
					printf("- MODIFICADO EXISTOSAMENTE.\n");
					retorno=Passenger_mostrarPasajero(pasajero);
				}while(confirm("- DESEA MODIFICAR OTRO DATO (S/N)?"));
			}
		} else {
			retorno=-2;
		}
	}
    return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	Passenger* pasajero=NULL;
	int id, indice;
	if(pArrayListPassenger!=NULL&&!ll_isEmpty(pArrayListPassenger)){
		do{
			getPositiveInt("- INGRESE ID DE PASAJERO A BUSCAR: ", &id, 0, ll_len(pArrayListPassenger));
			indice=Passenger_getPassengerById(pArrayListPassenger, id);
			pasajero=(Passenger*)ll_get(pArrayListPassenger, indice);
			if(indice!=-1&&!Passenger_getIsEmpty(pasajero)){
				Passenger_mostrarPasajero(pasajero);
				if(pasajero!=NULL&&confirm("- CONFIRME BAJA DE PASAJERO(S/N).")){
					//Passenger_setIsEmpty(pasajero, 1);
					ll_remove(pArrayListPassenger, indice);
					retorno=0;
					printf("- PASAJERO DADO DE BAJA SATISFACTORIAMENTE.\n");
				} else {
					printf("- BAJA CANCELADA.\n");
				}
			} else {
				printf("- PASAJERO NO ENCONTRADO EN EL SISTEMA.\n");
			}
		}while(confirm("- DESEA REALIZAR OTRA BAJA(S/N)?"));
	}
	return retorno;
}

/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	Passenger* pasajero;
	int len;
    if(pArrayListPassenger!=NULL&&!ll_isEmpty(pArrayListPassenger)){
    	len=ll_len(pArrayListPassenger);
    	Passenger_printHeader(len);
		for(int i=0;i<len;i++){
			pasajero=(Passenger*)ll_get(pArrayListPassenger,i);
			if(!Passenger_getIsEmpty(pasajero)){
				Passenger_mostrarPasajero(pasajero);
			}
    	}
		retorno=0;
    }
	return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	int opcion;
	int (*pFuncion)(void* arg1, void* arg2);
	if(pArrayListPassenger!=NULL&&!ll_isEmpty(pArrayListPassenger)){
		getPositiveInt("CRITERIOS:\n- 1. POR ID.\n- 2. POR NOMBRE.\n INGRESE CRITERIO:", &opcion,1,2);
		if(opcion==1){
			pFuncion=Passenger_compareById;
		} else {
			pFuncion=Passenger_compareByLastName;
		}
		// 1:Ascendiente
		// 0:Descendiente
		getPositiveInt("ORDEN:\n- 1. ASCENDIENTE.\n- 2. DESCENDIENTE.\n INGRESE ORDEN:", &opcion,1,2);
		if(opcion==1){
			printf("- ORDENANDO PASAJEROS PORFAVOR ESPERE...\n");
			retorno=ll_sort(pArrayListPassenger, pFuncion, 1);
		} else {
			printf("- ORDENANDO PASAJEROS PORFAVOR ESPERE...\n");
			retorno=ll_sort(pArrayListPassenger, pFuncion, 0);
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=-2;
	FILE* pArchivo;
	pArchivo=fopen(path,"w");
	if(pArchivo!=NULL&&stringIsPath(path)&&pArrayListPassenger!=NULL){
			printf("- REALIZANDO ESCRITURA...\n");
			retorno=parser_saveAsText(pArchivo, pArrayListPassenger);
	}
	fclose(pArchivo);
    return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger)
{
	int retorno=-2;
	FILE* pArchivo;
	pArchivo=fopen(path,"wb");
	if(pArchivo!=NULL&&stringIsPath(path)&&pArrayListPassenger!=NULL){
		printf("- REALIZANDO ESCRITURA...\n");
		retorno=parser_saveAsBinary(pArchivo, pArrayListPassenger);
	}
	fclose(pArchivo);
    return retorno;
}




