#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Se inclute math para trabajar con POW.

/***************************************************************************************
El siguiente programa ha sido desarrollado por Jorge Sandoval, Rut 19.233.004-1, 
estudiante de la Universidad de Santiago de Chile. 
El objetivo principal es calcular la potencia de una matriz dispersa cuadrada orden NxN.
La entrada debe ser un archivo de tipo .in con una matriz con un formato específico.
Las variables se trabajarán como double ya que se trabajo con la función POW que retorna
un double.
****************************************************************************************/

//Se define la estructura NODO para crear una lista enlazada.
typedef struct MatrizDispersa{
   //4 bytes.
   int fila;
   //4 bytes.
   int Columna;
   //8 bytes.
   double dato;  
   struct MatrizDispersa * siguiente; 
}MD;

//Estos punteros permitiran agregar elementos a la lista, se inicializarán en main apuntando 
//a NULL.
MD * primero, *ultimo;

//Funcion: anadir al final. (cola)
//Descripción: Añade un nuevo elemento a la Lista Enlazada
//DOM: enteros fila, columna y double dato.
//REC: Void.

void anadir(int filaActual, int columnaActual, double datoActual){
   MD *nuevo;
   // reservamos memoria para el nuevo elemento.
   nuevo = (MD *) malloc (sizeof(MD));
   //se guarda la fila.
   nuevo->fila = filaActual;
   //se guarda la columna.
   nuevo->Columna = columnaActual;
   //se guarda el dato.
   nuevo-> dato = datoActual;
   //el campo siguiente va a ser NULL por ser el último elemento de la lista
   nuevo->siguiente = NULL;
 
   //Se comprueba si la lista esta vacia.
   if(primero==NULL){
      primero = nuevo;
      ultimo = nuevo;
   }
   else{
   //el último tiene que apuntar al nuevo.
      ultimo->siguiente = nuevo;
   //el nuevo ahora será el último.
      ultimo = nuevo;
   }
}

//Funcion: Mostrar Lista Enlazada. 
//Descripción: Funcion que muestra por consola la Lista Enlazada.
//DOM: Void.
//REC: Void.
void MostrarListaEnlazada(){
   //Para recorrer la lista se crea un auxiliar.
   MD *auxiliar;
   int i=0;
   auxiliar = primero;
   printf("\nMostrando la lista completa:\n");
   //Recorre lista hasta encontrar un puntero a NULL.
   while (auxiliar!=NULL){
      printf( "[fila %d,columna %d, dato %f]\n",auxiliar->fila,auxiliar->Columna,auxiliar->dato);
      auxiliar = auxiliar->siguiente;
      i++;
   }
   //En caso de que no exista ningun elemento (no entra al WHILE)
   if (i==0) printf( "\nLa lista está vacía!!\n" );
}

//Funcion: Pow Matriz
//Descripción: Funcion que eleva un elemento "a" a un exponente "b".
//DOM: double Exponente
//REC: entero "contador".
int powMatriz(double exp){
   //Para trabajar lista enlazada.
   MD * auxiliar;
   int i;
   i= 0;
   auxiliar = primero;
   //Se recorre hasta encontrar un puntero que apunte a NULL.
   while (auxiliar!= NULL){
      //Reemplazamos el dato antiguo por el nuevo elevado a exp.
      auxiliar->dato = pow(auxiliar->dato,exp);
      //Se avanza al siguiente nodo.
      auxiliar =auxiliar->siguiente;
      //aumenta el contador.
      i++;
   }
   //Se retorna i como contador ya que servirá para guardar cuantos elementos
   //tiene la lista enlazada.
   return i;
}

//Funcion: Mostrar Matriz.
//Descripción: Funcion que imprime la lista enlazada con formato de matriz.
//DOM: entero n y contador.
//REC: Void.
void MostrarMatriz(int n,int contador){  
   //Para trabajar la lista enlazada.
   MD *auxiliar;
   //Auxiliar se sitúa en el primer nodo.
   auxiliar = primero;
   int i;
   //Se recorre con for hasta el tamaño de la matriz inicial N.
   for (i = 0; i < n; ++i){
      int j;
      for (j = 0; j < n; ++j){
         //Si existe un elemento en la lista enlazada imprime el dato.
         if (auxiliar->fila == i && auxiliar->Columna == j){
            printf(" %d ",(int)auxiliar->dato);
            //Se avanza al siguiente nodo.
            auxiliar = auxiliar->siguiente;
         }
         //Si no, imprimirá un 0 para simular la matriz inicial.
         else
            printf(" 0 ");
      }
      printf("\n");
   }
   //La estructura ocupa 1 Double (8 bytes) y 2 enteros (4 bytes).
   long int bitsOcupados = (contador * 16) + (((n*n) - contador) *4);
   long int bitsReales = ((n*n) * 16);
   printf("El tamaño de la matriz dispersa es: %ld bytes.\n",bitsOcupados);
   printf("El tamaño de la matriz completa habria sido: %ld bytes.\n",bitsReales);
}

//Funcion: Leer Matriz 
//Descripción: Funcion que procesa el archivo 
//DOM: archivo matriz.in
//REC: void
void LeerMatriz(){
   FILE *fichero;
   //se crea variable para guardar el orden de la matriz.
   int n = 0;
   double exp = 0;

   //se abre el archivo.
   //************************************************
   fichero = fopen("MatrizPrueba.in","r");
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
   //toma el segundo valor para saber a que numero se elevará la matriz.
   fscanf (fichero, "%lf", &exp);
   printf("La matriz dispersa otorgada es de [%d,%d].\n",n,n);
   printf("El exponente otorgado ha sido: >%d<2.\n", (int)exp);

   //Se Recorren los elementos del archivo.
   int i;
   for (i=0; i < n;++i){
   		int j;
      for (j=0; j < n;++j){
         //Se declara la variable dato leido para almacenar el dato actual.
         double DatoLeido;
         //se busca un dato que coincida.
         fscanf(fichero,"%lf", &DatoLeido);
         //Si el dato es distinto de cero.
         if(DatoLeido != 0){
            //Se añade a la Lista Enlazada guardando su posición.
            anadir(i,j,DatoLeido);
         }

      }
   }

   //Se cierra el archivo.
   fclose(fichero);

   //Se eleva la Matriz a el exponente entregado y se procesa para obtener el contador.
   //contador = cantidad de elementos en la lista.
   int contador = powMatriz(exp);
   //Se imprime la Matriz al usuario con el formato solicitado.
   MostrarMatriz(n,contador);
}

int main(int argc, char const *argv[]){
   //Ya que no existen elementos en la Lista,Primero y Ultimo apuntarán a NULL.
   primero = (MD *) NULL;
   ultimo = (MD *) NULL;
	//Se llama a la funcion que lee y realiza llamados de procesamiento.
	LeerMatriz();
   //Si el usuario desea puede imprimir la lista enlazada para entender como trabaja.
   //MostrarListaEnlazada();
	return 0;
}