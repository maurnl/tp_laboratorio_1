/*
 * menu.c
 *
 *  Created on: 25 jun. 2022
 *      Author: Mauro
 */
#include <stdio.h>
#include "utn.h"

int menu(){
	int opcion=-1;
	getPositiveInt("\t\t**MENU**:\n\t1. ALTA PASAJEROS.\n\t2. MODIFICAR PASAJEROS.\n\t3. BAJA PASAJEROS.\n\t4. INFORMAR PASAJEROS\n\t5. ALTA FORZADA DE 10 PASAJEROS.\n\t6. SALIR.\n", &opcion, 1, 5);
	return opcion;
}
