 /*
 * =====================================================================================
 *
 *    Asignacion:  Proyecto 1
 *
 *        Version:  1.0.15
 *  Fecha: 04 de octubre de 2020
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

/*
	 Almacenador de productos de las ciudades
*/
typedef struct informacion_prod {
	char nombre[32];	//nombre del producto
	int interes;		//recibe o envia?
	int intercambio;	//precio
	int cantidad;		//cantidad
}prod;

/*
	 Almacenador de productos del jugador
*/
typedef struct prod_player {
	char nombre[32];	//nombre del producto
	int cantidad;		//cantidad
}prodP;

/*
	 Función para añadir los productos y el dinero al jugador
*/
void annadir_player(tabla_h* tablilla) {
	// Se crean los structs para cada producto (incluyendo el dinero)
	prodP* prod = (prodP*) calloc(1, sizeof(prodP));
	prodP* prod1 = (prodP*) calloc(1, sizeof(prodP)); 	
	prodP* prod2 = (prodP*) calloc(1, sizeof(prodP)); 	
	prodP* prod3 = (prodP*) calloc(1, sizeof(prodP));	

	sprintf(prod -> nombre, "Papel");	// Se guarda el nombre del producto en la parte respectiva
	prod -> cantidad = rand() % 100;	// Se guarda la cantidad de el producto en un intervalo de 0 a 100
	annadir_nodo_hash(tablilla, prod -> nombre, strlen(prod -> nombre), prod); 	//Se añade el struct a la tabla hash como un nodo nuevo

	sprintf(prod1 -> nombre, "Bolsa Te");	// Se guarda el nombre del producto en la parte respectiva
	prod1 -> cantidad = rand() % 100;		// Se guarda la cantidad de el producto en un intervalo de 0 a 100
	annadir_nodo_hash(tablilla, prod1 -> nombre, strlen(prod1 -> nombre), prod1);	//Se añade el struct a la tabla hash como un nodo nuevo

	sprintf(prod2 -> nombre, "Fibra");	// Se guarda el nombre del producto en la parte respectiva
	prod2 -> cantidad = rand() % 100;	// Se guarda la cantidad de el producto en un intervalo de 0 a 100
	annadir_nodo_hash(tablilla, prod2 -> nombre, strlen(prod2 -> nombre), prod2);	//Se añade el struct a la tabla hash como un nodo nuevo

	sprintf(prod3 -> nombre, "Dinero");	// Se guarda el nombre del producto en la parte respectiva
	prod3 -> cantidad = rand() % 2000;	// Se guarda la cantidad de el producto en un intervalo de 0 a 100
	annadir_nodo_hash(tablilla, prod3 -> nombre, strlen(prod3 -> nombre),prod3);	//Se añade el struct a la tabla hash como un nodo nuevo
}

/*
	 Función para añadir los productos a las tablas de las ciudades
*/
void annadir_a_tabla(tabla_h* tablilla) {
	// Se crean los structs que almacenaran los datos de cada producto
	prod* produ = (prod*) calloc(1, sizeof(prod));
	prod* produ1 = (prod*) calloc(1, sizeof(prod));
	prod* produ2 = (prod*) calloc(1, sizeof(prod));

	sprintf(produ -> nombre, "Papel");	// Se les asigna el valor de el nombre
	produ -> interes = rand() % 2;	//Se les asigna un interes, ya sea enviar o recibir
	produ -> intercambio = rand() % 100;	//Se les da un costo a los productos
	produ -> cantidad = rand() % 100;		//Se le asigna una cantidad
	annadir_nodo_hash(tablilla, produ -> nombre, strlen(produ -> nombre), produ); 	//Se añade el nodo a la tabla de la ciudad

	sprintf(produ1 -> nombre, "Bolsa Te");	// Se les asigna el valor de el nombre
	produ1 -> interes = rand() % 2;	//Se les asigna un interes, ya sea enviar o recibir
	produ1 -> intercambio = rand() % 100;	//Se les da un costo a los productos
	produ1 -> cantidad = rand() % 100;		//Se le asigna una cantidad
	annadir_nodo_hash(tablilla, produ1 -> nombre, strlen(produ1 -> nombre), produ1);	//Se añade el nodo a la tabla de la ciudad

	sprintf(produ2 -> nombre, "Fibra");	// Se les asigna el valor de el nombre
	produ2 -> interes = rand() % 2;	//Se les asigna un interes, ya sea enviar o recibir
	produ2 -> intercambio = rand() % 100;	//Se les da un costo a los productos
	produ2 -> cantidad = rand() % 100;		//Se le asigna una cantidad
	annadir_nodo_hash(tablilla, produ2 -> nombre, strlen(produ2 -> nombre), produ2);	//Se añade el nodo a la tabla de la ciudad
}

/*
	 Función para revisar el interes de las ciudades
*/
void ver_interes(listilla* lista) {
	nodito* act = lista -> inicio; 	//Se llama a la lista
	while (act != NULL) { 	//Mientras act no sea nulo
		if (act -> interes >= 30) { 	//Se verifica que el interes sea mayor a 30, si es asi y no hay tabla se crea una, sino se continua y ya
			if (act -> tabla == NULL) {
				act -> tabla = crear_tabla();
				tabla_h* table = act -> tabla;
				annadir_a_tabla(table);
				act = act -> sigt;
			} else {
				printf(" ");
				act = act -> sigt;
			}
		} else { 	//Si el interes es menor a 30 se elimina la tabla
			eliminar_tabla(act -> tabla);
			act -> tabla = NULL;
			act = act -> sigt;
		}
	}
}

/*
	 Función para ir cambiando el interes de la ciudad
*/
void change_interes(listilla* lista) {
	nodito* act = lista -> inicio; 	//Se empiezza a recorrer la lista
	while (act != NULL) {	//Se recorre la lista y se modifican los valores de interes de cada ciudad
		act -> interes += rand() % 30;
		act -> interes -= rand() % 30;
		act = act -> sigt;
	}
}

/*
	 Función para crear las tablas para las ciudades
*/
void crear_tablas_para_ciudades(listilla* lista) {
	nodito* act = lista -> inicio; 	//Se inicia la lista y se recorre, a cada ciudad se le crea la tabla y se le añaden los productos a la tabla
	while (act != NULL) {
		act -> tabla = crear_tabla();
		tabla_h* table = act -> tabla;
		annadir_a_tabla(table);
		act = act -> sigt;
	}
}

/*
	 Función para promocionar el cañamo en una ciudad
*/
void promocionar(listilla* lista, int ciudad) {
	/* Se asigna una variable con un numero aleatorio
	 * Se recorre la lista hasta encontrar la ciudad a promocionar
	 * Una vez encontrada la ciudad se le aumenta el interes
	*/
	int aumento = rand() % 50;
	nodito* act = lista -> inicio;
	int cont = 1;
	while (cont != ciudad) {
		act = act -> sigt;
		cont ++;
	}
	act -> interes += aumento;
}

/*
	 Función para imprimir la informacion del producto de una ciudad
*/
void printf_info(prod* info) {
	printf("   Nombre: %s\n"
    "   Precio: %d\n"
	"   Cantidad: %d\n", info -> nombre, info ->intercambio, info ->cantidad);
	if (info -> interes == ENVIA) {
		printf("   Envia\n");
	} else {
		printf("   Recibe\n");
	}
	printf("_____________________________________________________\n");
}

/*
	 Función para imprimir la informacion del producto de el jugador
*/
void printf_info_player(prodP* info) {
	printf("   Nombre: %s", info -> nombre);
	printf("   Cantidad: %d\n", info -> cantidad);
}

/*
	 Función para recibir de una ciudad que envia
*/
void enviar(prod* act, prodP* actu, prodP* dinero) {
	if (dinero -> cantidad >= act -> intercambio && act -> cantidad >= 1) { //Se verifica si el jugador cuenta con suficiente dinero y si la ciudad cuenta con suficientes recursos
		dinero -> cantidad -= act -> intercambio; //Si es asi, se hace el cobro
		act -> cantidad --; 	//Se le quita uno a la ciudad
		actu -> cantidad ++; 	//Y se le añade al jugador
		printf("   Se ha realizado el intercambio exitosamente!\n");
	} else if (act -> cantidad < 1) { 	//Si no hay suficientes recursos se imprique:
		printf("   La ciudad no tiene suficiente %s\n", act -> nombre);
	} else {
		printf("   Cantidad de dinero insuficiente!\n");
	}
}

/*
	 Función para enviar producto a ciudad que recibe
*/
void recibir(prod* act, prodP* actu, prodP* dinero) {
	if (actu -> cantidad >= 1) { 	//Se verifica que el jugador posea suficiente recurso
		dinero -> cantidad += act -> intercambio; 	//Se le suma el dinero al jugador (Puesto que le estan comprando)
		act -> cantidad ++; 	//La ciudad obtiene el producto
		actu -> cantidad --;	//Y el jugador lo pierde por hacer el intercambio
		printf("   Se ha realizado el intercambio exitosamente!\n");
	} else {
		printf("   No tienes suficientes recursos para intercambiar!\n");
	}
}

/*
	 Función para realizar el intercambio de productos
*/
void intercambio(prod* produ, int producto, tabla_h* player) {
	/* Asignacion de variables */
	char produ_name[32] = {0};
	char produ_name1[32] = {0};
	char produ_name2[32] = {0};
	char produ_name3[32] = {0};

	if (producto == 1) {
		memset(produ_name, 0, sizeof(produ_name)); //Se configura el espacio de memoria
		sprintf(produ_name, "Papel"); 	//Se le pone el nombre a el espacio
		prodP* get_produ = obtener_datos_hash(player, produ_name, strlen(produ_name));	//Se obtienen los datos del hash en base a la llave, el largo de la llave y la tabla

		memset(produ_name3, 0, sizeof(produ_name3));
		sprintf(produ_name3, "Dinero");
		prodP* get_produ3 = obtener_datos_hash(player, produ_name3, strlen(produ_name3));
		if (produ -> interes == ENVIA) { 	//Si el interes es enviar
			enviar(produ, get_produ, get_produ3); 	//Se ejecuta la funcion de envia
		} else {
			recibir(produ, get_produ, get_produ3); 	//Sino, se ejecuta la funcion de recibe
		}
	// Lo mismo pasa con los otros productos
	} else if (producto == 2) {
		memset(produ_name1, 0, sizeof(produ_name1));
		sprintf(produ_name1, "Bolsa Te");
		prodP* get_produ1 = obtener_datos_hash(player, produ_name1, strlen(produ_name1));

		memset(produ_name3, 0, sizeof(produ_name3));
		sprintf(produ_name3, "Dinero");
		prodP* get_produ3 = obtener_datos_hash(player, produ_name3, strlen(produ_name3));
		if (produ -> interes == ENVIA) {
			enviar(produ, get_produ1, get_produ3);
		} else {
			recibir(produ, get_produ1, get_produ3);
		}

	} else if (producto == 3) {
		memset(produ_name2, 0, sizeof(produ_name2));
		sprintf(produ_name2, "Fibra");
		prodP* get_produ2 = obtener_datos_hash(player, produ_name2, strlen(produ_name2));

		memset(produ_name3, 0, sizeof(produ_name3));
		sprintf(produ_name3, "Dinero");
		prodP* get_produ3 = obtener_datos_hash(player, produ_name3, strlen(produ_name3));
		if (produ -> interes == ENVIA) {
			enviar(produ, get_produ2, get_produ3);
		} else {
			recibir(produ, get_produ2, get_produ3);
		}
	
	} else {
		printf(" ");
	}
}

/*
	 Función principal!
*/
int main() {
	srand(time(NULL));
	printf("Bienvenido al simulador de red de intercambios de ciudades del cañamo!\n");
	printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n\n");
	printf(" Por favor, digite su nombre de usuario: ");
	char* player_name = input_texto(); 	// Se obtiene el nombre del jugador
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
		"   cantidad de dinero superior a los $10.000, muchos éxitos y diviertete!\n\n"
		"   Para poder ver la informacion de la ciudad y realizar intercambios\n"
		"   debe entrar a la opcion varias veces hasta llegar a la ciudad que desea.\n\n"
		"   Si realiza un intercambio y este no sale exitoso por falta de dinero o de\n"
		"   productos perderá el turno, asi que sea cuidadoso (hardcore).\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n\n");
	printf("Para continuar preciona Enter...");
	getchar();
	printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        "\n\n   	Cargando... \n\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
	tabla_h* player = crear_tabla(); 	//Se crea la tabla del jugador
	listilla* ciudad = calloc(1,sizeof(listilla)); 	// Se crea la lista para las ciudades
	annadir_player(player); 	//Se añaden los datos a la tabla del jugador
	lista_ciudades(ciudad); 	//Se crea la lista de ciudades
	crear_tablas_para_ciudades(ciudad); 	//Se crean las tablas para las ciudades
	int turnos = 1;	//Contador de turnos
    int opcion = 0;
    int exit = 0; 	// Por si se quiere salir
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
		"   Te encuentras en el turno %d\n"
		"   La lista de ciudades es: \n   ",player_name, turnos);
		imprimir_lista(ciudad);
    printf("\n\n   Que deseas realizar?\n"
		"   1. Ver inventario\n"
		"   2. Ver informacion de ciudad y intercambiar productos (actualmente: %s)	\n"
        "   3. Promocionar ciudad\n"
        "   4. Salir del juego\n"
        "╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n", act -> valor);
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
			printf("         ═════════════════════ :Productos: ═════════════════════\n");
						memset(prod_name, 0, sizeof(prod_name)); 	//Se configura el espacio de memoria
						sprintf(prod_name, "Papel"); 	//Se le asigna el nombre al espacio
						prodP* get_prod = obtener_datos_hash(player, prod_name, strlen(prod_name)); //Se inicializa el struct para poder imprimir los datos
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
						printf("\n$");
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
				printf("   veces, ya que solo puede ver una a la vez.\n\n");
				printf("   Para continuar presione Enter...");
				getchar();
				nodito* init = ciudad -> inicio; 	// 
				printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
				tabla_h* tablilla = act -> tabla;
				char nombre[32] = {0};
				char nombre1[32] = {0};
				char nombre2[32] = {0};
				printf("╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n"
        			"   Ciudad: %s\n"
					"   Interes: %d\n", act -> valor, act -> interes);
				if (act -> tabla == NULL) { //Si no posee tabla es porque el interes es bajo por lo que se imprime
					printf("   Esta ciudad no posee el interes suficiente para intercambiar productos\n"
						"   Para poder realizar intercambios con esta ciudad, promocione primero!\n"
						"╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
					printf("Presione Enter para continuar...");
					getchar();
					printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
					if (act -> sigt == NULL) {
						act = init; 	// Si la posicion siguiente es vacia se vuelve al inicio
					} else {
						act = act -> sigt; //Sino solo se apunta a la siguiente
					}
					break;
				} else { 	//Si posee tabla entonces se hace lo mismo que en el case 1, solo que con los valores de los productos de la ciudad
					printf("         ═════════════════════ :Productos: ═════════════════════\n");
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
					printf("   Desea realizar un intercambio con esta ciudad? \n"
						"   Si es asi digite: 1, en caso contrario digite cualquier número\n");
					int continuar;
					scanf("%d",&continuar);
					if (continuar == 1) { 	//Si se desea realizar el intercambio
						printf("\n╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n");
						printf("   Para lo siguiente tome que:\n   El producto 1 es Papel\n"
							"   El producto 2 es Bolsa Te\n"
							"   El producto 3 es Fibra\n"
							"   Si no se selecciona ninguno de los productos se volvera al menu inicial\n\n");
						printf("   Digite el numero del producto a intercambiar: ");
						int it;
						scanf("%d", &it);
						if (it == 1) { 	// Si el producto a ver es 1
							intercambio(get_prod, it, player); //Se trata de realizar el intercambio
							turnos ++; 	//Independientemente de si se logra el intercambio o no, se suma 1 a los turnos
							change_interes(ciudad); 	//Se revuelven los intereses
							printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
							break; 	//Se vuelve al inicio, esto anterior pasa con los otros productos
						} else if (it == 2) {
							intercambio(get_prodi1, it, player);
							turnos ++;
							change_interes(ciudad);
							printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
							break;
						} else if (it == 3) {
							intercambio(get_prodi2, it, player);
							turnos ++;
							change_interes(ciudad);
							printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
							break;
						} else { 	//Si no se digita una opcion valida pues... aja
							printf("   Digite una opcion valida :u");
							break;
						}
					} else { 	//Si no se desea hacer un intercambio, se limpia la pantalla y se apunta a la siguiente ciudad
						printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
						if (act -> sigt == NULL) {
							act = init;
							break;
						} else {
							act = act -> sigt;
							break;
						}
					}
				}
        case 3:	//Si la opcion es tres
        	printf("\e[1;1H\e[2J"); 	//Se limpia la pantalla
			printf("\n╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯☆●ʚ♡ɞ●☆╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n\n");
			printf("   La lista de ciudades es: ");
			imprimir_lista(ciudad);
			printf("   Para lo siguiente tome las ciudades por sus posiciones de 1 hasta la ultima\n");
			printf("\n   Escriba el numero de la ciudad a promocionar: ");
			int ciudad_act;
			scanf("%d", &ciudad_act);
			int cont = 1;
			nodito* acto = ciudad -> inicio; 	//Se apunta al inicio de la lista
			while (acto != NULL && cont != ciudad_act) { 	//Se recorre la lista hasta encontrar la ciudad seleccionada
					act = acto -> sigt;
					cont ++;
				}
			if (acto == NULL) { 	//Si el numero era mayor a la cantidad de ciudades se imprime:
				printf("\nEscribe la posicion de la ciudad!\n");
			} else if (cont == ciudad_act){ 	//Si se encuentra la ciudad, entonces
				promocionar(ciudad, ciudad_act); //Se llama a la funcion para promocionar
				printf("\n═════════════════════ :Ciudad promocionada: ═════════════════════\n\n");
				turnos ++;	//Se suma 1 a los turnos
				printf("╰━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮☆●ʚ♡ɞ●☆╭━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╯\n");
				break;
			} else { 	//Si no se escribe bien la posicion de la ciudad pues...
				printf("Escribe la posicion de la ciudad!\n");
			}
		case 4:
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
	/* Se saca el struct que almacena el dinero del jugador */
	char proda_name3[32] = {0}; 
	memset(proda_name3, 0, sizeof(proda_name3));
	sprintf(proda_name3, "Dinero");
	prodP* get_proda3 = obtener_datos_hash(player, proda_name3, strlen(proda_name3));

	/* Se verifica si se cumplio la condicion de gane o no, y se imprime si gano o no */
	if (get_proda3 -> cantidad >= 10000) {
		printf("Ganaste! Felicidades, has llegado hasta el final, obtuviste %d y has conseguido ganar!!!\n", get_proda3 -> cantidad);
		printf("Presiona Enter para salir...");
		getchar();
	} else {
		printf("Has perdido, lo lamento...\n");
		printf("Presiona Enter para salir...");
		getchar();
	}
	return 0;
}
