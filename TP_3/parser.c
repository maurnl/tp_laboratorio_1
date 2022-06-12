#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "menu.h"
#include "Controller.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pArchivo, LinkedList* pArrayListPassenger)
{
	int retorno=0;
	int leido;
	char buffers[7][50];
	char fantasma[50];
	Passenger* passengerBuff=NULL;
	// Lectura fantasma
	fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", fantasma, fantasma, fantasma, fantasma, fantasma, fantasma, fantasma);
	while(!feof(pArchivo)){
		leido=fscanf(pArchivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffers[0], buffers[1], buffers[2], buffers[3], buffers[4], buffers[5], buffers[6]);
		if(leido==7){
			passengerBuff=Passenger_newParametros(atoi(buffers[0]),buffers[1],buffers[2],atof(buffers[3]),2,buffers[4], buffers[6]);
			if(passengerBuff!=NULL){
				Passenger_setTipoPasajeroStr(passengerBuff, buffers[5]);
				ll_add(pArrayListPassenger, passengerBuff);
			}
		} else if(!feof(pArchivo)){
			retorno=-1;
			break;
		}
	}
    return retorno;
}

/** \brief Parsea los datos de los pasajeros desde el archivo data.bin (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pArchivo , LinkedList* pArrayListPassenger)
{
	int retorno=-1;
	int leido;
	Passenger passengerLectura;
	Passenger* passengerBuff;
	while(!feof(pArchivo)){
		leido=fread(&passengerLectura, sizeof(Passenger), 1, pArchivo);
		if(leido==1){
			passengerBuff=Passenger_newParametros(passengerLectura.id,passengerLectura.nombre, passengerLectura.apellido, passengerLectura.precio, passengerLectura.tipoPasajero, passengerLectura.codigoVuelo, passengerLectura.estadoVuelo);
			if(passengerBuff!=NULL){
				ll_add(pArrayListPassenger, passengerBuff);
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
 * @brief Guarda los datos de una lista de pasajeros en modo binario
 * @param pArchivo Puntero a archivo
 * @param pArrayListPassenger LinkedList*
 * @return
 */
int parser_saveAsBinary(FILE* pArchivo, LinkedList* pArrayListPassenger){
	int retorno=0;
	int escrito;
	Passenger* passengerAux=NULL;
	for(int i=0;i<ll_len(pArrayListPassenger);i++){
		passengerAux=ll_get(pArrayListPassenger, i);
		escrito=fwrite(passengerAux, sizeof(Passenger), 1, pArchivo);
		if(escrito<1){
			retorno=-1;
			break;
		}
	}
	return retorno;
}

/**
 * @brief Guarda los datos de una lista de pasajeros en modo texto
 * @param pArchivo Puntero a archivo
 * @param pArrayListPassenger LinkedList*
 * @return
 */
int parser_saveAsText(FILE* pArchivo, LinkedList* pArrayListPassenger){
	int retorno=0;
	Passenger* passengerAux=NULL;
	int idAux;
	char nombreAux[50], apellidoAux[50], codigoAux[9], estadoAux[25], tipoAux[25];
	float precioAux;
	fprintf(pArchivo, "id,name,lastname,price,flycode,typePassenger,statusFlight\n");
	for(int i=0;i<ll_len(pArrayListPassenger);i++){
		passengerAux=ll_get(pArrayListPassenger, i);
		if(passengerAux!=NULL){
			Passenger_getId(passengerAux, &idAux);
			Passenger_getNombre(passengerAux, nombreAux);
			Passenger_getApellido(passengerAux, apellidoAux);
			Passenger_getPrecio(passengerAux, &precioAux);
			Passenger_getCodigoVuelo(passengerAux, codigoAux);
			Passenger_getTipoPasajeroStr(passengerAux, tipoAux);
			Passenger_getEstadoVuelo(passengerAux, estadoAux);
			fprintf(pArchivo, "%d,%s,%s,%.0f,%s,%s,%s\n", idAux, nombreAux, apellidoAux, precioAux, codigoAux, tipoAux, estadoAux);
		}  else {
			retorno=-1;
			break;
		}
	}
	return retorno;
}
