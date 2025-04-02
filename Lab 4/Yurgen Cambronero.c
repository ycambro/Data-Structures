/*
 * Laboratorio 4, 5, 6
 *
 * Autor: Yurgen Cambronero
 * Fecha: 1 de Setiembre del 2022
 */

#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void consumirNuevaLinea(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != EOF && c != '\n');
}

char* input_texto(){
	/* Declaracion de variables */
	char texto[80]; 	//Genera espacio para texto
	fgets(texto, sizeof(texto), stdin); 	//Recibe el texto
	
	/* Traspaso al Heap */
	int tamaño_char = strlen(texto);
	char* string = calloc(tamaño_char, sizeof(char));
	strcpy(string, texto); 		// Convierte el texto de pila a heap.
	return string;		//Devuelve el string ya convertido o pasado.
}

/* Creacion del nodo y la lista en structs*/
typedef struct nodo{
	char* valor;
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

/* Funciones */
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

int imprimir_lista(listilla* lista) {
	/* Declaración de inicio */
	nodito* act = lista -> inicio; 	//Inicia la lista
	
	/* Funcion en si */
	if (act == NULL) { 	//Si la lista esta vacia pues...
		printf("	El registro esta vacio\n");
		return -1;
	} while (act != NULL) { 	//Sino
		printf("%s\n", act -> valor); 	//Imprime el valor en la lista
		act = act -> sigt; 	//Y avanza al siguiente
	}
	return 0;
}
	

int main() {
    	printf("		Bienvenido al sistema de registros de guerras!\n");
    	listilla* lista = calloc(1,sizeof(listilla));
    	int opcion = 0;
    	int exit = 0;
    	while (!exit) {
        printf(		"╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        	"   Seleccione una opcion\n"
        	"   1.Insertar a el registro de guerras algun pais en guerra\n"
        	"   2.Imprimir el registro de guerra\n"
        	"   3.Borrar el registro de guerra\n"
        	"   4.Cerrar el registro\n"
        	"╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
        	scanf("%d", &opcion); 	//Escanea una opcion
			consumirNuevaLinea(); 	//Consume el \n para solucionar errores
        	switch (opcion) {
        	case 1: 	//Si la opcion es uno
            		printf("	    Digite el pais que se encuentra en guerra actualmente\n");
            		char* pais = input_texto(); 	//Se recibe un texto
            		printf("%s\n", pais); 	//Se imprime el texto
            		insertar_al_final(lista, pais); 	//Se llama a la funcion
					printf("\e[1;1H\e[2J");
            		printf("════════════════════ :Se añadio un pais a el registro: ════════════════════\n\n\n");
            		break;
        	 case 2: 	//Si es la opcion es dos
        	 		printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
            		imprimir_lista(lista); 	//Se llama a la funcion imprimir lista
            		break;
        	 case 3:	//Si la opcion es tres
            		eliminar_lista(lista); 	//Se llama a la funcion
            		printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
            		printf("═════════════════════ :Registro eliminado: ═════════════════════\n\n\n");
            		break;
        	 case 4: 	//Si la opcion es cuatro
            		exit = 1; 	//Se cierra el programa rompiendo el while
            		printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
            		printf("		Tenga un buen dia!.... Log out\n");
            		break;
        
        	default: 	//En caso de que opcion no sea 1,2,3 o 4
        		printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla y se regaña
            		printf("		Digite una opcion valida\n");
            		break;
            	}
		}
    	return 0;
}
