/*
 * Controller.h
 *
 *  Created on: 18 jun. 2022
 *      Author: Mauro
 */
int controller_loadFromText(char* path , LinkedList* pArrayListMascotas);
int controller_loadFromBinary(char* path , LinkedList* pArrayListMascotas);
int controller_addMascota(LinkedList* pArrayListMascotas,int* id);
int controller_editMascota(LinkedList* pArrayListMascotas);
int controller_removeMascota(LinkedList* pArrayListMascotas);
int controller_ListMascota(LinkedList* pArrayListMascotas);
int controller_sortMascota(LinkedList* pArrayListMascotas);
int controller_saveAsText(char* path , LinkedList* pArrayListMascotas);
int controller_saveAsBinary(char* path , LinkedList* pArrayListMascotas);
int controller_getNextId(LinkedList* pArrayListMascotas);
int controller_mergeLinkedList(LinkedList* list1, LinkedList* list2);
int controller_mapMascota(LinkedList* pArrayListMascotas);
int controller_filterMascota(LinkedList* pArrayListMascotas);
