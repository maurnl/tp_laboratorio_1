/*
 * input.c
 *
 *  Created on: 4 jun. 2022
 *      Author: Mauro
 */
#include "utn.h"
#include "LinkedList.h"
#include "Passenger.h"
#include <stdio.h>

/**
 * @brief Funcion para control de menu
 * @param flagSave bandera para evitar salir sin guardar
 * @return
 */
int menu(int* flagSave){
	int opcion=-1;
	getPositiveInt("\tMenu:\n\t\t1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).\n\t\t2. Cargar los datos de los pasajeros desde el archivo data.bin (modo binario).\n\t\t3. Alta de pasajero\n\t\t4. Modificar datos de pasajero\n\t\t5. Baja de pasajero\n\t\t6. Listar pasajeros\n\t\t7. Ordenar pasajeros\n\t\t8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).\n\t\t9. Guardar los datos de los pasajeros en el archivo data.bin (modo binario).\n\t\t10. Salir",
			&opcion, 1, 10);
	if(opcion==10&&!*flagSave){
		printf("- GUARDE LOS CAMBIOS REALIZADOS ANTES DE SALIR DEL PROGRAMA.\n");
		opcion=11;
	} else if(opcion==8||opcion==9){
		*flagSave=1;
	}

	return opcion;
}
