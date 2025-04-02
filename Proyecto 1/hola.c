 /*
 * =====================================================================================
 *
 *    Asignacion:  Proyecto 1
 *
 *        Version:  1.0
 *  Fecha: 14 de marzo de 2020
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

#define TAMANNO_MAXIMO 	1024*1024		// Longitud máxima de la tabla
#define SI			1
#define NO			0
#define ENVIA		1
#define RECIBE		0

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

/* Creacion del nodo y la lista en structs - Creacion de nodos hash y tabla en si*/
typedef struct nodo{
	char* valor;
	int interes;
	struct tabla_hash* tabla;
	struct nodo* sigt;
}nodito;

typedef struct lista{
	nodito* inicio;
}listilla;

typedef struct nodo_hash
{
	struct nodo_hash* sigt;	// Puntero a siguiente
	char* key;				//Palabra clave o hash
	void* valor;			//valor
	char ocupado;	// ¿Está ocupado?
}nodo_h;

typedef struct tabla_hash
{
	nodo_h** table;
}tabla_h;

nodito* crear_nodo(char* texto){
    nodito* nn = calloc(1, sizeof(nodito));
	nn -> valor = texto;
	return nn;
}

/* Funciones */

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

/*
	 Función para devolver valor hash
*/

unsigned int valor_hash(char* key, unsigned int key_len) {
	unsigned int hash = 1315423911;
	unsigned int i = 0;

	for(i = 0; i < key_len; key++, i++)
	{
		hash ^= ((hash << 5) + (*key) + (hash >> 2)); 	//Se hace un XOR en ciclo
	}

	return hash;
}

/*
	 Función para inicializar el nodo hash
	 Le da los punteros e información necesaria al nodo
*/
void inicializar_nodo_hash(nodo_h* nodo) {
	nodo -> sigt = NULL;
	nodo -> key = NULL;
	nodo -> valor = NULL;
	nodo -> ocupado = NO;
}

/*
	 Función para crear una tabla hash
	 Devuelve una tabla de hash funcional a menos que no se pueda crear, en ese caso retorna un NULL
*/
tabla_h* crear_tabla(void) {
	tabla_h* tablilla = (tabla_h *)calloc(1, sizeof(tabla_h));	// Se asigna el espacio y direccion para la tabla
	if (!tablilla)
	{
		printf("No hay memoria suficiente\n");
		return NULL; 
	}
	
	tablilla -> table = calloc(1,sizeof(nodo_h) * TAMANNO_MAXIMO);	// Asigna el espacio para los nodos de la tabla hash
	if (!tablilla -> table) 	//Si no se logra crear el espacio, se elimina la tabla
	{
		printf("No hay suficiente memoria para la tabla\n");
		free(tablilla);
		tablilla = NULL;
		return NULL;
	}
	
	memset(tablilla -> table, 0, sizeof(nodo_h) * TAMANNO_MAXIMO);	// Se inicializan todos los nodos en 0
	
	return tablilla;		// Devuelve la tabla
}

/*
	 Función para añadir nodo a la tabla de hash
	 Retorna 0 si funcionó o -1 si falló
*/
int annadir_nodo_hash(tabla_h* tablilla, char* key, unsigned int key_len, void* valor) {
	if(!tablilla || !key ) //Se verifica que la tabla no este vacia y que se haya dado alguna llave
	{
		printf("Algo está en NULL\n");
		return -1;
	}

	unsigned int i = valor_hash(key, key_len) % TAMANNO_MAXIMO;		// Se obtiene el subindice de la tabla en base a su llave

	nodo_h* act = tablilla -> table[i]; 	//Apunta a el punto actual
	nodo_h* prev = act; 	//Apunta a el anterior al actual, sin embargo al inicio se empieza en actual
	
	while(act)	// Si hay un nodo hash aqui debemos ir al final
	{
		if ( strncmp(key, act -> key, key_len) == 0 )	// Si el valor clave existe entonces se actualiza
		{
			if(act -> ocupado) 	//Si el punto esta ocupado
			{
				act -> valor = valor; 	//Entonces el valor de actual es el valor recibido
				act -> ocupado = 1;		// Y se indica que actual esta ocupado
				break;
			}
		}
		prev = act;
		act = act -> sigt;
	}
	
	if(!act)	// Si el punto no esta ocupado o ya se pasó por el ciclo anterior
	{
		nodo_h* nn = (nodo_h *)calloc(1, sizeof(nodo_h)); //Se asigna espacio para un nuevo nodo
		if(!nn) //Si no se logra crear
		{
			printf("No hay suficiente memoria\n"); //Entonces es porque no hay:
			return -1;
		}
		inicializar_nodo_hash(nn); 	//Se le dan los punteros al nuevo nodo
		char* nn_key = (char*)calloc(1, key_len+1); //Se le da el valor a la clave
		if(!nn_key) //Si no se logra crear se borra el nodo
		{
			free(nn);
			nn = NULL;
			return -1;
		}
		strncpy(nn_key, key, key_len);
		nn -> key = nn_key; 	//Se le dan los valores al nuevo nodo
		nn -> valor = valor;
		nn -> ocupado = SI;	// Se asigna como ocupado
		
		if(prev == NULL)		// Si el punto no ha sido ocupado
		{
			tablilla -> table[i] = nn; 	//Se añade la tabla aqui
		}
		else		// Si el punto ha sido ocupado y se llega al final
		{
			prev -> sigt = nn; // Se asigna el nuevo nodo en act
		}
	}
	
	return 0;
}

/*
	 Función para obtener los datos de la tabla hash
	 Debe devolver el contenido almacenado a menos que no haya(NULL)
*/
void* obtener_datos_hash(tabla_h* tablilla, char* key, unsigned int key_len) {
	if( !tablilla || !key) //Si no hay tabla o no hay clave, entonces es porque:
	{
		printf("Algo esta en NULL\n");
		return NULL;
	}
	
	int i = valor_hash(key, key_len) % TAMANNO_MAXIMO; //Se obtiene el valor hash
	nodo_h *act = tablilla->table[i];
	
	while(act)
	{
		if(strncmp(act->key, key, key_len) == 0)
		{
			return act->valor;
		}
		act = act->sigt;
	}
	
	return NULL;
}

/*
	 Función para eliminar toda la tabla hash
*/
void eliminar_tabla(tabla_h* tablilla) {
    if (tablilla) 	// Si existe la tabla
	{
        if (tablilla->table) //Y adicionalmente hay tabla en sí 
		{
            int i = 0; 
            for (i = 0; i<TAMANNO_MAXIMO; i++)	// Se recorre todo
			{
                nodo_h* act = tablilla->table[i];
                nodo_h* borr = NULL; 	//Este sera
                while (act)		// Hay contenido de almacenamiento en este momento
				{
                    borr = act->sigt;
                    act->ocupado = 0;	// Marca de ocupación borrada a 0
                    act = borr;
                }
            }
            free(tablilla->table);	// Libera el uso de memoria del puntero de almacenamiento de la tabla
            tablilla->table = NULL;
        }
        free(tablilla);		// Suelta el puntero de la tabla
		tablilla = NULL;
    }
	return ;
}

// Funciones del simulador
void lista_ciudades(listilla* ciudad) {
	char* nombra = "San Andres";
	insertar_al_final(ciudad, nombra); 	//Se llama a la funcion

	char* nombra1 = "Heredia";
	insertar_al_final(ciudad, nombra1); 	//Se llama a la funcion

	char* nombra2 = "New York";
	insertar_al_final(ciudad, nombra2); 	//Se llama a la funcion

	char* nombra3 = "Monte Video";
	insertar_al_final(ciudad, nombra3); 	//Se llama a la funcion

	char* nombra4 = "Buenos Aires";
	insertar_al_final(ciudad, nombra4); 	//Se llama a la funcion

	char* nombra5 = "Montreal";
	insertar_al_final(ciudad, nombra5); 	//Se llama a la funcion

	char* nombra6 = "Quito";
	insertar_al_final(ciudad, nombra6); 	//Se llama a la funcion

	char* nombra7 = "Miami";
	insertar_al_final(ciudad, nombra7); 	//Se llama a la funcion

	char* nombra8 = "Londres";
	insertar_al_final(ciudad, nombra8); 	//Se llama a la funcion

	char* nombra9 = "Paris";
	insertar_al_final(ciudad, nombra9); 	//Se llama a la funcion

	int a = 0;
	int num;
	while (a != 1) {
		printf("Digite el número de ciudades con las que desea jugar: ");
		scanf("%d", &num);
		if (num >= 3 && num <= 10){
			printf("Perfecto!");
			a ++;
			break;
		} else {
			printf("El número de ciudades debe estar entre 3 y 10, no se permiten números fuera de este alcance!\n");
		}
	}
	int max = 10 - num;
	eliminar(ciudad, max);
	nodito* act = ciudad -> inicio;
	while(act != NULL) {
		act -> interes = rand() % 100;
		act = act -> sigt;
	}
}

typedef struct informacion_prod {
	char nombre[32];	//nombre del producto
	int interes;		//recibe o envia?
	int intercambio;	//precio
	int cantidad;		//cantidad
}prod;

typedef struct prod_player {
	char nombre[32];	//nombre del producto
	int cantidad;		//cantidad
}prodP;

void annadir_player(tabla_h* tablilla) {
	prodP* prod = (prodP*) calloc(1, sizeof(prodP));
	prodP* prod1 = (prodP*) calloc(1, sizeof(prodP));
	prodP* prod2 = (prodP*) calloc(1, sizeof(prodP));
	prodP* prod3 = (prodP*) calloc(1, sizeof(prodP));

	sprintf(prod -> nombre, "Papel");
	prod -> cantidad = rand() % 100;	
	annadir_nodo_hash(tablilla, prod -> nombre, strlen(prod -> nombre), prod);

	sprintf(prod1 -> nombre, "Bolsa Te");
	prod1 -> cantidad = rand() % 100;	
	annadir_nodo_hash(tablilla, prod1 -> nombre, strlen(prod1 -> nombre), prod1);

	sprintf(prod2 -> nombre, "Fibra");
	prod2 -> cantidad = rand() % 100;
	annadir_nodo_hash(tablilla, prod2 -> nombre, strlen(prod2 -> nombre), prod2);

	sprintf(prod3 -> nombre, "Dinero");
	prod3 -> cantidad = rand() % 1000;
	annadir_nodo_hash(tablilla, prod3 -> nombre, strlen(prod3 -> nombre),prod3);
}

void annadir_a_tabla(tabla_h* tablilla) {
	prod* produ = (prod*) calloc(1, sizeof(prod));
	prod* produ1 = (prod*) calloc(1, sizeof(prod));
	prod* produ2 = (prod*) calloc(1, sizeof(prod));

	sprintf(produ -> nombre, "Papel");
	produ -> interes = rand() % 2;
	produ -> intercambio = rand() % 100;
	produ -> cantidad = rand() % 100;
	annadir_nodo_hash(tablilla, produ -> nombre, strlen(produ -> nombre), produ);

	sprintf(produ1 -> nombre, "Bolsa Te");
	produ1 -> interes = rand() % 2;
	produ1 -> intercambio = rand() % 100;
	produ1 -> cantidad = rand() % 100;	
	annadir_nodo_hash(tablilla, produ1 -> nombre, strlen(produ1 -> nombre), produ1);

	sprintf(produ2 -> nombre, "Fibra");
	produ2 -> interes = rand() % 2;
	produ2 -> intercambio = rand() % 100;
	produ2 -> cantidad = rand() % 100;
	annadir_nodo_hash(tablilla, produ2 -> nombre, strlen(produ2 -> nombre), produ2);
}

void ver_interes(listilla* lista) {
	nodito* act = lista -> inicio;
	while (act != NULL) {
		if (act -> interes >= 30) {
			if (act -> tabla == NULL) {
				act -> tabla = crear_tabla();
				tabla_h* table = act -> tabla;
				annadir_a_tabla(table);
				act = act -> sigt;
			} else {
				printf(" ");
				act = act -> sigt;
			}
		} else {
			eliminar_tabla(act -> tabla);
			act -> tabla = NULL;
			act = act -> sigt;
		}
	}
}

void crear_tablas_para_ciudades(listilla* lista) {
	nodito* act = lista -> inicio;
	while (act != NULL) {
		act -> tabla = crear_tabla();
		tabla_h* table = act -> tabla;
		annadir_a_tabla(table);
		act = act -> sigt;
	}
}

void promocionar(listilla* lista, int ciudad) {
	int aumento = rand() % 50;
	nodito* act = lista -> inicio;
	int cont = 1;
	while (cont != ciudad) {
		act = act -> sigt;
		cont ++;
	}
	act -> interes += aumento;
}

void printf_info(prod* info) {
	printf("   %s: \n"
    "   Precio: %d\n"
	"   Cantidad: %d\n", info -> nombre, info ->intercambio, info ->cantidad);
	if (info -> interes == ENVIA) {
		printf("   Envia\n");
	} else {
		printf("   Recibe\n");
	}
	printf("_____________________________________________________\n");
}

void printf_info_player(prodP* info) {
	printf("   Nombre: %s", info -> nombre);
	printf("   Cantidad: %d\n", info -> cantidad);
}

void intercambio(tabla_h* player, nodito* act) {
	tabla_h* tablita = act -> tabla;

}

int main() {
	srand(time(NULL));
	printf("Bienvenido al simulador de red de intercambios de ciudades del cañamo!\n");
	printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n\n");
	printf(" Por favor, digite su nombre de usuario: ");
	char* player_name = input_texto();
	printf("\n╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
	printf(" Perfecto! Entonces tu nombre de usuario es %s", player_name);
	printf(" Preciona ENTER para continuar...");
	getchar();
	printf("\e[1;1H\e[2J");
	printf(" Lee las siguientes instrucciones para saber como funciona el simulador:\n");
	printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        "   Instrucciones: \n"
        "   El simulador consiste en un sistema de intercambio de productos basados\n"
        "   o derivados del cañamo, para esto el jugador cuenta con un inventario \n"
        "   de cierta cantidad de productos los cuales usará para enviar o recibir\n"
        "   a otras ciudades que tenga interés en productos del cañamo.\n\n"
		"   Cada ciudad muestra sus productos, el coste, si envia o recibe y el\n"
		"   nombre de la ciudad, adicionalmente, el límite de ciudades que pueden\n"
		"   crearse esta definido en un rango entre 3 y 10, siendo 3 el minimo\n"
		"   de ciudades que pueden haber y 10 el máximo\n\n"
		"   El máximo de turnos es 30, para ganar debes tratar de conseguir una\n"
		"   cantidad de dinero superior a los $10.000, muchos éxitos y diviertete!\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n\n");
	printf("Para continuar preciona Enter...");
	getchar();
	printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        "\n\n   	Cargando... \n\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
	tabla_h* player = crear_tabla();
	listilla* ciudad = calloc(1,sizeof(listilla));
	annadir_player(player);
	lista_ciudades(ciudad);
	crear_tablas_para_ciudades(ciudad);
	int turnos = 1;
    int opcion = 0;
    int exit = 0;
	printf("\e[1;1H\e[2J");
	printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        "\n\n   						 Listo! Precione Enter \n\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
	getchar();
	printf("\e[1;1H\e[2J");
	printf("Se han creado las ciudades, estas son: ");
	imprimir_lista(ciudad);
	printf("\nPrecione Enter para continuar...");
	getchar();
	nodito* act = ciudad -> inicio;
    while (!exit && turnos <= 30) {
	ver_interes(ciudad);
    printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        "   Hola! %s"
		"   Te encuentras en el turno %d\n\n"
        "   Que deseas realizar?\n"
		"   1. Ver inventario\n"
		"   2. Ver informacion de ciudad	\n"
        "   3. Promocionar ciudad\n"
		"   4. Intercambiar productos\n"
        "   5. Salir del juego\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n",player_name, turnos);
        scanf("%d", &opcion); 	//Escanea una opcion
		consumirNuevaLinea(); 	//Consume el \n para solucionar errores
        switch (opcion) {
        case 1: 	//Si la opcion es uno
			printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
			char prod_name[32] = {0};
			char prod_name1[32] = {0};
			char prod_name2[32] = {0};
			char prod_name3[32] = {0};
            printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
				"   Nombre: %s\n", player_name);
			printf("   Productos: \n");
						memset(prod_name, 0, sizeof(prod_name));
						sprintf(prod_name, "Papel");
						prodP* get_prod = obtener_datos_hash(player, prod_name, strlen(prod_name));
						printf_info_player(get_prod);

						memset(prod_name1, 0, sizeof(prod_name1));
						sprintf(prod_name1, "Bolsa Te");
						prodP* get_prod1 = obtener_datos_hash(player, prod_name1, strlen(prod_name1));
						printf_info_player(get_prod1);

						memset(prod_name2, 0, sizeof(prod_name2));
						sprintf(prod_name2, "Fibra");
						prodP* get_prod2 = obtener_datos_hash(player, prod_name2, strlen(prod_name2));
						printf_info_player(get_prod2);

						memset(prod_name3, 0, sizeof(prod_name3));
						sprintf(prod_name3, "Dinero");
						prodP* get_prod3 = obtener_datos_hash(player, prod_name3, strlen(prod_name3));
						printf_info_player(get_prod3);
						printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
						printf("Presione Enter para continuar...");
						getchar();
						printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla

       		break;
    	case 2: 	//Si es la opcion es dos
       	 	printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
				printf("\n╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n\n");
				printf("   La lista de ciudades es: ");
				imprimir_lista(ciudad);
				printf("\n   Para ver la informacion de todas las ciudades entre a esta opcion varias\n");
				printf("   veces, ya que solo puede ver una a la vez.\n");
				printf(" Para continuar presione Enter...");
				getchar();
				nodito* init = ciudad -> inicio;
				printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
				tabla_h* tablilla = act -> tabla;
				char nombre[32] = {0};
				char nombre1[32] = {0};
				char nombre2[32] = {0};
				printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        			"   Ciudad: %s\n"
					"   Interes: %d\n", act -> valor, act -> interes);
				if (act -> tabla == NULL) {
					printf("   Esta ciudad no posee el interes suficiente para intercambiar productos\n"
						"   Para poder realizar intercambios con esta ciudad, promocione primero!\n"
						"╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
					printf("Presione Enter para continuar...");
					getchar();
					printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
					if (act -> sigt == NULL) {
					act = init;
					} else {
					act = act -> sigt;
					}
					break;
				} else {
					printf("   Productos: \n");
					memset(nombre, 0, sizeof(nombre));
					sprintf(nombre, "Papel");
					prod* get_prod = obtener_datos_hash(tablilla, nombre, strlen(nombre));
					printf_info(get_prod);

					memset(nombre1, 0, sizeof(nombre1));
					sprintf(nombre1, "Bolsa Te");
					prod* get_prodi1 = obtener_datos_hash(tablilla, nombre1, strlen(nombre1));
					printf_info(get_prodi1);

					memset(nombre2, 0, sizeof(nombre2));
					sprintf(nombre2, "Fibra");
					prod* get_prodi2 = obtener_datos_hash(tablilla, nombre2, strlen(nombre2));
					printf_info(get_prodi2);
					printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
					printf("Presione Enter para continuar...");
					getchar();
					printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
					if (act -> sigt == NULL) {
						act = init;
					} else {
					act = act -> sigt;
					}
					break;
				}
        case 3:	//Si la opcion es tres
        	printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
			printf("\n╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n\n");
			printf("   La lista de ciudades es: ");
			imprimir_lista(ciudad);
			printf(" Para lo siguiente tome las ciudades por sus posiciones de 1 hasta la ultima\n");
			printf("\n   Escriba el numero de la ciudad a promocionar: ");
			int ciudad_act;
			scanf("%d", &ciudad_act);
			int cont = 1;
			nodito* acto = ciudad -> inicio;
			while (acto != NULL && cont != ciudad_act) {
					act = acto -> sigt;
					cont ++;
				}
			if (acto == NULL) {
				printf("\nEscribe la posicion de la ciudad!\n");
			} else if (cont == ciudad_act){
				promocionar(ciudad, ciudad_act);
				printf("\n═════════════════════ :Ciudad promocionada: ═════════════════════\n\n");
				turnos ++;
				printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
				printf(" Presione Enter para continuar...\n");
				getchar();
				break;
			} else {
				printf("Escribe la posicion de la ciudad!\n");
			}
		case 4:
			printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n");
			printf("   Digite el nombre de la ciudad con la que desea hacer intercambios:\n");
			
			printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
			break;

        case 5: 	//Si la opcion es cuatro
           	exit = 1; 	//Se cierra el programa rompiendo el while
        	printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
    		printf("		Tenga un buen dia!.... Log out\n");
			printf(" Digite Enter para continuar...");
			getchar();
       		break;
       	default: 	//En caso de que opcion no sea 1,2,3 o 4
       		printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla y se regaña
       		printf("		Digite una opcion valida\n");
     		break;
    	}
	}
	return 0;
}
