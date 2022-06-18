/*
 ============================================================================
 Name        : TP_4.c
 Author      : Mauro Luciano (DIV J)
 Version     : la que anda
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "menu.h"

int main(void) {
	setbuf(stdout, NULL);
		int id=1;
	    int option=0;
	    int flagSave=0;
	    int salida;
	    LinkedList* listaMascotas = ll_newLinkedList();
	    do{
			option=menu(&flagSave);
	        switch(option)
	        {
	            case 1:
	                salida=controller_loadFromText("data.csv",listaMascotas);
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
	            	salida=controller_loadFromBinary("data.bin",listaMascotas);
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
	            	id=controller_getNextId(listaMascotas);
	            	salida=controller_addMascota(listaMascotas, &id);
	            	break;
	            case 4:
	            	salida=controller_editMascota(listaMascotas);
	            	switch(salida){
						case 0:
							printf("- MASCOTA ENCONTRADA Y MOSTRADA.\n");
							break;
						case -1:
							printf("- ERROR AL MOSTRAR MASCOTA.\n");
							break;
						case -2:
							printf("- MASCOTA NO ENCONTRADA EN EL SISTEMA.\n");
							break;
						case -3:
							printf("- LISTA VACIA. CARGUE ALGUNA MASCOTA Y REINTENTE.\n");
							break;
	            	}
	            	break;
	            case 5:
	            	salida=controller_removeMascota(listaMascotas);
	            	if(salida==-1){
	            		printf("- LISTA VACIA. CARGUE ALGUNA MASCOTA Y REINTENTE\n");
	            	}
	            	break;
	            case 6:
	            	salida=controller_ListMascota(listaMascotas);
	            	switch(salida){
						case -1:
							printf("- LISTA VACIA. CARGUE ALGUNA MASCOTA Y REINTENTE.\n");
							break;
						case -2:
							printf("- ERROR AL MOSTRAR MASCOTA.\n");
							break;
	            	}
					break;
	            case 7:
	            	salida=controller_sortMascota(listaMascotas);
	            	if(salida==0){
	            		printf("- MASCOTAS ORDENADOS CORRECTAMENTE.\n");
	            	} else if(salida==-1){
	            		printf("- LISTA VACIA. CARGUE ALGUNA MASCOTA Y REINTENTE.\n");
	            	}
	            	break;
	            case 8:
	            	salida=controller_mapMascota(listaMascotas);
	            	switch(salida){
						case 0:
							printf("- COSTO TOTAL CALCULADO CORRECTAMENTE.\n");
							break;
						case -1:
							printf("- MAPEADO CANCELADO.\n");
							break;
	            	}
	            	break;
				case 9:
	            	salida=controller_filterMascota(listaMascotas);
	            	switch(salida){
	            	case -1:
	            		printf("- NO SE ENCONTRARON MASCOTAS PARA EL FILTRO APLICADO.\n");
	            		break;
	            	case -2:
	            		printf("- APLICACION DE FILTRO CANCELADA.\n");
	            		break;
	            	}
					break;
	            case 10:
	            	salida=controller_saveAsText("data.csv", listaMascotas);
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
	            case 11:
	            	controller_saveAsBinary("data.bin",listaMascotas);
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
	            case 12:
	            	ll_deleteLinkedList(listaMascotas);
	            	break;
	            case 13:
	            	break;
	        }
	    }while(option!=12);
	    return 0;
}
