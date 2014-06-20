#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

// Prototipos
unsigned char** crearArregloPixeles(int, int);

struct BMP_Header{
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

int main(int argc, char** argv){
    char nombrePrimerImagen[35];
    char nombreSegundaImagen[35];
    char nombrePrimerImagenBlancoNegro[35] = "tempErroneo_";
    char nombreSegundaImagenBlancoNegro[35] = "tempErroneo_";
    char nombreImagenCombinada[35] = "salidaErronea.bmp";
    
    struct BMP_Header primerCabeceraBMP;
    struct BMP_Header segundaCabeceraBMP;
    
    FILE *punteroPrimerImagen = NULL;
    FILE *punteroSegundaImagen = NULL;
    FILE *punteroPrimerImagenBlancoNegro = NULL;
    FILE *punteroSegundaImagenBlancoNegro = NULL;
    FILE *punteroImagenSalida = NULL;  
    
    int cantThreads;
    
    time_t comienzoTrabajoParalelo, finalizaTrabajoParalelo;
    
    
    if (argc == 4){
		cantThreads = atoi(argv[1]);
        strcpy(nombrePrimerImagen, argv[2]);
        strcpy(nombreSegundaImagen, argv[3]);
    }
    else{
        printf("ERROR >> El programa debe ser invocado con tres parametros indicando la cantidad de threads a usar y las imagenes a transformar.\n");
        return 1;
    }
    
    strcat(nombrePrimerImagenBlancoNegro, nombrePrimerImagen);
    strcat(nombreSegundaImagenBlancoNegro, nombreSegundaImagen);
    
    omp_set_num_threads(cantThreads);

    punteroPrimerImagen = fopen(nombrePrimerImagen, "r");
    punteroSegundaImagen = fopen(nombreSegundaImagen, "r");
    punteroPrimerImagenBlancoNegro = fopen(nombrePrimerImagenBlancoNegro, "w");
    punteroSegundaImagenBlancoNegro = fopen(nombreSegundaImagenBlancoNegro, "w");
    punteroImagenSalida = fopen(nombreImagenCombinada, "w");

    if (punteroPrimerImagen == NULL){
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para lectura\n",nombrePrimerImagen);
        return 1;
    }
    
    if (punteroSegundaImagen == NULL){
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para lectura\n",nombreSegundaImagen);
        return 1;
    }

    if (punteroPrimerImagenBlancoNegro == NULL){
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n",nombrePrimerImagenBlancoNegro);
        return 1;
    }

    if (punteroSegundaImagenBlancoNegro == NULL){
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n",nombreSegundaImagenBlancoNegro);
        return 1;
    }
    
    if (punteroImagenSalida == NULL){
        printf("ERROR >> No se pudo abrir el archivo \"%s\" para escritura\n",nombreImagenCombinada);
        return 1;
    }
    
    fread(&primerCabeceraBMP.tipo, sizeof (char), 2, punteroPrimerImagen);
    fread(&primerCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroPrimerImagen);
    fread(&primerCabeceraBMP.offsetArregloPixeles, sizeof (unsigned  int), 1, punteroPrimerImagen);
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
    
    fread(&segundaCabeceraBMP.tipo, sizeof (char), 2, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroSegundaImagen);
    fread(&segundaCabeceraBMP.offsetArregloPixeles, sizeof (unsigned  int), 1, punteroSegundaImagen);
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
    
    fseek(punteroPrimerImagen, primerCabeceraBMP.offsetArregloPixeles, SEEK_SET);
    fseek(punteroSegundaImagen, segundaCabeceraBMP.offsetArregloPixeles, SEEK_SET);
    
    unsigned char red, green, blue;
        
    int numFilasPrimerImagen = primerCabeceraBMP.altoBitMap;
    int numColPrimerImagen = primerCabeceraBMP.anchoBitMap * 3;
    
    int numFilasSegundaImagen = segundaCabeceraBMP.altoBitMap;
    int numColSegundaImagen = segundaCabeceraBMP.anchoBitMap * 3;
    
    unsigned char **pixelesPrimerImagen = crearArregloPixeles(numFilasPrimerImagen, numColPrimerImagen);
    if (pixelesPrimerImagen == NULL){
		printf("ERROR >> No se pudo crear el arreglo para los pixeles de la primer imagen.\n");
		return 1;
	}
	
    unsigned char **pixelesSegundaImagen = crearArregloPixeles(numFilasSegundaImagen, numColSegundaImagen);
    if (pixelesSegundaImagen == NULL){
		printf("ERROR >> No se pudo crear el arreglo para los pixeles de la segunda imagen.\n");
		return 1;
	}
	
    int i, j;
    int valorPromedio = 0;
    
    comienzoTrabajoParalelo = time(NULL);
    
    #pragma omp parallel private (blue, green, red, valorPromedio, i) shared (primerCabeceraBMP, pixelesPrimerImagen, j, segundaCabeceraBMP, pixelesSegundaImagen)
    {
		#pragma omp for
		for (j=0; j<primerCabeceraBMP.altoBitMap; j++){
			for (i=0; i<primerCabeceraBMP.anchoBitMap; i++){
				if (fread(&blue, sizeof(unsigned char), 1, punteroPrimerImagen) != 1){
					printf("ERROR >> No se pudo leer el pixel (%d,%d) azul de la primer imagen\n", j, i);
				}
				if (fread(&green, sizeof(unsigned char), 1, punteroPrimerImagen) != 1){
					printf("ERROR >> No se pudo leer el pixel (%d,%d) verde de la primer imagen\n", j, i);
				}
				if (fread(&red, sizeof(unsigned char), 1, punteroPrimerImagen) != 1){
					printf("ERROR >> No se pudo leer el pixel (%d,%d) rojo de la primer imagen\n", j, i);
				}
				valorPromedio = blue + red + green;
				valorPromedio = (int)(valorPromedio / 3);
				pixelesPrimerImagen[j][i*3] = (unsigned char)valorPromedio;
				pixelesPrimerImagen[j][(i*3)+1] = (unsigned char)valorPromedio;
				pixelesPrimerImagen[j][(i*3)+2] = (unsigned char)valorPromedio;
			}
		}
		
		#pragma omp for
		for (j=0; j<segundaCabeceraBMP.altoBitMap; j++){
			for (i=0; i<segundaCabeceraBMP.anchoBitMap; i++){
				if (fread(&blue, sizeof(unsigned char), 1, punteroSegundaImagen) != 1){
					printf("ERROR >> No se pudo leer el pixel (%d,%d) azul de la segunda imagen\n", j, i);
				}
				if (fread(&green, sizeof(unsigned char), 1, punteroSegundaImagen) != 1){
					printf("ERROR >> No se pudo leer el pixel (%d,%d) verde de la segunda imagen\n", j, i);
				}
				if (fread(&red, sizeof(unsigned char), 1, punteroSegundaImagen) != 1){
					printf("ERROR >> No se pudo leer el pixel (%d,%d) rojo de la segunda imagen\n", j, i);
				}
				valorPromedio = blue + red + green;
				valorPromedio = (int)(valorPromedio / 3);
				
				pixelesSegundaImagen[j][i*3] = (unsigned char)valorPromedio;
				pixelesSegundaImagen[j][(i*3)+1] = (unsigned char)valorPromedio;
				pixelesSegundaImagen[j][(i*3)+2] = (unsigned char)valorPromedio;
			}
		}
	}
	
	finalizaTrabajoParalelo = time(NULL);
	
	double tiempoTranscurrido = difftime(finalizaTrabajoParalelo, comienzoTrabajoParalelo);


    fwrite(&primerCabeceraBMP.tipo, sizeof (char), 2, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroPrimerImagenBlancoNegro);
    fwrite(&primerCabeceraBMP.offsetArregloPixeles, sizeof (unsigned  int), 1, punteroPrimerImagenBlancoNegro);
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
	
	fseek(punteroPrimerImagenBlancoNegro, primerCabeceraBMP.offsetArregloPixeles, SEEK_SET);
	
    for (j=0; j<primerCabeceraBMP.altoBitMap; j++){
		for (i=0; i<primerCabeceraBMP.anchoBitMap; i++){
			fwrite(&pixelesPrimerImagen[j][i*3], sizeof(unsigned char), 1, punteroPrimerImagenBlancoNegro);
			fwrite(&pixelesPrimerImagen[j][(i*3)+1], sizeof(unsigned char), 1, punteroPrimerImagenBlancoNegro);
			fwrite(&pixelesPrimerImagen[j][(i*3)+2], sizeof(unsigned char), 1, punteroPrimerImagenBlancoNegro);
		}
	}
	
	
    fwrite(&segundaCabeceraBMP.tipo, sizeof (char), 2, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroSegundaImagenBlancoNegro);
    fwrite(&segundaCabeceraBMP.offsetArregloPixeles, sizeof (unsigned  int), 1, punteroSegundaImagenBlancoNegro);
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
	
	fseek(punteroSegundaImagenBlancoNegro, segundaCabeceraBMP.offsetArregloPixeles, SEEK_SET);
	
    for (j=0; j<segundaCabeceraBMP.altoBitMap; j++){
		for (i=0; i<segundaCabeceraBMP.anchoBitMap; i++){
			fwrite(&pixelesSegundaImagen[j][i*3], sizeof(unsigned char), 1, punteroSegundaImagenBlancoNegro);
			fwrite(&pixelesSegundaImagen[j][(i*3)+1], sizeof(unsigned char), 1, punteroSegundaImagenBlancoNegro);
			fwrite(&pixelesSegundaImagen[j][(i*3)+2], sizeof(unsigned char), 1, punteroSegundaImagenBlancoNegro);
		}
	}	

    fwrite(&primerCabeceraBMP.tipo, sizeof (char), 2, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.tamanioArchivo, sizeof (unsigned int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.reservado1, sizeof (unsigned short int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.reservado2, sizeof (unsigned short int), 1, punteroImagenSalida);
    fwrite(&primerCabeceraBMP.offsetArregloPixeles, sizeof (unsigned  int), 1, punteroImagenSalida);
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
	
	fseek(punteroImagenSalida, primerCabeceraBMP.offsetArregloPixeles, SEEK_SET);
	
	comienzoTrabajoParalelo = time(NULL);
	
	#pragma omp parallel private (i) shared (primerCabeceraBMP, pixelesPrimerImagen, pixelesSegundaImagen, j)
    {
		#pragma omp for
		
		for (j=0; j<primerCabeceraBMP.altoBitMap; j++){
			for (i=0; i<primerCabeceraBMP.anchoBitMap; i++){
				pixelesPrimerImagen[j][i*3] = (pixelesPrimerImagen[j][i*3] + pixelesSegundaImagen[j][i*3]) / 2;
				pixelesPrimerImagen[j][(i*3)+1] = (pixelesPrimerImagen[j][(i*3)+1] + pixelesSegundaImagen[j][(i*3)+1]) / 2;
				pixelesPrimerImagen[j][(i*3)+2] = (pixelesPrimerImagen[j][(i*3)+2] + pixelesSegundaImagen[j][(i*3)+2]) / 2;
			}
		}
	}
	
	finalizaTrabajoParalelo = time(NULL);
	
	tiempoTranscurrido += difftime(finalizaTrabajoParalelo, comienzoTrabajoParalelo);
	
	for (j=0; j<primerCabeceraBMP.altoBitMap; j++){
		for (i=0; i<primerCabeceraBMP.anchoBitMap; i++){
			fwrite(&pixelesPrimerImagen[j][i*3], sizeof(unsigned char), 1, punteroImagenSalida);
			fwrite(&pixelesPrimerImagen[j][(i*3)+1], sizeof(unsigned char), 1, punteroImagenSalida);
			fwrite(&pixelesPrimerImagen[j][(i*3)+2], sizeof(unsigned char), 1, punteroImagenSalida);
		}
	}
	
	printf("%d, %d, %d, %f\n", cantThreads, primerCabeceraBMP.anchoBitMap, primerCabeceraBMP.altoBitMap, tiempoTranscurrido);
		
    return 0;
}


unsigned char** crearArregloPixeles(int numFilas, int numCol){
	unsigned char **arreglo;
	int i;
	
	arreglo = (unsigned char**)malloc(sizeof(unsigned char*) * numFilas);
	
	if (arreglo == NULL){
		printf("ERROR >> No se pudo crear el arreglo.\n");
		return NULL;
	}
	
	for (i=0; i<numFilas; i++){
		arreglo[i] = (unsigned char*)malloc(sizeof(unsigned char) * numCol);
		
		if (arreglo[i] == NULL){
			printf("ERROR >> No se pudo crear el arreglo.\n");
			return NULL;
		}
	}
	
	return arreglo;
}
