/*
 * controller.c
 *
 *  Created on: 25 jun. 2022
 *      Author: Mauro
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utn.h"
#include "controller.h"
#include "ArrayPassenger.h"

/**
 * Add passengers
 * @param list pointer to passengers array
 * @param len int
 * @return -3 if null pointer or invalid len or -2 if no empty space or -1 if invalid data entered or 0 if ok
 */
int controller_addPassenger(Passenger* list, int len){
	int returnAux=-3;
	char nameBuff[51];
	float priceBuff;
	char lastNameBuff[51];
	int typeBuff;
	char flycodeBuff[10];
	int statusBuff;
	char typeDesc[25];
	if(list!=NULL&&len>0){
		returnAux=-2;
		if(getEmptyPassengerIndex(list, len)!=-1){
			returnAux=-1;
			printf("\t\t**REGISTRAR NUEVO PASAJERO**\n");
			if(!getAlphabeticText("- INGRESE NOMBRE DEL PASAJERO: ", nameBuff, 51)
			   &&!getAlphabeticText("- INGRESE APELLIDO DEL PASAJERO: ", lastNameBuff, 51)
			   &&!getPositiveFloat("- INGRESE PRECIO DEL VUELO($1000-$150000): ",&priceBuff,1000,150000)
			   &&!getAlphanumericText("- INGRESE CODIGO DE VUELO(EJEMPLO: 'XX90001'): ",flycodeBuff,10)
			   &&!getAlphabeticText("- INGRESE TIPO DE PASAJERO(FIRST CLASS, EXECUTIVE CLASS O TURIST CLASS): ", typeDesc,25)
			   &&typePassengerStrToInt(typeDesc)!=-1)
			{
				statusBuff=confirm("- EL AVION ESTA EN VUELO(S/N)?");
				returnAux=1;
				typeBuff=typePassengerStrToInt(typeDesc);
				printf("- DATOS INGRESADOS:\n");
				printf("NOMBRE          APELLIDO        PRECIO          TIPO DE PASAJERO        CODIGO DE VUELO ESTADO DE VUELO\n");
				printf("---------------------------------------------------------------------------------------------------------------\n");
				printf("%-15s\t%-15s\t%-5.2f\t%-16s\t%-10s\t",nameBuff,lastNameBuff,priceBuff,typeDesc,flycodeBuff);
				if(statusBuff){
					printf("EN VUELO\n");
				} else{
					printf("ESPERANDO\n");
				}
				printf("---------------------------------------------------------------------------------------------------------------\n");
				if(confirm("DESEA DAR DE ALTA ESTE PASAJERO(S/N)?")){
					returnAux=0;
					addPassengers(list,len,nextPassengerId(),nameBuff,lastNameBuff,priceBuff,typeBuff,flycodeBuff, statusBuff);
				}
			}
		}
	}
	return returnAux;
}
/**
 * Edit passengers
 * @param list pointer to array of passengers
 * @param len int
 * @return -2 if null pointer or invalid len or -1 if passenger id not found or 0 if ok
 */
int controller_editPassenger(Passenger* list, int len){
	int returnAux=-2;
	char flycodeBuff[10];
	int validData=1;
	char typeBuff[25];
	int id, typeIntBuff;
	int index,opcion;
	char nameBuff[51];
	float priceBuff;
	char lastNameBuff[51];
	if(list!=NULL&&len>0&&!passengerListIsEmpty(list,len)){
		returnAux=-1;
		printPassengers(list, len);
		getPositiveInt("- INGRESE ID A BUSCAR EN EL SISTEMA: ",&id,0,2000);
		index=findPassengerById(list,len,id);
		if(index!=-1&&(*(list+index)).isEmpty==0){
			returnAux=0;
			printf("ID  NOMBRE              APELLIDO        PRECIO          TIPO DE PASAJERO        CODIGO DE VUELO ESTADO DE VUELO\n");
			printf("---------------------------------------------------------------------------------------------------------------\n");
			printPassenger(*(list+index));
			printf("---------------------------------------------------------------------------------------------------------------\n");
			do{
				if(!validData){
					printf("- EL DATO INGRESADO NO ES VALIDO. PORFAVOR INTENTE DE NUEVO.\n");
				}
				validData=0;
				getPositiveInt("- INGRESE DATO A MODIFICAR:\n\t1. NOMBRE.\n\t2. APELLIDO.\n\t3. PRECIO.\n\t4. CODIGO\n\t5. TIPO DE PASAJERO.\n\t6. VOLVER AL MENU",&opcion,1,6);
				switch(opcion){
				case 1:
					if(!getAlphabeticText("- INGRESE NUEVO NOMBRE:",nameBuff,51)){
						validData=1;
						printf("- NOMBRE NUEVO: '%s'.\n", nameBuff);
						if(confirm("- CONFIRME MODIFICACION DE NOMBRE(S/N)"))
							strcpy((*(list+index)).name,nameBuff);
					}
					break;
				case 2:
					if(!getAlphabeticText("- INGRESE NUEVO APELLIDO:",lastNameBuff,51)){
						validData=1;
						printf("- APELLIDO NUEVO: '%s'.\n", lastNameBuff);
						if(confirm("- CONFIRME MODIFICACION DE APELLIDO(S/N)"))
							strcpy((*(list+index)).lastName,lastNameBuff);
					}
					break;
				case 3:
					if(!getPositiveFloat("- INGRESE PRECIO NUEVO($1000-$150000): ",&priceBuff,1000,15000)){
						validData=1;
						printf("- PRECIO NUEVO: '%.2f'.\n", priceBuff);
						if(confirm("- CONFIRME MODIFICACION DE PRECIO(S/N)"))
							(*(list+index)).price=priceBuff;
					}
					break;
				case 4:
					if(!getAlphanumericText("- INGRESE CODIGO DE VUELO NUEVO(EJEMPLO 'AL2002'): ",flycodeBuff,10)){
						validData=1;
						printf("- CODIGO DE VUELO NUEVO: '%s'.",flycodeBuff);
						if(confirm("- CONFIRME MODIFICACION DE CODIGO DE VUELO(S/N)"))
							strcpy((*(list+index)).flycode,flycodeBuff);
					}
					break;
				case 5:
					if(!getPositiveInt("- INGRESE TIPO DE PASAJERO NUEVO POR ID(1. FIRST CLASS,2. EXECUTIVE CLASS,3.TURIST CLASS):",&typeIntBuff,1,3)&&!typePassengerToStr(typeIntBuff,typeBuff)){
						validData=1;
						printf("- TIPO DE PASAJERO NUEVO: '%s'.\n",typeBuff);
						if(confirm("- CONFIRME MODIFICACION DE TIPO DE PASAJERO(S/N)")){
							(*(list+index)).typePassenger.typeId=typeIntBuff;
							strcpy((*(list+index)).typePassenger.typeDescription,typeBuff);
						}
					}
					break;
				}
			}while(opcion!=6);
			printf("- PASAJERO MODIFICADO: \n");
			printf("ID  NOMBRE              APELLIDO        PRECIO          TIPO DE PASAJERO        CODIGO DE VUELO ESTADO DE VUELO\n");
			printf("---------------------------------------------------------------------------------------------------------------\n");
			printPassenger(*(list+index));
			printf("---------------------------------------------------------------------------------------------------------------\n");
			while(confirm("<< PRESIONE ENTER PARA CONTINUAR... >>"));
		}
	}
	return returnAux;
}
/**
 * remove Passenger
 * @param list pointer to passenger array
 * @param len int
 * @return -2 if null pointers or invalid len or -1 if passenger id not found or 0 if removed succesfully.
 */
int controller_removePassenger(Passenger* list, int len){
	int returnAux=-3;
	int id,index;
	if(list!=NULL&&len>0&&!passengerListIsEmpty(list,len)){
		returnAux=-2;
		printPassengers(list, len);
		if(!getPositiveInt("- INGRESE ID A BUSCAR EN EL SISTEMA: ",&id,0,2000)){
			index=findPassengerById(list,len,id);
			if(index!=-1){
				returnAux=-1;
				printf("ID  NOMBRE              APELLIDO        PRECIO          TIPO DE PASAJERO        CODIGO DE VUELO ESTADO DE VUELO\n");
				printf("---------------------------------------------------------------------------------------------------------------\n");
				printPassenger(*(list+index));
				printf("---------------------------------------------------------------------------------------------------------------\n");
				if(confirm("- ESTA SEGURO QUE DESEA BORRAR ESTE PASAJERO(S/N)?")){
					returnAux=removePassenger(list, len, id);
				}
			}
		}
	}
	return returnAux;
}
/**
 * list passengers
 * @param list pointer to array of passengers
 * @param len int
 * @return -1 if null pointer or invalid len 0 if ok
 */
int controller_listPassenger(Passenger* list, int len){
	int returnAux=-2;
	int opcion=4;
	if(list!=NULL&&len>0&&!passengerListIsEmpty(list,len)){
		returnAux=-1;
		do{
			getPositiveInt("\t\t** INFORMES **\n\t1. LISTAR ORDENADOS ALFABETICAMENTE POR NOMBRE Y TIPO.\n\t2. TOTAL, PROMEDIO DE PASAJES Y CUANTOS PASAJEROS LO SUPERAN.\n\t3. LISTAR ORDENADOS ALFABETICAMENTE POR CODIGO Y ESTADO DE VUELO.\n\t4. VOLVER AL MENU.\n",&opcion,1,4);
			switch(opcion){
			case 1:
				sortPassengers(list,len,1);
				break;
			case 2:
				returnAux=printHigherThanAveragePassengers(list,len);
				break;
			case 3:
				sortPassengersByFlycode(list,len,1);
				break;
			}
			if(opcion!=2&&opcion!=4){
				returnAux=printPassengers(list, len);
				while(confirm("<< PRESIONE ENTER PARA CONTINUAR... >>"));
			}
		}while(opcion!=4);
	}
	return returnAux;
}
