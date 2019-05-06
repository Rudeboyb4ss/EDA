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
typedef struct MatrizDispersa{
   int fila;
   int Columna;
   double dato;  
   struct MatrizDispersa * siguiente; 
}MD;

MD * primero, *ultimo;

//Con esta función se añade un elemento al final de la lista.

void añadir(int filaActual, int columnaActual, double datoActual) {
   MD *nuevo;
   // reservamos memoria para el nuevo elemento.
   nuevo = (MD *) malloc (sizeof(MD));
   /*if (nuevo==NULL) 
      printf( "No hay memoria disponible!\n");*/
   //seguarda la fila.
   nuevo->fila = filaActual;
   //se guarda la columna.
   nuevo->Columna = columnaActual;
   //se guarda el dato.
   nuevo-> dato = datoActual;
   //el campo siguiente va a ser NULL por ser el último elemento de la lista
   nuevo->siguiente = NULL;
 
   // ahora metemos el nuevo elemento en la lista. lo situamos al final de la lista.
   //comprobamos si la lista está vacía.
      if (primero==NULL) {
         primero = nuevo;
         ultimo = nuevo;
      }
      else {
      // el que hasta ahora era el último tiene que apuntar al nuevo.
         ultimo->siguiente = nuevo;
      // hacemos que el nuevo sea ahora el último.
         ultimo = nuevo;
      }
 }
 
 void MostrarListaEnlazada() {
      MD *auxiliar; // lo usamos para recorrer la lista.
      int i=0;
      auxiliar = primero;
      printf("\nMostrando la lista completa:\n");

      while (auxiliar!=NULL) {
            printf( "[fila %d,columna %d, dato %f]\n",auxiliar->fila,auxiliar->Columna,auxiliar->dato);
            auxiliar = auxiliar->siguiente;
            i++;
      }
      if (i==0) printf( "\nLa lista está vacía!!\n" );
 }


int powMatriz(double exp){
   MD * auxiliar;
   int i;
   i= 0;
   auxiliar = primero;
   while (auxiliar!= NULL){
   auxiliar->dato = pow(auxiliar->dato,exp);
   auxiliar =auxiliar->siguiente;
   i++;
   }
   return i;
}

void MostrarMatriz(int n,int contador){
   int matriz[n][n];
   int i;
   for (i = 0; i < n; ++i){
      int j;
      for (j = 0; j < n; ++j){
         matriz[i][j]= 0;
      }
   }

   MD *auxiliar; // lo usamos para recorrer la lista.
   auxiliar = primero;
   for (int i = 0; i < contador; ++i){
      matriz[auxiliar->fila][auxiliar->Columna] = (int)(auxiliar->dato);
      auxiliar = auxiliar->siguiente;
   }
   printf("La Matriz resultante es:\n");
   int l;
   for (l = 0; l < n; ++l){
      int m;
      for (m = 0; m < n; ++m){
         printf(" %d ",matriz[l][m]);
      }
      printf("\n");
   }  

   int bitsOcupados = (contador * 8) + (((n*n) - contador) *4);
   int bitsReales = ((n*n) * 8);
   printf("El tamaño de la matriz dispersa es: %d bytes.\n",bitsOcupados);
   printf("El tamaño de la matriz completa habría sido: %d bytes.\n",bitsReales);
}

//Funcion: Leer Matriz 
//DOM: archivo matriz.in
//REC: void
void LeerMatriz(){

   FILE *fichero;
   //se crea variable para guardar el orden de la matriz.
   int n = 0;
   double exp = 0;

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

   //toma el primer valor para guardar el tamaño de la matriz.
   fscanf (fichero, "%d", &n);
   //printf("La matriz otorgada es de (%d,%d).\n",n,n);
   //toma el segundo valor para saber a que numero se elevará la matriz.
   fscanf (fichero, "%lf", &exp);
   //printf("El exponente otorgado ha sido :%lf. \n", exp);
   //se reserva memoria para la matriz.

   //leer datos y rellenar matriz 
   int i;
   for (i=0; i < n;++i){
   		int j;
      for (j=0; j < n;++j){
         double DatoLeido;
         fscanf(fichero,"%lf", &DatoLeido);
         if(DatoLeido != 0){
            añadir(i,j,DatoLeido);
         }

      }
   }
   //Se cierra el archivo.
   fclose(fichero);

   int contador = powMatriz(exp);
   MostrarMatriz(n,contador);


}

int main(int argc, char const *argv[]){
   primero = (MD *) NULL;
   ultimo = (MD *) NULL;
	//Se llama a la funcion que lee y realiza llamados de procesamiento.
	LeerMatriz();
   //MostrarListaEnlazada();
	return 0;
}