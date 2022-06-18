/*
 * input.c
 *
 *  Created on: 18 jun. 2022
 *      Author: Mauro
 */
#include <stdio.h>
#include "utn.h"

/**
 * @brief Funcion para control de menu
 * @param flagSave bandera para evitar salir sin guardar
 * @return
 */
int menu(int* flagSave){
	int opcion=-1;
	getPositiveInt("\tMenu:\n\t\t1. Cargar los datos de las mascotas desde el archivo data.csv (modo texto).\n\t\t2. Cargar los datos de las mascotas desde el archivo data.bin (modo binario).\n\t\t3. Alta de mascota\n\t\t4. Modificar datos de mascota\n\t\t5. Baja de mascota\n\t\t6. Listar mascotas\n\t\t7. Ordenar mascotas\n\t\t8. Mapear mascotas.\n\t\t9. Filtrar mascotas\n\t\t10. Guardar los datos de las mascotas en el archivo data.csv (modo texto).\n\t\t11. Guardar los datos de las mascotas en el archivo data.bin (modo binario).\n\t\t12. Salir",
			&opcion, 1, 12);
	if(opcion==12&&!*flagSave){
		printf("- GUARDE LOS CAMBIOS REALIZADOS ANTES DE SALIR DEL PROGRAMA.\n");
		opcion=13;
	} else if(opcion==10||opcion==11){
		*flagSave=1;
	}

	return opcion;
}
