/*
 * ArrayPassenger.c
 *
 *  Created on: 25 jun. 2022
 *      Author: Mauro
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utn.h"
#include "ArrayPassenger.h"

/**
 * checks if a passengers list is empty
 * @return 1 if its empty 0 if not
 */
int passengerListIsEmpty(Passenger* list, int len){
	int returnAux=1;
	for(int i=0;i<len;i++){
		if((*(list+i)).isEmpty==0){
			returnAux=0;
			break;
		}
	}
	return returnAux;
}
/**
 * returns the first empty index in a passengers array
 * @param list pointer to passengers array
 * @param len int
 * @return -1 if no empty space or 0 if ok
 */
int getEmptyPassengerIndex(Passenger* list, int len){
	int returnAux=-1;
	if(list!=NULL&&len>0){
		for(int i=0;i<len;i++){
			if((*(list+i)).isEmpty==1){
				returnAux=i;
				break;
			}
		}
	}
	return returnAux;
}
/**
 * calculates the next passenger id by storing it as static
 * @return the next passenger id
 */
int nextPassengerId(void){
	static int id=0;
	id++;
	return id;
}
/**
 * type passenger int id to string
 * @param typeId id
 * @param typeDesc str
 * @return -1 if null pointer or invalid type id
 */
int typePassengerToStr(int typeId, char* typeDesc){
	int returnAux=-1;
	if(typeDesc!=NULL&&typeId>0&&typeId<4){
		returnAux=0;
		switch(typeId){
			case 1:
				strcpy(typeDesc, "FIRST CLASS");
				break;
			case 2:
				strcpy(typeDesc, "EXECUTIVE CLASS");
				break;
			case 3:
				strcpy(typeDesc, "TURIST CLASS");
				break;
		}
	}
	return returnAux;
}
/**
 * type passenger string to int
 * @param type string
 * @return -1 if null pointer or invalid type or type id if ok
 */
int typePassengerStrToInt(char* type){
	int returnAux=-1;
	if(type!=NULL){
		stringToUpper(type,strlen(type));
		if(!strcmp("FIRST CLASS",type)){
			returnAux=1;
		}else if(!strcmp("EXECUTIVE CLASS",type)){
			returnAux=2;
		}else if(!strcmp("TURIST CLASS",type)){
			returnAux=3;
		}
	}
	return returnAux;
}
/** \brief To indicate that all position in the array are empty,
* this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Passenger* Pointer to array of passenger
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
* */
int initPassengers(Passenger* list, int len){
	int returnAux=-1;
	if(list!=NULL&&len>0){
		for(int i=0;i<len;i++){
			(*(list+i)).isEmpty=1;
		}
		returnAux=0;
	}
	return returnAux;
}
/** \brief add in a existing list of passengers the values received as parameters
* in the first empty position
* \param list passenger*
* \param len int
* \param id int
* \param name[] char
* \param lastName[] char
* \param price float
* \param typePassenger int
* \param flycode[] char
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space] - (0) if Ok
* */
int addPassengers(Passenger* list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[],int statusFlight){
	int returnAux=-1;
	int freeIndex=getEmptyPassengerIndex(list,len);
	char typeDesc[25];
	if(list!=NULL&&len>0&&freeIndex!=-1&&name!=NULL&&lastName!=NULL){
		(*(list+freeIndex)).id=id;
		strcpy((*(list+freeIndex)).name, name);
		strcpy((*(list+freeIndex)).lastName, lastName);
		(*(list+freeIndex)).price=price;
		(*(list+freeIndex)).typePassenger.typeId=typePassenger;
		typePassengerToStr(typePassenger, typeDesc);
		strcpy((*(list+freeIndex)).typePassenger.typeDescription,typeDesc);
		strcpy((*(list+freeIndex)).flycode, flycode);
		(*(list+freeIndex)).statusFlight=statusFlight;
		(*(list+freeIndex)).isEmpty=0;
		returnAux=0;
	}
	return returnAux;
}
/** \brief find a Passenger by Id en returns the index position in array.
*
* \param list Passenger*
* \param len int
* \param id int
* \return Return passenger index position or (-1) if [Invalid length or NULL pointer received or passenger not found]
* */
int findPassengerById(Passenger* list, int len, int id){
	int returnAux=-1;
	if(list!=NULL&&len>0&&id>0){
		for(int i=0;i<len;i++){
			if((*(list+i)).id==id){
				returnAux=i;
				break;
			}
		}
	}
	return returnAux;
}
/** \brief Remove a Passenger by Id (put isEmpty Flag in 1)
*
* \param list Passenger*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a passenger] - (0) if Ok
*
*/
int removePassenger(Passenger* list, int len, int id){
	int returnAux=-1;
	int index;
	if(list!=NULL&&len>0&&id>0&&findPassengerById(list, len,id)!=-1){
		index=findPassengerById(list, len,id);
		(*(list+index)).isEmpty=1;
		returnAux=0;
	}
	return returnAux;
}
/** \brief Sort the elements by name in the array of passengers, the argument order indicate UP or DOWN order
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortPassengers(Passenger* list,int len, int order){
	int retorno=-1;
	int flagSwapeo;
	Passenger aux;
	if(list!=NULL&&len>0){
		do {
			flagSwapeo = 0;
			for(int i=1; i<len; i++) {
				if((order&&(strcmp((*(list+i)).name, (*(list+i-1)).name)<0||(!strcmp((*(list+i)).name, (*(list+i-1)).name)&&strcmp((*(list+i)).typePassenger.typeDescription, (*(list+i-1)).typePassenger.typeDescription)>0)))||(!order&&((strcmp((*(list+i)).name, (*(list+i-1)).name)>0||(!strcmp((*(list+i)).name, (*(list+i-1)).name)&&strcmp((*(list+i)).typePassenger.typeDescription, (*(list+i-1)).typePassenger.typeDescription)<0))))) {
					aux = *(list+i);
					*(list+i) = *(list+i-1);
					*(list+i-1) = aux;
					flagSwapeo = 1;
				}
			}
		} while(flagSwapeo);
		retorno = 1;
	}
	return retorno;
}
/**
 * prints a single passenger info
 * @param passenger passenger
 */
void printPassenger(Passenger passenger){
	printf("%-4d%-15s\t%-15s\t%-8.2f\t%-16s\t%-10s\t",passenger.id,passenger.name,passenger.lastName,passenger.price,passenger.typePassenger.typeDescription,passenger.flycode);
	if(passenger.statusFlight){
		printf("EN VUELO\n");
	} else{
		printf("ESPERANDO\n");
	}
}
/** \brief print the content of passengers array
* \param list Passenger*
* \param length int
* \return int
*/
int printPassengers(Passenger* list, int len){
	int returnAux=-1;
	if(list!=NULL&&len>0){
		printf("ID  NOMBRE              APELLIDO        PRECIO          TIPO DE PASAJERO        CODIGO DE VUELO ESTADO DE VUELO\n");
		printf("---------------------------------------------------------------------------------------------------------------\n");
		for(int i=0;i<len;i++){
			if(!(*(list+i)).isEmpty)
				printPassenger(*(list+i));
		}
		printf("---------------------------------------------------------------------------------------------------------------\n");
		returnAux=0;
	}
	return returnAux;
}
/** \brief Sort the elements by flycode in the array of passengers, the argument order indicate UP or DOWN order
* \param list Passenger*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortPassengersByFlycode(Passenger* list, int len, int order){
	int retorno=-1;
	int flagSwapeo;
	Passenger aux;
	if(list!=NULL&&len>0){
		do {
			flagSwapeo = 0;
			for(int i=1; i<len; i++) {
				if((order&&(strcmp((*(list+i)).flycode, (*(list+i-1)).flycode)<0||(!strcmp((*(list+i)).flycode, (*(list+i-1)).flycode)&&strcmp((*(list+i)).typePassenger.typeDescription, (*(list+i-1)).typePassenger.typeDescription)>0)))||(!order&&((strcmp((*(list+i)).name, (*(list+i-1)).name)>0||(!strcmp((*(list+i)).name, (*(list+i-1)).name)&&strcmp((*(list+i)).typePassenger.typeDescription, (*(list+i-1)).typePassenger.typeDescription)<0))))) {
					aux = *(list+i);
					*(list+i) = *(list+i-1);
					*(list+i-1) = aux;
					flagSwapeo = 1;
				}
			}
		} while(flagSwapeo);
		retorno = 1;
	}
	return retorno;
}

/**
 * calculates total and average price if a passengers array
 * @param list pointer to array of passengers
 * @param len int
 * @param average float to store result
 * @param total float to store result
 * @return -1 if null pointers or invalid len 0 if ok
 */
int getPassengersAverageAndTotalPrice(Passenger* list, int len, float* average, float* total){
	int retorno=-1;
	int contador=0;
	float acumulador=0;
	if(list!=NULL&&len>0&&average!=NULL&&total!=NULL){
		for(int i=0;i<len;i++) {
			if((*(list+i)).isEmpty==0){
				acumulador+=((*(list+i)).price);
				contador++;
			}
		}
		*average=acumulador/contador;
		*total=acumulador;
		retorno=0;
	}
	return retorno;
}
/**
 * prints passengers above average price
 * @param list passengers list
 * @param len int
 * @return -1 if null pointers or invalid len or 0 iff ok
 */
int printHigherThanAveragePassengers(Passenger* list, int len){
	int retorno=-1;
	float promedio;
	float total;
	int contador=0;
	if(list!=NULL&&len>0){
		getPassengersAverageAndTotalPrice(list, len, &promedio, &total);
		printf("**     TOTAL: $%.2f. PROMEDIO: $%.2f      **\n", total,promedio);
		printf("** LISTADO PASAJEROS CON PRECIO MAYOR A $%.2f  **\n", promedio);
		printf("-----------------------------------------------------\n");
		printf("ID       APELLIDO        NOMBRE          PRECIO \n");
		printf("-----------------------------------------------------\n");
		for(int i=0;i<len;i++){
			if((*(list+i)).isEmpty==0&&(*(list+i)).price>promedio) {
				contador++;
				printf("%d\t %-10s\t %-8s\t $%-6.2f\n", (*(list+i)).id, (*(list+i)).name, (*(list+i)).lastName, (*(list+i)).price);
			}
		}
		printf("-----------------------------------------------------\n");
		printf("** SUPERAN EL PROMEDIO %d PASAJEROS. **\n",contador);
		retorno=0;
	}
	return retorno;
}

/**
 * Hardcodes 10 passengers
 * @param list array of passengers
 * @param len int
 * @return 10 (hardcoded passengers qty)
 */
void hardcodePassengers(Passenger* list, int len){
	char names[10][51]={"Zanella","Barbara","Cristian","Alberto","Quispe","Randall","Boo","Sullivan","Mike","Cachito"};
	char lastnames[10][51]={"Le-Good","Cosins","Welbelove","Adrianello","Childerley","Huband","Sime","Kynastone","Simione","Dellar"};
	float prices[10]={9000,15000,9000,45000,7050,22000,19000,14444,4500,9000};
    int types[10]={3,2,1,3,2,1,3,2,1,3};
    char codes[10][10]={"JK50001","LM50001","DF50001","AL50001","AL50001","BC50001","NO50001","NO50001","AL50001","YZ50001"};
    char status[10]={1,0,1,1,1,0,1,1,0,0};
    for(int i=0;i<10;i++){
    	addPassengers(list,len,nextPassengerId(),names[i],lastnames[i],prices[i],types[i],codes[i],status[i]);
    }
    printf("- PASAJEROS CARGADOS CORRECTAMENTE.\n");
}


