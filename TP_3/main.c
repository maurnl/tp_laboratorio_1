#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "menu.h"

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main()
{
	setbuf(stdout, NULL);
	int id=1;
    int option=0;
    int flagSave=0;
    int salida;
    LinkedList* listaPasajeros = ll_newLinkedList();
    do{
		option=menu(&flagSave);
        switch(option)
        {
            case 1:
                salida=controller_loadFromText("data.csv",listaPasajeros);
            	switch(salida){
					case 0:
						printf("- ARCHIVO CARGADO CORRECTAMENTE.\n");
						break;
					case -1:
						printf("- ERROR EN LA LECTURA DEL ARCHIVO.\n");
						break;
					case -2:
						printf("- ARCHIVO INEXISTENTE O RUTA NO VALIDA.\n");
						break;
            	}
                break;
            case 2:
            	salida=controller_loadFromBinary("data.bin",listaPasajeros);
            	switch(salida){
					case 0:
						printf("- ARCHIVO CARGADO CORRECTAMENTE.\n");
						break;
					case -1:
						printf("- ERROR EN LA LECTURA DEL ARCHIVO.\n");
						break;
					case -2:
						printf("- ARCHIVO INEXISTENTE O RUTA NO VALIDA.\n");
						break;
            	}
            	break;
            case 3:
            	id=controller_getNextId(listaPasajeros);
            	salida=controller_addPassenger(listaPasajeros, &id);
            	if(salida==-2){
            		printf("- DATO NO VALIDO. REINTENTE.\n");
            	}
            	break;
            case 4:
            	salida=controller_editPassenger(listaPasajeros);
            	switch(salida){
					case -1:
						printf("- ERROR AL MOSTRAR PASAJERO.\n");
						break;
					case -2:
						printf("- PASAJERO NO ENCONTRADO EN EL SISTEMA.\n");
						break;
					case -3:
						printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
						break;
            	}
            	break;
            case 5:
            	salida=controller_removePassenger(listaPasajeros);
            	if(salida==-1){
            		printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE\n");
            	}
            	break;
            case 6:
            	salida=controller_ListPassenger(listaPasajeros);
            	switch(salida){
					case -1:
						printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
						break;
					case -2:
						printf("- ERROR AL MOSTRAR PASAJERO.\n");
						break;
            	}
				break;
            case 7:
            	salida=controller_sortPassenger(listaPasajeros);
            	if(salida==0){
            		printf("- PASAJEROS ORDENADOS CORRECTAMENTE.\n");
            	} else if(salida==-1){
            		printf("- LISTA VACIA. CARGUE ALGUN PASAJERO Y REINTENTE.\n");
            	}
            	break;
            case 8:
            	salida=controller_saveAsText("data.csv", listaPasajeros);
            	switch(salida){
					case 0:
						printf("- CAMBIOS GUARDADOS CORRECTAMENTE.\n");
						break;
					case -1:
						printf("- ERROR DE ESCRITURA.\n");
						break;
					case -2:
						printf("- NO SE PUDO CREAR ARCHIVO (RUTA O LISTA INVALIDA).\n");
						break;
            	}
            	break;
            case 9:
            	controller_saveAsBinary("data.bin",listaPasajeros);
               	switch(salida){
					case 0:
						printf("- CAMBIOS GUARDADOS CORRECTAMENTE.\n");
						break;
					case -1:
						printf("- ERROR DE ESCRITURA.\n");
						break;
					case -2:
						printf("- NO SE PUDO CREAR ARCHIVO (RUTA O LISTA INVALIDA).\n");
						break;
				}
            	break;
            case 10:
            	ll_deleteLinkedList(listaPasajeros);
            	break;
            case 11:
            	break;
        }
    }while(option != 10);
    return 0;
}

