/*
 * Laboratorio 4, 5, 6
 *
 * Autor: Yurgen Cambronero
 * Fecha: 1 de Setiembre del 2022
 */

#include <stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct nodo{
	char* valor;
	struct nodo* sigt;
}nodito;

typedef struct lista{
	nodito* inicio;
}listilla;

void insertar_al_final(nodito*inicio, char* valor_a_agregar){
    nodito* actual = inicio;
    if (actual->valor==NULL){
        actual->valor=valor_a_agregar;
        return;
    }
    while (actual->sigt!=NULL)
    {
        actual=actual->sigt;
    }
    actual -> sigt= calloc(1,sizeof(nodito));
    actual = actual->sigt;
    actual->valor=valor_a_agregar;
}

char* input_texto(){
	/* Declaracion de variables */
	char texto[80];
	fgets(texto, sizeof(texto), stdin);
	
	/* Traspaso al Heap */
	int tamaño_char = strlen(texto);
	char* string = calloc(tamaño_char + 1, sizeof(char));
	strcpy(string, texto);
	return string;
}

int main() {
	char* pais = input_texto();
	printf("%s", pais);
	nodito*inicio = calloc(1,sizeof(nodito));
	insertar_al_final(inicio, pais);
}
