 /*
 * =====================================================================================
 *
 *    Asignacion:  Proyecto 2
 *
 *        Version:  1.0.0
 *  Fecha: 11 de noviembre de 2022
 *      Compilador:  gcc
 *
 * Autor:  Yurgen Cambronero Mora
 *  Curso:  Estructuras de Datos
 *
 * =====================================================================================
 */

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANNO_MAXIMO 	1024*1024		// Longitud máxima de la tabla
#define SI			1
#define NO			0
#define ENVIA		1
#define RECIBE		0

typedef struct nodo{
	char* valor;
	int interes;
	struct tabla_hash* tabla;
	struct nodo* sigt;
}nodito;

typedef struct lista{
	nodito* inicio;
}listilla;

nodito* crear_nodo(char* texto){
    nodito* nn = calloc(1, sizeof(nodito));
	nn -> valor = texto;
	return nn;
}

typedef struct nodo_c{
	struct lista* archivos;
	char* terminos;
	int valor;
	struct nodo_c* izq;
	struct nodo_c* der;
}noditoc

typedef struct arbol_c{
	struct nodo_c* raiz;
}arbolitoc

noditoc* crear_nodo_c(char* termino, listilla* archivo){
	noditoc* nn = calloc(1, sizeof(noditoc));
	nn -> terminos = termino;
	nn -> archivos = archivo;
	nn -> valor = strlen(termino);
	return nn;
}

/* Funciones Lista */

/*
	Función para insertar al final de una lista
*/
void insertar_al_final(listilla* lista, char* annadir) {
	/* Declaración de inicio */
	nodito* act = lista -> inicio; 	//Inicia la lista
	
	/* Condicionales */
	if (act == NULL) { 	//Si la lista esta vacia
		nodito* nn = crear_nodo(annadir); 	//Crea un nodo
		lista -> inicio = nn; 	//Y lo annade
		return;
		
	} else {	//Funcion en si
		while(act -> sigt != NULL) {
			act = act -> sigt; 	//Busca en la lista al último espacio
		}
		nodito* nn = crear_nodo(annadir); 	//Crea un nodo
		act -> sigt = nn; 	//Vincula el nodo actual con el nuevo
	}
}

/*
	 Función para eliminar un elemento de una lista
*/
void eliminar(listilla*lista, int n) {
	/* Declaración de inicio y variables */
	nodito* act = lista -> inicio; 	//Inicia la lista
	nodito* bor = NULL; 	//Se crea un eliminador
	int pos = 0;
	
	/* Funcion en si */
	if (n == 0 || act == NULL) { 	//Si la lista esta vacia pues...
		printf("\n");
	} while (act != NULL && pos != n) { 	//Sino
		lista -> inicio = act -> sigt; 	//Se mueve inicio
		bor = act; 	//Agarra el nodo
		act = act -> sigt; 	//Conecta al actual con el siguiente
		free(bor); 	//Le hace el free
		bor = NULL; 	//Y vuelve a limpiar bor
		pos ++;
	}
}

/*
	Función para eliminar una lista
*/
void eliminar_lista(listilla*lista) {
	/* Declaración de inicio y variables */
	nodito* act = lista -> inicio; 	//Inicia la lista
	nodito* bor = NULL; 	//Se crea un eliminador
	
	/* Funcion en si */
	if (act == NULL) { 	//Si la lista esta vacia pues...
		printf("	La lista ya esta vacia\n");
	} while (act != NULL) { 	//Sino
		bor = act; 	//Agarra el nodo
		act = act -> sigt; 	//Conecta al actual con el siguiente
		free(bor); 	//Le hace el free
		bor = NULL; 	//Y vuelve a limpiar bor
	}
	lista -> inicio = NULL; 	//Luego limpia el inicio de la lista
}

/*
	 Función para imprimir una lista
*/
int imprimir_lista(listilla* lista) {
	/* Declaración de inicio */
	nodito* act = lista -> inicio; 	//Inicia la lista
	
	/* Funcion en si */
	if (act == NULL) { 	//Si la lista esta vacia pues...
		printf("	El registro esta vacio\n");
		return -1;
	} while (act != NULL) { 	//Sino
		printf("%s - ", act -> valor); 	//Imprime el valor en la lista
		act = act -> sigt; 	//Y avanza al siguiente
	}
	return 0;
}

/* Funciones Arbol Chaflaneado */

void insertar_chaflaneado_auxiliar(noditoc* raiz, noditoc* nn) {
	if (raiz -> der == NULL && nn -> valor > raiz -> valor){
		raiz -> der = nn;
	} else if (raiz -> izq == NULL && nn -> valor <= raiz -> valor) {
		raiz -> izq == nn;
	} else if (raiz -> der != NULL && nn -> valor > raiz -> valor) {
		insertar_chaflaneado_auxiliar(raiz -> der, nn);
	} else {
		insertar_chaflaneado_auxiliar(raiz -> izq, nn);
	}
}

void insertar_chaflaneado(arbolitoc* arbol, char* termino, listilla* lista){
	noditoc* nn = crear_nodo_c(termino, lista);
	noditoc* actual = arbol -> raiz;
	if (actual == NULL) {
		arbol -> raiz = nn;
	} else {
	insertar_chaflaneado_auxiliar(abol -> raiz, nn);
	while (arbol -> raiz != nn) {
		reacomodar(nn, arbol);
	}
}

void reacomodar(noditoc* nodo, arbolitoc* arbol){
	noditoc* papa = padre(arbol, nn);
	nodito* abuelo = padre(arbol, papa);
	if (abuelo -> der == padre && padre -> izq == nodo){
		rotar_der(nodo, padre);
		rotar_izq(nodo, abuelo);
	} else if (abuelo -> izq == padre && padre -> der == nodo){
		rotar_izq(nodo, padre);
		rotar_der(nodo, abuelo);
	} else if (abuelo -> der == padre && padre -> der == nodo) {
		rotar_izq(padre, abuelo);
		rotar_izq(nodo, padre);
	} else if (abuelo -> izq == padre && padre -> izq == nodo) {
		rotar_der(padre, abuelo);
		rotar_der(nodo, padre);
	} else if (abuelo == NULL && padre -> izq == nodo){
		rotar_der(nodo, padre);
	} else {
		rotar_izq(nodo, padre);
	}
}
		
void rotar_der(nodito* n, nodito* n1){
	n -> izq = n1 -> der;
	n1 -> der = n;
	n = n1;
}

void rotar_izq(nodito* n, nodito* n1){
	n -> der = n1 -> izq;
	n1 -> izq = n;
	n = n1;
}

noditoc* padre(arbolitoc* arbol, noditoc* nodo){
	if (arbol -> raiz == NULL || arbol -> raiz == nodo){
		return NULL;
	} else if (arbol -> izq == nodo || arbol -> der == nodo) {
		return arbol -> raiz;
	} else if (nodo -> valor <= arbol -> valor){
		return padre(arbol -> izq, nodo);
	} else {
		return padre(arbol -> der, nodo);
}


