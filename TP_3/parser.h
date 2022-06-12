// Lectura
int parser_PassengerFromText(FILE* pArchivo, LinkedList* pArrayListPassenger);
int parser_PassengerFromBinary(FILE* pArchivo, LinkedList* pArrayListPassenger);
// Escritura
int parser_saveAsText(FILE* pArchivo, LinkedList* pArrayListPassenger);
int parser_saveAsBinary(FILE* pArchivo, LinkedList* pArrayListPassenger);
