transfBMPSec: transfBMPSec.c
	 gcc -o transfBMPSec transfBMPSec.c -Wall

imageCreator: imageCreator.c
	 gcc -o imageCreator imageCreator.c -Wall
	 
transfBMPPar: transfBMPPar.c
	 gcc -fopenmp -o transfBMPPar transfBMPPar.c -Wall	 
	 
transfBMPParPrueba: transfBMPParPrueba.c
	 gcc -fopenmp -o transfBMPParPrueba transfBMPParPrueba.c -Wall
	 
transfBMPParErroneo: transfBMPParErroneo.c
	 gcc -fopenmp -o transfBMPParErroneo transfBMPParErroneo.c -Wall
