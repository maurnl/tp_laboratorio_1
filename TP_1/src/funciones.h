/**
 * @brief Toma un mensaje pasa mostrar al usuario y pregunta por si o no
 * @param mensaje Es el mensaje a mostrar
 * @return 1 si la respuesta es si, 0 en caso contrario
 */
int preguntar(char mensaje[]);
/**
 * @brief Toma un precio base y un valor de porcentaje y lo aplica al precio base
 * @param precioBase Es el precio base
 * @param porcentaje Es el porcentaje a aplicar ( puede ser negativo )
 * @param *resultado Es la variable de tipo puntero donde se guardará el resultado
 * @return -1 si el valor base es menor a cero, 1 si funcionó correctamente
 */
float aplicarPorcentaje(float precioBase, float porcentaje, float* resultado);
/**
 * @brief Toma un valor en pesos y lo convierte a BTC
 * @param precio Es el valor en pesos a convertir
 * @param *resultado Es la variable de tipo puntero donde se guardará el resultado
 * @return -1 si el valor base es menor a cero, 1 si funcionó correctamente
 */
float pesoABtc(float precio, float* resultado);
/**
 * @brief Calcula el valor unitario dividiendo el total por la cantidad de muestras
 * @param precioTotal Es el costo total
 * @param unidades Es la cantidad de unidades
 * @param *resultado Es la variable de tipo puntero donde se guardará el resultado
 * @return -1 si el valor base es menor a cero, 1 si funcionó correctamente
 */
float precioUnitario(float precioTotal, float unidades,float* resultado);
/**
 * @brief Muestra al usuario un mensaje y luego le pide un valor float
 * @param mensaje Es el mensaje a mostrar
 * @return el valor float ingresado por el usuario
 */
float pedirFloatPositivo(char mensaje[]);
/**
 * @brief Muestra al usuario un mensaje y luego le pide un valor de tipo int mayor a 0
 * @param mensaje Es el mensaje a mostrar
 * @return el valor int ingresado por el usuario
 */
int pedirIntPositivo(char mensaje[]);
