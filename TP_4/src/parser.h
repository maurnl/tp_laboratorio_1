// Lectura
int parser_MascotaFromText(FILE* pArchivo, LinkedList* pArrayListMascotas);
int parser_MascotaFromBinary(FILE* pArchivo, LinkedList* pArrayListMascotas);
// Escritura
int parser_saveMascotasAsText(FILE* pArchivo, LinkedList* pArrayListMascotas);
int parser_saveMascotasAsBinary(FILE* pArchivo, LinkedList* pArrayListMascotas);
