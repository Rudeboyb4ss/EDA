#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/***************************************************************************************
El siguiente programa ha sido desarrollado por Jorge Sandoval, Rut 19.233.004-1, 
estudiante de la Universidad de Santiago de Chile. 
El objetivo principal es calcular el determiante de una matriz cuadrada de orden NxN.
La entrada debe ser un archivo de tipo .in con una matriz con un formato específico.
Las variables se trabajarán como double ya que se trabajo con la función POW que retorna
un double.
****************************************************************************************/

//Funcion: calcular determinante.
//DOM: Matriz (arreglo) 
//REC: Numero formato long double.
long double determinante(double ** matriz , int orden){
	//se definen las variables para almacenar los resultados.
	long double det = 0 , aux = 0;
	//Esta variable permitirá rellenar la matriz cofactor.
	int ColumanaAux;
	//Caso base: Determinante de una matriz de 2x2.
	if (orden == 2)
		return (matriz[0][0]*matriz[1][1] - matriz[1][0]*matriz[0][1]);
	
	else{
		//Se inicia una variable de 0 hasta el orden actual.
		int j;
		for(j=0; j < orden;j++){
			//Se crea la matriz cofactor por cada vuelta del ciclo pero de un orden menor.
			double**cofactor = (double **)malloc(sizeof(double)*(orden-1)); 
			int i;
   			for (i=0; i<(orden-1);i++) 
      			cofactor[i] = (double*)malloc(sizeof(double)*(orden-1)); 
      	//se recorren las filas.
      	int fila;
      	for (fila=1; fila < orden; fila++){
      		//se reinicia la variable columna aux.
      		ColumanaAux = 0;
      		//se recorren las columnas
      		int columna;
      		for (columna=0; columna < orden; columna++){
      			//se establece cual será la fila y columna que se eliminará.
      			if (columna != j){
      				//se rellena la matriz cofactor.
      				cofactor[fila-1][ColumanaAux] = matriz[fila][columna];
      				ColumanaAux++;
      			}
      		}
      	}
      	//se realiza la operacion donde se establece el determinante, el signo segun matriz de signos 
      	//y se hace el llamado recursivo.
      	aux = (pow(-1, 2+j) * matriz[0][j] * determinante(cofactor,orden-1));
      	det = det + aux;

      	//Se libera memoria reservada para la matriz cofactor.
      	int q;
      	for (q=0; q < orden-1 ;q++)
      		free(cofactor[q]);
      	free(cofactor);
		}
	//Se retorna el determinante obtenido en el caso else.
	return det;
	}
}

//Funcion: Leer Matriz 
//DOM: archivo matriz.in
//REC: void
void LeerMatriz(){
   FILE *fichero;
   //se crea variable para guardar el orden de la matriz.
   int n = 0;
   //se abre el archivo.
   //************************************************
   fichero = fopen("matriz-2333148719.in","r");
   //************************************************
   //Si no se puede abrir.
   if (fichero==NULL){
   	  //se notifica.
      printf( "No se puede abrir el fichero.\n" );
      //Se corta ejecución.
      exit (-1);
   }

   //toma el primer valor del archivo para asignar memoria a matriz.
   fscanf (fichero, "%d", &n);
   //se reserva memoria para la matriz.
   double ** matriz = (double **)malloc(sizeof(double)*n); 
   int i;
   for (i=0; i<n;i++) 
      matriz[i] = (double*)malloc(sizeof(double)*n); 

   //leer datos y rellenar matriz 
   for (i=0; i < n;++i){
   		int j;
      for (j=0; j < n;++j){
         fscanf(fichero,"%lf", &matriz[i][j]);
      }
   }
   //Se cierra el archivo.
   fclose(fichero);
   //se imprime la matriz para que el cliente pueda verificar errores.
   printf( "\n\nMatriz proporcionada:\n" );
   for (i = 0; i < n; i++) {
   		int j;
      for (j = 0; j < n; j++)
	 printf ("%d ", (int)matriz[i][j]);
      printf ("\n");
   }
   printf("Esta matriz es de (%dx%d).\n",n,n);

   //Se calcula el determinante, entregando la matriz y el orden.
   long double det = determinante(matriz, n);
   //Se muentra el resultado obtenido.
   printf("\nEl determinante obtenido ha sido: %ld. \n\n",(long int)det);
}

int main(int argc, char const *argv[]){
	//Se llama a la funcion que lee y realiza llamados de procesamiento.
	LeerMatriz();
	return 0;
}