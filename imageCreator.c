#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Prototipos
unsigned char** crearArregloPixeles(int, int);
void crearPatron(unsigned char**, int, int, int);

// Estructura para el header de una imagen BMP de 24 bits.
struct BMP_Header {
    char tipo[2];
    unsigned int tamanioArchivo;
    unsigned short int reservado1;
    unsigned short int reservado2;
    unsigned int offsetArregloPixeles;
    unsigned int longitudBitMapInfoHeader;
    int anchoBitMap;
    int altoBitMap;
    unsigned short int numeroPlanos;
    unsigned short int bitsPorPixel;
    unsigned int tipoCompresion;
    unsigned int tamanioImagenEnBytes;
    int resolucionHorizontal;
    int resolucionVertical;
    unsigned int numeroColoresUsados;
    unsigned int numeroColoersImportantes;
};

int main(int argc, char** argv) {
    char nombrePrimerImagen[35] = "";
    char nombreSegundaImagen[35] = "";
    
    int anchoImagen;
    int altoImagen;
    
    struct BMP_Header cabeceraBMP;
    
    FILE *punteroPrimerImagen = NULL;
    FILE *punteroSegundaImagen = NULL;
    
    int patronPrimerImagen, patronSegundaImagen;


    // Controlo los argumentos con los que se llama el programa.
    if (argc == 5) {
        anchoImagen = atoi(argv[1]);
        altoImagen = atoi(argv[2]);
        patronPrimerImagen= atoi(argv[3]);
        patronSegundaImagen= atoi(argv[4]);
    } else {
        printf("ERROR >> El programa debe ser invocado con cuatro parametros indicando el ancho, alto y patrones de las imagenes a crear.\n");
        return 1;
    }

    strcat(nombrePrimerImagen, "primerImg");
    strcat(nombrePrimerImagen, argv[1]);
    strcat(nombrePrimerImagen, "x");
    strcat(nombrePrimerImagen, argv[2]);
    strcat(nombrePrimerImagen, ".bmp");

    strcat(nombreSegundaImagen, "segundaImg");
    strcat(nombreSegundaImagen, argv[1]);
    strcat(nombreSegundaImagen, "x");
    strcat(nombreSegundaImagen, argv[2]);
    strcat(nombreSegundaImagen, ".bmp");

    // Abro los archivos BMP para escribir.
    punteroPrimerImagen = fopen(nombrePrimerImagen, "w");
    punteroSegundaImagen = fopen(nombreSegundaImagen, "w");

    if (punteroPrimerImagen == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n", nombrePrimerImagen);
        return 1;
    }
    if (punteroSegundaImagen == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n", nombreSegundaImagen);
        return 1;
    }
    
    // Lleno la estructura header con la informacion de las imagenes a crear.
    cabeceraBMP.tipo[0] = 'B';
    cabeceraBMP.tipo[1] = 'M';
    cabeceraBMP.tamanioArchivo = (anchoImagen * 3 + (anchoImagen % 4)) * altoImagen + 54;
    cabeceraBMP.reservado1 = 0;
    cabeceraBMP.reservado2 = 0;
    cabeceraBMP.offsetArregloPixeles = 54;
    cabeceraBMP.longitudBitMapInfoHeader = 40;
    cabeceraBMP.anchoBitMap = anchoImagen;
    cabeceraBMP.altoBitMap = altoImagen;
    cabeceraBMP.numeroPlanos = 1;
    cabeceraBMP.bitsPorPixel = 24;
    cabeceraBMP.tipoCompresion = 0;
    cabeceraBMP.tamanioImagenEnBytes = (anchoImagen * 3 + (anchoImagen % 4)) * altoImagen;
    cabeceraBMP.resolucionHorizontal = 2835;
    cabeceraBMP.resolucionVertical = 2835;
    cabeceraBMP.numeroColoresUsados = 0;
    cabeceraBMP.numeroColoersImportantes = 0;


    // Escribo el header de la primer imagen.
    fwrite(&cabeceraBMP.tipo, sizeof (char), 2, punteroPrimerImagen);
    fwrite(&cabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.anchoBitMap, sizeof (int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.altoBitMap, sizeof (int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.resolucionVertical, sizeof (int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroPrimerImagen);
    fwrite(&cabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroPrimerImagen);

    // Adelanto el puntero de los archivos para que apunten al comienzo del arreglo de pixeles.
    fseek(punteroPrimerImagen, cabeceraBMP.offsetArregloPixeles, SEEK_SET);

    // Calculo el relleno de la imagen en caso de que el numero de bytes de cada linea de la imagen no sea multiplo de cuatro.
    int rellenoImagen = cabeceraBMP.anchoBitMap % 4;

    int numFilas = altoImagen;
    int numCol = anchoImagen * 3 + rellenoImagen;

    // Creo la matriz que tendra los pixeles de la primer imagen.
    unsigned char **pixelesPrimerImagen = crearArregloPixeles(numFilas, numCol);
    if (pixelesPrimerImagen == NULL) {
        printf("ERROR >> No se pudo crear el arreglo para los pixeles de la primer imagen.\n");
        return 1;
    }

    // Creo la matriz que tendra los pixeles de la segunda imagen.
    unsigned char **pixelesSegundaImagen = crearArregloPixeles(numFilas, numCol);
    if (pixelesSegundaImagen == NULL) {
        printf("ERROR >> No se pudo crear el arreglo para los pixeles de la segunda imagen.\n");
        return 1;
    }

    // Asigno un patron a los pixeles de la primer imagen.
    crearPatron(pixelesPrimerImagen, anchoImagen, altoImagen, patronPrimerImagen);
    
    // Asigno un patron a los pixeles de la segunda imagen.
    crearPatron(pixelesSegundaImagen, anchoImagen, altoImagen, patronSegundaImagen);

    int i, j;
    
    // Escribo la matriz de pixeles en el archivo de la primer imagen.
    for (j = 0; j < numFilas; j++) {
        for (i = 0; i < numCol; i++) {
            fwrite(&pixelesPrimerImagen[j][i], sizeof (unsigned char), 1, punteroPrimerImagen);
        }
    }

    for (i = 0; i < numFilas; i++) {
        free(pixelesPrimerImagen[i]);
    }
    free(pixelesPrimerImagen);

    fclose(punteroPrimerImagen);

    // Escribo el header de la segunda imagen.
    fwrite(&cabeceraBMP.tipo, sizeof (char), 2, punteroSegundaImagen);
    fwrite(&cabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.anchoBitMap, sizeof (int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.altoBitMap, sizeof (int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.resolucionVertical, sizeof (int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroSegundaImagen);
    fwrite(&cabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroSegundaImagen);

    // Adelanto el puntero de los archivos para que apunten al comienzo del arreglo de pixeles.
    fseek(punteroSegundaImagen, cabeceraBMP.offsetArregloPixeles, SEEK_SET);

    // Escribo la matriz de pixeles en el archivo de la segunda imagen.
    for (j = 0; j < numFilas; j++) {
        for (i = 0; i < numCol; i++) {
            fwrite(&pixelesSegundaImagen[j][i], sizeof (unsigned char), 1, punteroSegundaImagen);
        }
    }

    for (i = 0; i < numFilas; i++) {
        free(pixelesSegundaImagen[i]);
    }
    free(pixelesSegundaImagen);

    fclose(punteroSegundaImagen);

    return 0;
}

unsigned char** crearArregloPixeles(int numFilas, int numCol) {
    unsigned char **arreglo;
    int i;

    arreglo = (unsigned char**) malloc(sizeof (unsigned char*) * numFilas);

    if (arreglo == NULL) {
        printf("ERROR >> No se pudo crear el arreglo.\n");
        return NULL;
    }

    for (i = 0; i < numFilas; i++) {
        // Notar que aqui utilizo un calloc en lugar de un malloc, ya que necesito que la matriz este inicializada en cero para que los bytes de relleno ya esten incializados.
        arreglo[i] = (unsigned char*) calloc(numCol, sizeof (unsigned char));

        if (arreglo[i] == NULL) {
            printf("ERROR >> No se pudo crear el arreglo.\n");
            return NULL;
        }
    }

    return arreglo;
}

void crearPatron(unsigned char** pixelesImagen, int anchoImagen, int altoImagen, int opcion){
    int divisionAnchoRandom = anchoImagen / 2;
    int divisionAltoRandom = altoImagen / 2;
    int longitudRandom = anchoImagen / 10;
    int blueRandom;
    int greenRandom;
    int redRandom;

    int i,j;
    
    srand(time(NULL));
    
    blueRandom = rand() % 255;
    greenRandom = rand() % 255;
    redRandom = rand() % 255;  
    
    switch (opcion){
        case 0:{
            // Patron: Una linea vertical en el medio.
            for (j = 0; j < altoImagen; j++){
                for (i = 0; i < anchoImagen; i++){
                    if ((i >= divisionAnchoRandom - longitudRandom) && (i <= divisionAnchoRandom + longitudRandom)){
                        pixelesImagen[j][i*3] = (unsigned char)((blueRandom + i) % 255);
                        pixelesImagen[j][(i*3)+1] = (unsigned char)((greenRandom + i) % 255);
                        pixelesImagen[j][(i*3)+2] = (unsigned char)((redRandom + i) % 255);
                    }
                    else{
                        pixelesImagen[j][i * 3] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
                    }
                }
            }
            break;
        }
        case 1:{
            // Patron: Una linea horizontal en el medio.
            for (j = 0; j < altoImagen; j++){
                for (i = 0; i < anchoImagen; i++){
                    if ((j >= divisionAltoRandom - longitudRandom) && (j <= divisionAltoRandom + longitudRandom)){
                        pixelesImagen[j][i*3] = (unsigned char)((blueRandom + j) % 255);
                        pixelesImagen[j][(i*3)+1] = (unsigned char)((greenRandom + j) % 255);
                        pixelesImagen[j][(i*3)+2] = (unsigned char)((redRandom + j) % 255);
                    }
                    else{
                        pixelesImagen[j][i * 3] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
                    }
                }
            }
            break;
        }
        case 2:{
            // Patron: Varias lineas verticales separadas por un espacio determinado.
            for (j = 0; j < altoImagen; j++){
                for (i = 0; i < anchoImagen; i++){
                    if ((i % divisionAnchoRandom) <= longitudRandom){
                        pixelesImagen[j][i*3] = (unsigned char)((blueRandom + i) % 255);
                        pixelesImagen[j][(i*3)+1] = (unsigned char)((greenRandom + i) % 255);
                        pixelesImagen[j][(i*3)+2] = (unsigned char)((redRandom + i) % 255);
                    }
                    else{
                        pixelesImagen[j][i * 3] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
                    }
                }
            }
            break;
        }
        case 3:{
            // Patron: Varias lineas horizontales separadas por un espacio determinado.
            for (j = 0; j < altoImagen; j++){
                for (i = 0; i < anchoImagen; i++){
                    if ((j % divisionAltoRandom) <= longitudRandom){
                        pixelesImagen[j][i*3] = (unsigned char)((blueRandom + j) % 255);
                        pixelesImagen[j][(i*3)+1] = (unsigned char)((greenRandom + j) % 255);
                        pixelesImagen[j][(i*3)+2] = (unsigned char)((redRandom + j) % 255);
                    }
                    else{
                        pixelesImagen[j][i * 3] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
                    }
                }
            }
            break;
        }
        case 4:{
            // Patron: Mitad vertical de la imagen de 'un' color.
            for (j = 0; j < altoImagen; j++){
                for (i = 0; i < anchoImagen; i++){
                    if (i <= divisionAnchoRandom){
                        pixelesImagen[j][i*3] = (unsigned char)((blueRandom + i) % 255);
                        pixelesImagen[j][(i*3)+1] = (unsigned char)((greenRandom + i) % 255);
                        pixelesImagen[j][(i*3)+2] = (unsigned char)((redRandom + i) % 255);
                    }
                    else{
                        pixelesImagen[j][i * 3] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
                    }
                }
            }
            break;
        }
        case 5:{
            // Patron: Mitad horizontal de la imagen de 'un' color.
            for (j = 0; j < altoImagen; j++){
                for (i = 0; i < anchoImagen; i++){
                    if (j <= divisionAltoRandom){
                        pixelesImagen[j][i*3] = (unsigned char)((blueRandom + j) % 255);
                        pixelesImagen[j][(i*3)+1] = (unsigned char)((greenRandom + j) % 255);
                        pixelesImagen[j][(i*3)+2] = (unsigned char)((redRandom + j) % 255);
                    }
                    else{
                        pixelesImagen[j][i * 3] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
                        pixelesImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
                    }
                }
            }
            break;
        }
        default:{
        }
    }
}
