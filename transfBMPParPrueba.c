#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

// Prototipos
unsigned char** crearArregloPixeles(int, int);

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
    char nombrePrimerImagen[35];
    char nombreSegundaImagen[35];
    char nombrePrimerImagenBlancoNegro[35] = "tempPrueba_";
    char nombreSegundaImagenBlancoNegro[35] = "tempPrueba_";
    char nombreImagenCombinada[35] = "salidaPrueba.bmp";

    struct BMP_Header primerCabeceraBMP;
    struct BMP_Header segundaCabeceraBMP;
    ///struct BMP_Header cabeceraImagenSalida;    

    FILE *punteroPrimerImagen = NULL;
    FILE *punteroSegundaImagen = NULL;
    FILE *punteroPrimerImagenBlancoNegro = NULL;
    FILE *punteroSegundaImagenBlancoNegro = NULL;
    FILE *punteroImagenSalida = NULL;

    int cantThreads;

    time_t comienzoTrabajoParalelo, finalizaTrabajoParalelo;


    // Controlo los argumentos con los que se llama el programa.
    if (argc == 4) {
        cantThreads = atoi(argv[1]);
        strcpy(nombrePrimerImagen, argv[2]);
        strcpy(nombreSegundaImagen, argv[3]);
    } else {
        printf("ERROR >> El programa debe ser invocado con tres parametros indicando la cantidad de threads a usar y las imagenes a transformar.\n");
        return 1;
    }

    strcat(nombrePrimerImagenBlancoNegro, nombrePrimerImagen);
    strcat(nombreSegundaImagenBlancoNegro, nombreSegundaImagen);

    // Asigno la cantidad de threads a usar para ejecutar el programa
    omp_set_num_threads(cantThreads);

    // Abro los archivos BMP para leer.
    punteroPrimerImagen = fopen(nombrePrimerImagen, "r");
    punteroSegundaImagen = fopen(nombreSegundaImagen, "r");

    if (punteroPrimerImagen == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para lectura\n", nombrePrimerImagen);
        return 1;
    }

    if (punteroSegundaImagen == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para lectura\n", nombreSegundaImagen);
        return 1;
    }


    // Leo el header de la primer imagen.
    ///fread(&cabeceraBMP, sizeof (struct BMP_Header), 1, punteroArchivoImagen);
    fread(&primerCabeceraBMP.tipo, sizeof (char), 2, punteroPrimerImagen);
    fread(&primerCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.anchoBitMap, sizeof (int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.altoBitMap, sizeof (int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.resolucionVertical, sizeof (int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroPrimerImagen);

    ///
    /*
    printf("tipo: %c%c\n", primerCabeceraBMP.tipo[0],primerCabeceraBMP.tipo[1]);///
    printf("tamanioArchivo: %d\n", primerCabeceraBMP.tamanioArchivo);///
    printf("offsetArregloPixeles: %d\n", primerCabeceraBMP.offsetArregloPixeles);///
    printf("longitudBitMapInfoHeader: %d\n", primerCabeceraBMP.longitudBitMapInfoHeader);///
    printf("anchoBitMap: %d\n", primerCabeceraBMP.anchoBitMap);///
    printf("altoBitMap: %d\n", primerCabeceraBMP.altoBitMap);///
    printf("numeroPlanos: %d\n", primerCabeceraBMP.numeroPlanos);///
    printf("bitsPorPixel: %d\n", primerCabeceraBMP.bitsPorPixel);///
    printf("tipoCompresion: %d\n", primerCabeceraBMP.tipoCompresion);///
    printf("tamanioImagenEnBytes: %d\n", primerCabeceraBMP.tamanioImagenEnBytes);///
    printf("resolucionHorizontal: %d\n", primerCabeceraBMP.resolucionHorizontal);///
    printf("resolucionVertical: %d\n", primerCabeceraBMP.resolucionVertical);///
    printf("numeroColoresUsados: %d\n", primerCabeceraBMP.numeroColoresUsados);///
    printf("numeroColoersImportantes: %d\n", primerCabeceraBMP.numeroColoersImportantes);///*/


    // Leo el header de la segunda imagen.
    fread(&segundaCabeceraBMP.tipo, sizeof (char), 2, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.anchoBitMap, sizeof (int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.altoBitMap, sizeof (int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.resolucionVertical, sizeof (int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroSegundaImagen);

    // Adelanto el puntero de los archivos para que apunten al comienzo del arreglo de pixeles.
    // Debo adelantarlo desde el comienzo lo que dice el offset porque puede que el arreglo de pixeles no se encuentre inmediatamente despues del header.
    fseek(punteroPrimerImagen, primerCabeceraBMP.offsetArregloPixeles, SEEK_SET);
    fseek(punteroSegundaImagen, segundaCabeceraBMP.offsetArregloPixeles, SEEK_SET);    
    
    // Calculo el relleno de la primer imagen en caso de que el numero de bytes de cada linea de la imagen no sea multiplo de cuatro.
    int rellenoPrimerImagen = primerCabeceraBMP.anchoBitMap % 4;

    // Creo la matriz que tendra los pixeles de la primer imagen.
    int numFilasPrimerImagen = primerCabeceraBMP.altoBitMap;
    int numColPrimerImagen = primerCabeceraBMP.anchoBitMap * 3 + rellenoPrimerImagen;

    unsigned char **pixelesPrimerImagen = crearArregloPixeles(numFilasPrimerImagen, numColPrimerImagen);
    if (pixelesPrimerImagen == NULL) {
        printf("ERROR >> No se pudo crear el arreglo para los pixeles de la primer imagen.\n");
        return 1;
    }
    
    // Calculo el relleno de la segunda imagen en caso de que el numero de bytes de cada linea de la imagen no sea multiplo de cuatro.
    int rellenoSegundaImagen = segundaCabeceraBMP.anchoBitMap % 4;

    // Creo la matriz que tendra los pixeles de la segunda imagen.
    int numFilasSegundaImagen = segundaCabeceraBMP.altoBitMap;
    int numColSegundaImagen = segundaCabeceraBMP.anchoBitMap * 3 + rellenoSegundaImagen;

    unsigned char **pixelesSegundaImagen = crearArregloPixeles(numFilasSegundaImagen, numColSegundaImagen);
    if (pixelesSegundaImagen == NULL) {
        printf("ERROR >> No se pudo crear el arreglo para los pixeles de la segunda imagen.\n");
        return 1;
    }

    int i, j;
    int valorPromedio = 0;
    unsigned char red, green, blue;

    // Obtengo el tiempo de comienzo del trabajo que se compara.
    comienzoTrabajoParalelo = time(NULL);


    //#pragma omp parallel private (blue, green, red, valorPromedio) shared (primerCabeceraBMP, pixelesPrimerImagen, i, j, segundaCabeceraBMP)
#pragma omp parallel private (blue, green, red, valorPromedio, i) shared (primerCabeceraBMP, pixelesPrimerImagen, j, segundaCabeceraBMP, pixelesSegundaImagen)
    {
        // Cargo la matriz de la primer imagen con los valores RGB de cada pixel de la primer imagen y la transformo a escala de grises.
#pragma omp for
        for (j = 0; j < primerCabeceraBMP.altoBitMap; j++) {
            fseek(punteroPrimerImagen, primerCabeceraBMP.offsetArregloPixeles + j*numColPrimerImagen, SEEK_SET);
            for (i = 0; i < primerCabeceraBMP.anchoBitMap; i++) {
                if (fread(&blue, sizeof (unsigned char), 1, punteroPrimerImagen) != 1) {
                    printf("ERROR >> No se pudo leer el pixel (%d,%d) azul de la primer imagen\n", j, i);
                }
                if (fread(&green, sizeof (unsigned char), 1, punteroPrimerImagen) != 1) {
                    printf("ERROR >> No se pudo leer el pixel (%d,%d) verde de la primer imagen\n", j, i);
                }
                if (fread(&red, sizeof (unsigned char), 1, punteroPrimerImagen) != 1) {
                    printf("ERROR >> No se pudo leer el pixel (%d,%d) rojo de la primer imagen\n", j, i);
                }
                valorPromedio = blue + red + green;
                valorPromedio = (int) (valorPromedio / 3);
                ///Borrar
                /*
                pixelesPrimerImagen[i*3][j] = (unsigned char)valorPromedio;
                pixelesPrimerImagen[(i*3)+1][j] = (unsigned char)valorPromedio;
                pixelesPrimerImagen[(i*3)+2][j] = (unsigned char)valorPromedio;*/
                pixelesPrimerImagen[j][i * 3] = (unsigned char) valorPromedio;
                pixelesPrimerImagen[j][(i * 3) + 1] = (unsigned char) valorPromedio;
                pixelesPrimerImagen[j][(i * 3) + 2] = (unsigned char) valorPromedio;
            }
        }

        // Cargo la matriz de la segunda imagen con los valores RGB de cada pixel de la segunda imagen y la transformo a escala de grises.
#pragma omp for
        for (j = 0; j < segundaCabeceraBMP.altoBitMap; j++) {
            fseek(punteroSegundaImagen, segundaCabeceraBMP.offsetArregloPixeles + j*numColSegundaImagen, SEEK_SET);
            for (i = 0; i < segundaCabeceraBMP.anchoBitMap; i++) {
                if (fread(&blue, sizeof (unsigned char), 1, punteroSegundaImagen) != 1) {
                    printf("ERROR >> No se pudo leer el pixel (%d,%d) azul de la segunda imagen\n", j, i);
                }
                if (fread(&green, sizeof (unsigned char), 1, punteroSegundaImagen) != 1) {
                    printf("ERROR >> No se pudo leer el pixel (%d,%d) verde de la segunda imagen\n", j, i);
                }
                if (fread(&red, sizeof (unsigned char), 1, punteroSegundaImagen) != 1) {
                    printf("ERROR >> No se pudo leer el pixel (%d,%d) rojo de la segunda imagen\n", j, i);
                }
                valorPromedio = blue + red + green;
                valorPromedio = (int) (valorPromedio / 3);
                ///BORRAR
                /*
                pixelesSegundaImagen[i*3][j] = (unsigned char)valorPromedio;
                pixelesSegundaImagen[(i*3)+1][j] = (unsigned char)valorPromedio;
                pixelesSegundaImagen[(i*3)+2][j] = (unsigned char)valorPromedio;*/

                pixelesSegundaImagen[j][i * 3] = (unsigned char) valorPromedio;
                pixelesSegundaImagen[j][(i * 3) + 1] = (unsigned char) valorPromedio;
                pixelesSegundaImagen[j][(i * 3) + 2] = (unsigned char) valorPromedio;
            }
        }
    }
    
    fclose(punteroPrimerImagen);
    fclose(punteroSegundaImagen);

    // Obtengo el tiempo de fin del trabajo.
    finalizaTrabajoParalelo = time(NULL);

    // Calculo el tiempo transcurrido.
    double tiempoTranscurrido = difftime(finalizaTrabajoParalelo, comienzoTrabajoParalelo);


    // Abro el archivo para escribir la primer imagen en blanco y negro.
    punteroPrimerImagenBlancoNegro = fopen(nombrePrimerImagenBlancoNegro, "w");

    if (punteroPrimerImagenBlancoNegro == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n", nombrePrimerImagenBlancoNegro);
        return 1;
    }

    // Escribo el header de la primer imagen en escala de grises.
    fwrite(&primerCabeceraBMP.tipo, sizeof (char), 2, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.anchoBitMap, sizeof (int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.altoBitMap, sizeof (int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.resolucionVertical, sizeof (int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);

    // Adelanto el puntero del archivo para que apunte al comienzo del arreglo de pixeles.
    fseek(punteroPrimerImagenBlancoNegro, primerCabeceraBMP.offsetArregloPixeles, SEEK_SET);
    
    // Escribo la matriz de pixeles en el archivo de la primer imagen en escala de grises.
    for (j = 0; j < numFilasPrimerImagen; j++) {
        for (i = 0; i < numColPrimerImagen; i++) {
            fwrite(&pixelesPrimerImagen[j][i], sizeof (unsigned char), 1, punteroPrimerImagenBlancoNegro);
        }
    }
    /*
    // Escribo la matriz de pixeles en el archivo de la primer imagen en escala de grises.
    for (j = 0; j < primerCabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < primerCabeceraBMP.anchoBitMap; i++) {
            ///BORRAR            
            //fwrite(&pixelesPrimerImagen[i*3][j], sizeof(unsigned char), 1, punteroPrimerImagenBlancoNegro);
            //fwrite(&pixelesPrimerImagen[(i*3)+1][j], sizeof(unsigned char), 1, punteroPrimerImagenBlancoNegro);
            //fwrite(&pixelesPrimerImagen[(i*3)+2][j], sizeof(unsigned char), 1, punteroPrimerImagenBlancoNegro);
            fwrite(&pixelesPrimerImagen[j][i * 3], sizeof (unsigned char), 1, punteroPrimerImagenBlancoNegro);
            fwrite(&pixelesPrimerImagen[j][(i * 3) + 1], sizeof (unsigned char), 1, punteroPrimerImagenBlancoNegro);
            fwrite(&pixelesPrimerImagen[j][(i * 3) + 2], sizeof (unsigned char), 1, punteroPrimerImagenBlancoNegro);
        }
    }*/
    
    fclose(punteroPrimerImagenBlancoNegro);

    // Abro el archivo para escribir la segunda imagen en blanco y negro.
    punteroSegundaImagenBlancoNegro = fopen(nombreSegundaImagenBlancoNegro, "w");

    if (punteroSegundaImagenBlancoNegro == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n", nombreSegundaImagenBlancoNegro);
        return 1;
    }

    // Escribo el header de la segunda imagen en escala de grises.
    fwrite(&segundaCabeceraBMP.tipo, sizeof (char), 2, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.anchoBitMap, sizeof (int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.altoBitMap, sizeof (int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.resolucionVertical, sizeof (int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);

    // Adelanto el puntero del archivo para que apunte al comienzo del arreglo de pixeles.
    fseek(punteroSegundaImagenBlancoNegro, segundaCabeceraBMP.offsetArregloPixeles, SEEK_SET);

    // Escribo la matriz de pixeles en el archivo de la segunda imagen en escala de grises.
    for (j = 0; j < numFilasSegundaImagen; j++) {
        for (i = 0; i < numColSegundaImagen; i++) {
            fwrite(&pixelesSegundaImagen[j][i], sizeof (unsigned char), 1, punteroSegundaImagenBlancoNegro);
        }
    }
    /*
    // Escribo la matriz de pixeles en el archivo de la segunda imagen en escala de grises.
    for (j = 0; j < segundaCabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < segundaCabeceraBMP.anchoBitMap; i++) {
            ///BORRAR            
            //fwrite(&pixelesSegundaImagen[i*3][j], sizeof(unsigned char), 1, punteroSegundaImagenBlancoNegro);
            //fwrite(&pixelesSegundaImagen[(i*3)+1][j], sizeof(unsigned char), 1, punteroSegundaImagenBlancoNegro);
            //fwrite(&pixelesSegundaImagen[(i*3)+2][j], sizeof(unsigned char), 1, punteroSegundaImagenBlancoNegro);
            fwrite(&pixelesSegundaImagen[j][i * 3], sizeof (unsigned char), 1, punteroSegundaImagenBlancoNegro);
            fwrite(&pixelesSegundaImagen[j][(i * 3) + 1], sizeof (unsigned char), 1, punteroSegundaImagenBlancoNegro);
            fwrite(&pixelesSegundaImagen[j][(i * 3) + 2], sizeof (unsigned char), 1, punteroSegundaImagenBlancoNegro);
        }
    }*/
    
    fclose(punteroSegundaImagenBlancoNegro);

    // Abro el archivo para escribir la imagen combinada.
    punteroImagenSalida = fopen(nombreImagenCombinada, "w");

    if (punteroImagenSalida == NULL) {
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n", nombreImagenCombinada);
        return 1;
    }

    // Escribo el header de la imagen de salida.
    // Notar que el header sera identico al de la primer imagen ya que se supone que las imagenes de entrada al programa son las dos del mismo tamaño (asi las caracteristicas de la imagen seran las mismas).
    // Se podria usar el header de la segunda imagen al igual que el de la primer.
    ///fwrite(&primerCabeceraBMP, sizeof (struct BMP_Header), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.tipo, sizeof (char), 2, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.offsetArregloPixeles, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.longitudBitMapInfoHeader, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.anchoBitMap, sizeof (int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.altoBitMap, sizeof (int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.numeroPlanos, sizeof (unsigned short int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.bitsPorPixel, sizeof (unsigned short int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.tipoCompresion, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.tamanioImagenEnBytes, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.resolucionHorizontal, sizeof (int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.resolucionVertical, sizeof (int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.numeroColoresUsados, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.numeroColoersImportantes, sizeof (unsigned int), 1, punteroImagenSalida);

    // Adelanto el puntero del archivo para que apunte al comienzo del arreglo de pixeles.
    fseek(punteroImagenSalida, primerCabeceraBMP.offsetArregloPixeles, SEEK_SET);


    // Obtengo el tiempo del comienzo de trabajo.
    // Notar que esta es la segunda parte del trabajo que se compara con la version paralelizada.
    comienzoTrabajoParalelo = time(NULL);

#pragma omp parallel private (i) shared (primerCabeceraBMP, pixelesPrimerImagen, pixelesSegundaImagen, j)
    {
        // Combino las dos imagenes en escala de grises en un sola.
#pragma omp for		
        for (j = 0; j < primerCabeceraBMP.altoBitMap; j++) {
            for (i = 0; i < primerCabeceraBMP.anchoBitMap; i++) {
                pixelesPrimerImagen[j][i * 3] = (pixelesPrimerImagen[j][i * 3] + pixelesSegundaImagen[j][i * 3]) / 2;
                pixelesPrimerImagen[j][(i * 3) + 1] = (pixelesPrimerImagen[j][(i * 3) + 1] + pixelesSegundaImagen[j][(i * 3) + 1]) / 2;
                pixelesPrimerImagen[j][(i * 3) + 2] = (pixelesPrimerImagen[j][(i * 3) + 2] + pixelesSegundaImagen[j][(i * 3) + 2]) / 2;
            }
        }
    }
    
    for (i = 0; i < numFilasSegundaImagen; i++) {
        free(pixelesSegundaImagen[i]);
    }
    free(pixelesSegundaImagen);

    // Obtengo el tiempo de fin del trabajo.
    finalizaTrabajoParalelo = time(NULL);

    // Calculo el tiempo transcurrido.
    // Notar que suma al tiempo transcurrido anterior el tiempo que tarda en obtener la combinacion de las imagenes.
    tiempoTranscurrido += difftime(finalizaTrabajoParalelo, comienzoTrabajoParalelo);

    // Escribo el arreglo de pixeles en la imagen de salida.
    for (j = 0; j < numFilasPrimerImagen; j++) {
        for (i = 0; i < numColPrimerImagen; i++) {
            fwrite(&pixelesPrimerImagen[j][i], sizeof (unsigned char), 1, punteroImagenSalida);
        }
    }
    /*
    // Escribo el arreglo de pixeles en la imagen de salida.
    for (j = 0; j < primerCabeceraBMP.altoBitMap; j++) {
        for (i = 0; i < primerCabeceraBMP.anchoBitMap; i++) {
            fwrite(&pixelesPrimerImagen[j][i * 3], sizeof (unsigned char), 1, punteroImagenSalida);
            fwrite(&pixelesPrimerImagen[j][(i * 3) + 1], sizeof (unsigned char), 1, punteroImagenSalida);
            fwrite(&pixelesPrimerImagen[j][(i * 3) + 2], sizeof (unsigned char), 1, punteroImagenSalida);
        }
    }*/

    //fwrite(pixelesPrimerImagen, sizeof (unsigned char), primerCabeceraBMP.altoBitMap * primerCabeceraBMP.anchoBitMap * 3, punteroImagenSalida);
    /*
for (j=0; j<primerCabeceraBMP.altoBitMap; j++){
            for (i=0; i<primerCabeceraBMP.anchoBitMap; i++){
                    ///BORRAR
			
                    //blue = (pixelesPrimerImagen[i*3][j] + pixelesSegundaImagen[i*3][j]) / 2;
                    //green = (pixelesPrimerImagen[(i*3)+1][j] + pixelesSegundaImagen[(i*3)+1][j]) / 2;
                    //red = (pixelesPrimerImagen[(i*3)+2][j] + pixelesSegundaImagen[(i*3)+2][j]) / 2;
                    blue = (pixelesPrimerImagen[j][i*3] + pixelesSegundaImagen[j][i*3]) / 2;
                    green = (pixelesPrimerImagen[j][(i*3)+1] + pixelesSegundaImagen[j][(i*3)+1]) / 2;
                    red = (pixelesPrimerImagen[j][(i*3)+2] + pixelesSegundaImagen[j][(i*3)+2]) / 2;
                    fwrite(&blue, sizeof(unsigned char), 1, punteroImagenSalida);
                    fwrite(&green, sizeof(unsigned char), 1, punteroImagenSalida);
                    fwrite(&red, sizeof(unsigned char), 1, punteroImagenSalida);
            }
    }*/
    
    for (i = 0; i < numFilasPrimerImagen; i++) {
        free(pixelesPrimerImagen[i]);
    }
    free(pixelesPrimerImagen);
    
    fclose(punteroImagenSalida);

    // Muestro el tiempo transcurrido en realizar la tarea.
    printf("%d, %d, %d, %f\n", cantThreads, primerCabeceraBMP.anchoBitMap, primerCabeceraBMP.altoBitMap, tiempoTranscurrido);

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
        //arreglo[i] = (unsigned char*) malloc(sizeof (unsigned char) * numCol);
        // Se utiliza calloc en lugar de malloc para que cuando se combinan las imagenes el relleno de las imagenes sea cero y no basura.
        arreglo[i] = (unsigned char*) calloc(numCol, sizeof (unsigned char));

        if (arreglo[i] == NULL) {
            printf("ERROR >> No se pudo crear el arreglo.\n");
            return NULL;
        }
    }

    return arreglo;
}
