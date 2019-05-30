#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MostrarMatrizAd(int ** grafo, int vertices){

	for (int i = 0; i < vertices; ++i){
		for (int j = 0; j < vertices; ++j){
			printf("%d ",grafo[i][j]);
		}
		printf("\n");
	}
}

void VerificarGrafo(){

}

void BusquedaProfundidad(int ** grafo, int vertices,int* revisados, int i){
    revisados[i]=1;
	
	for(int j=0;j<vertices;j++)
       if(!revisados[j] && grafo[i][j] == 1)
            BusquedaProfundidad(grafo,vertices,revisados,j);
}

int VerificarCiclos(int ** grafo,int vertices){
	int bolean=0;
	int revisados[vertices];
	//se llena la lista de ceros.
	for(int i=0;i<vertices;i++)
    	revisados[i]=0;

    BusquedaProfundidad(grafo,vertices,revisados,0);

    for(int i=0;i<vertices;i++)
    	printf("%d ",revisados[i]);

    printf("\n");
	return bolean;
}

void VerificarRegular(int ** grafo){

}

void PonerPesos(int** grafo){

}


void RellenarGrafo(int**grafo,int vertices,int aristas,int ciclos,int regular,int gMax,int gMin, int pesos){
	printf("Entre a rellenar\n");
	//se rellena la matriz con ceros.
	for (int i = 0; i < vertices; ++i){
		for (int j = 0; j < vertices; ++j){
			grafo[i][j] = 0;
		}
	}
	//MostrarMatrizAd(grafo,vertices);
	int AristasAux = aristas;
	int seed=0;
	int AuxPosX,AuxPosY;
	//Se rellena la matriz adyacente del grafo
	while(AristasAux > 0){
		AuxPosX = (rand()+(seed+19))%vertices;
		AuxPosY = (rand()+seed)%vertices;

		if ((grafo[AuxPosX][AuxPosY]==0) && (AuxPosY!=AuxPosX)){
			//se cambia por 1
			grafo[AuxPosX][AuxPosY] = 1;
			grafo[AuxPosY][AuxPosX] = 1;

			AristasAux = AristasAux-1;
		}
		//Evita el segmentation fault cuando no cumple la condición.
		seed = seed+1;
	}

	MostrarMatrizAd(grafo,vertices);

	int c = VerificarCiclos(grafo,vertices);
}

void CrearGrafo(int vertices,int aristas,int ciclos,int regular,int gMax,int gMin, int pesos){
	printf("Entre a crear\n");
	int ** grafo = (int **)malloc(vertices*sizeof(int*)); 
   	for (int i=0; i < vertices;i++) 
    	grafo[i] = (int*)malloc(vertices* sizeof(int)); 
    //printf("Entre a crear grafo!\n");
    RellenarGrafo(grafo,vertices,aristas,ciclos,regular,gMax,gMin,pesos);
    printf("El Grafo ha sido creado con exito!.\n");
}


int main(int argc, char const *argv[]){
	srand (time(NULL));
	int modo = atoi(argv[1]);
	if(argc!=3 && argc !=9){
			printf("Ha ingresado mal los parametros, verifique e intente denuevo.\n");
			return 0;
	}

	switch(modo){
		case(1):
				//verifica entradas
				if(argc == 3 || (atoi(argv[4])!=0 && atoi(argv[4])!=1) || (atoi(argv[5])!=0 && atoi(argv[5])!=1)){
					printf("Ha ingresado mal los parametros, verifique e intente de nuevo.\n");
					break;
				}
				//verifica parametro "regular"
				if (atoi(argv[5]) == 1){
					if (atoi(argv[6]) != atoi(argv[7])){
						printf("Ha ingresado mal los parametros, se ha detectado un grafo regular por lo que el grado máximo y minimo deben ser iguales.\n");
						break;
					}
				}
				//Evita que se ingresen mas aristas de las que puede generar
				int MaxArista = 0;
				for (int i = 0; i < atoi(argv[2]); ++i){
					MaxArista = MaxArista + i;
				}
				if (MaxArista < atoi(argv[3])){
					printf("Ha excedido el numero maximo de aristas, verifique e intente denuevo.\n");
					printf("El numero maximo de aristas posibles es: %d.\n",MaxArista);
					break;
				}
				//printf("Entre a caso 1\n");
				CrearGrafo(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]),atoi(argv[6]),atoi(argv[7]),atoi(argv[8]));
				break;

		case (2):
			if (argc ==9){
				printf("Ha ingresado mal los parametros, verifique e intente denuevo.\n");
				break;
			}

			//printf("Entre a caso 2\n");
			VerificarGrafo();
			break;

		default:
			printf("Ha ingresado mal los parametros, verifique e intente denuevo.\n");
	}

	return 0;
}