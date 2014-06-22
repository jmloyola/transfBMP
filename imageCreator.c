#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Prototipos
unsigned char** crearArregloPixeles(int, int);
void crearPatron(unsigned char**, int, int, int);

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

    cabeceraBMP.tipo[0] = 'B';
    cabeceraBMP.tipo[1] = 'M';
    cabeceraBMP.tamanioArchivo = anchoImagen * 3 * altoImagen + 54; //Mirar. Cuando lo guarda, lo hace en little endian creo.
    cabeceraBMP.reservado1 = 0;
    cabeceraBMP.reservado2 = 0;
    cabeceraBMP.offsetArregloPixeles = 54;
    cabeceraBMP.longitudBitMapInfoHeader = 40;
    cabeceraBMP.anchoBitMap = anchoImagen;
    cabeceraBMP.altoBitMap = altoImagen;
    cabeceraBMP.numeroPlanos = 1;
    cabeceraBMP.bitsPorPixel = 24;
    cabeceraBMP.tipoCompresion = 0;
    cabeceraBMP.tamanioImagenEnBytes = anchoImagen * 3 * altoImagen;
    cabeceraBMP.resolucionHorizontal = 2835;
    cabeceraBMP.resolucionVertical = 2835;
    cabeceraBMP.numeroColoresUsados = 0;
    cabeceraBMP.numeroColoersImportantes = 0;


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

    fseek(punteroPrimerImagen, cabeceraBMP.offsetArregloPixeles, SEEK_SET);


    int numFilas = altoImagen;
    int numCol = anchoImagen * 3;

    unsigned char **pixelesPrimerImagen = crearArregloPixeles(numFilas, numCol);
    if (pixelesPrimerImagen == NULL) {
        printf("ERROR >> No se pudo crear el arreglo para los pixeles de la primer imagen.\n");
        return 1;
    }

    unsigned char **pixelesSegundaImagen = crearArregloPixeles(numFilas, numCol);
    if (pixelesSegundaImagen == NULL) {
        printf("ERROR >> No se pudo crear el arreglo para los pixeles de la segunda imagen.\n");
        return 1;
    }


    crearPatron(pixelesPrimerImagen, anchoImagen, altoImagen, patronPrimerImagen);
    crearPatron(pixelesSegundaImagen, anchoImagen, altoImagen, patronSegundaImagen);

    int i, j;
    
    for (j = 0; j < cabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < cabeceraBMP.anchoBitMap; i++) {
            fwrite(&pixelesPrimerImagen[j][i * 3], sizeof (unsigned char), 1, punteroPrimerImagen);
            fwrite(&pixelesPrimerImagen[j][(i * 3) + 1], sizeof (unsigned char), 1, punteroPrimerImagen);
            fwrite(&pixelesPrimerImagen[j][(i * 3) + 2], sizeof (unsigned char), 1, punteroPrimerImagen);
        }
    }

    for (i = 0; i < numFilas; i++) {
        free(pixelesPrimerImagen[i]);
    }
    free(pixelesPrimerImagen);

    fclose(punteroPrimerImagen);

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

    fseek(punteroSegundaImagen, cabeceraBMP.offsetArregloPixeles, SEEK_SET);

    for (j = 0; j < cabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < cabeceraBMP.anchoBitMap; i++) {
            fwrite(&pixelesSegundaImagen[j][i * 3], sizeof (unsigned char), 1, punteroSegundaImagen);
            fwrite(&pixelesSegundaImagen[j][(i * 3) + 1], sizeof (unsigned char), 1, punteroSegundaImagen);
            fwrite(&pixelesSegundaImagen[j][(i * 3) + 2], sizeof (unsigned char), 1, punteroSegundaImagen);
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
        arreglo[i] = (unsigned char*) malloc(sizeof (unsigned char) * numCol);

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
    
    
    
    /*
    for (j = 0; j < cabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < cabeceraBMP.anchoBitMap; i++) {
            //if ((i % divisionPrimerRandom) <= longitudPrimerRandom){
            //        pixelesPrimerImagen[j][i*3] = (unsigned char)((bluePrimerRandom + ((i % divisionPrimerRandom)*8)) % 255);
            //        pixelesPrimerImagen[j][(i*3)+1] = (unsigned char)((greenPrimerRandom + ((i % divisionPrimerRandom)*8)) % 255);
            //        pixelesPrimerImagen[j][(i*3)+2] = (unsigned char)((redPrimerRandom + ((i % divisionPrimerRandom)*8)) % 255);
            //}
            //else{
            //        pixelesPrimerImagen[j][i*3] = (unsigned char)(rand() % 255);
            //        pixelesPrimerImagen[j][(i*3)+1] = (unsigned char)(rand() % 255);
            //        pixelesPrimerImagen[j][(i*3)+2] = (unsigned char)(rand() % 255);
            //}
            if ((i >= divisionPrimerRandom - longitudPrimerRandom) && (i <= divisionPrimerRandom + longitudPrimerRandom)){
                    pixelesPrimerImagen[j][i*3] = (unsigned char)((bluePrimerRandom + i) % 255);
                    pixelesPrimerImagen[j][(i*3)+1] = (unsigned char)((greenPrimerRandom + i) % 255);
                    pixelesPrimerImagen[j][(i*3)+2] = (unsigned char)((redPrimerRandom + i) % 255);
            }
            else{
            pixelesPrimerImagen[j][i * 3] = (unsigned char) (rand() % 255);
            pixelesPrimerImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
            pixelesPrimerImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
            }
        }
    }*/
/*
    for (j = 0; j < cabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < cabeceraBMP.anchoBitMap; i++) {
            //if ((j % divisionSegundoRandom) <= longitudSegundoRandom){
            //        pixelesSegundaImagen[j][i*3] = (unsigned char)((blueSegundoRandom + ((j % divisionSegundoRandom)*8)) % 255);
            //        pixelesSegundaImagen[j][(i*3)+1] = (unsigned char)((greenSegundoRandom + ((j % divisionSegundoRandom)*8)) % 255);
            //        pixelesSegundaImagen[j][(i*3)+2] = (unsigned char)((redSegundoRandom + ((j % divisionSegundoRandom)*8)) % 255);
            //}
            //else{
            //        pixelesSegundaImagen[j][i*3] = (unsigned char)(rand() % 255);
            //       pixelesSegundaImagen[j][(i*3)+1] = (unsigned char)(rand() % 255);
            //        pixelesSegundaImagen[j][(i*3)+2] = (unsigned char)(rand() % 255);
            //}
            if ((j >= divisionSegundoRandom - longitudSegundoRandom) && (j <= divisionSegundoRandom + longitudSegundoRandom)){
                    pixelesSegundaImagen[j][i*3] = (unsigned char)((blueSegundoRandom + j) % 255);
                    pixelesSegundaImagen[j][(i*3)+1] = (unsigned char)((greenSegundoRandom + j) % 255);
                    pixelesSegundaImagen[j][(i*3)+2] = (unsigned char)((redSegundoRandom + j) % 255);
            }
            else{
            pixelesSegundaImagen[j][i * 3] = (unsigned char) (rand() % 255);
            pixelesSegundaImagen[j][(i * 3) + 1] = (unsigned char) (rand() % 255);
            pixelesSegundaImagen[j][(i * 3) + 2] = (unsigned char) (rand() % 255);
            }
        }
    }*/
}
