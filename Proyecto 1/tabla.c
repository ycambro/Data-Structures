/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  hash table
 *
 *        Version:  1.0
 * Creado: 14 de marzo de 2020 17:20:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxy
 *        Company:  xxx
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANNO_MAXIMO 	1024*1024		// Longitud máxima de la tabla
#define SI			1
#define NO			0

typedef struct nodo_hash
{
	struct nodo_hash *sigt;	// Puntero a siguiente
	char *key;				//Palabra clave o hash
	void *valor;			//valor
	char ocupado;	// ¿Está ocupado?
}nodo_h;

typedef struct tabla_hash
{
	nodo_h **table;
}tabla_h;

/*
	 Función para devolver valor hash
*/
unsigned int valor_hash(char* key, unsigned int key_len)
{
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
void inicializar_nodo_hash(nodo_h *node)
{
	node->sigt = NULL;
	node->key = NULL;
	node->valor = NULL;
	node->ocupado = NO;
}

/*
	 Función para crear una tabla hash
	 Devuelve una tabla de hash funcional a menos que no se pueda crear, en ese caso retorna un NULL
*/
tabla_h *crear_tabla(void)
{
	tabla_h *tablilla = (tabla_h *)calloc(1, sizeof(tabla_h));	// Se asigna el espacio y direccion para la tabla
	if (!tablilla)
	{
		printf("No hay memoria suficiente\n");
		return NULL; 
	}
	
	tablilla->table = calloc(1,sizeof(nodo_h) * TAMANNO_MAXIMO);	// Asigna el espacio para los nodos de la tabla hash
	if (!tablilla->table) 	//Si no se logra crear el espacio, se elimina la tabla
	{
		printf("No hay suficiente memoria para la tabla\n");
		free(tablilla);
		tablilla = NULL;
		return NULL;
	}
	
	memset(tablilla->table, 0, sizeof(nodo_h) * TAMANNO_MAXIMO);	// Se inicializan todos los nodos en 0
	
	return tablilla;		// Devuelve la tabla
}

/*
	 Función para añadir nodo a la tabla de hash
	 Retorna 0 si funcionó o -1 si falló
*/
int annadir_nodo_hash(tabla_h *tablilla, char *key, unsigned int key_len, void *valor)
{
	if(!tablilla || !key ) //Se verifica que la tabla no este vacia y que se haya dado alguna llave
	{
		printf("Algo está en NULL\n");
		return -1;
	}

	unsigned int i = valor_hash(key, key_len) % TAMANNO_MAXIMO;		// Se obtiene el subindice de la tabla en base a su llave

	nodo_h *act = tablilla->table[i]; 	//Apunta a el punto actual
	nodo_h *prev = act; 	//Apunta a el anterior al actual, sin embargo al inicio se empieza en actual
	
	while(act)	// Si hay un nodo hash aqui debemos ir al final
	{
		if ( strncmp(key, act->key, key_len) == 0 )	// Si el valor clave existe entonces se actualiza
		{
			if(act->ocupado) 	//Si el punto esta ocupado
			{
				act->valor = valor; 	//Entonces el valor de actual es el valor recibido
				act->ocupado = 1;		// Y se indica que actual esta ocupado
				break;
			}
		}
		prev = act;
		act = act->sigt;
	}
	
	if(!act)	// Si el punto no esta ocupado o ya se pasó por el ciclo anterior
	{
		nodo_h *nn = (nodo_h *)calloc(1, sizeof(nodo_h)); //Se asigna espacio para un nuevo nodo
		if(!nn) //Si no se logra crear
		{
			printf("No hay suficiente memoria\n"); //Entonces es porque no hay:
			return -1;
		}
		inicializar_nodo_hash(nn); 	//Se le dan los punteros al nuevo nodo
		char *nn_key = (char *)calloc(1, key_len+1); //Se le da el valor a la clave
		if(!nn_key) //Si no se logra crear se borra el nodo
		{
			free(nn);
			nn = NULL;
			return -1;
		}
		strncpy(nn_key, key, key_len);
		nn->key = nn_key; 	//Se le dan los valores al nuevo nodo
		nn->valor = valor;
		nn->ocupado = SI;	// Se asigna como ocupado
		
		if(prev == NULL)		// Si el punto no ha sido ocupado
		{
			tablilla->table[i] = nn; 	//Se añade la tabla aqui
		}
		else		// Si el punto ha sido ocupado y se llega al final
		{
			prev->sigt = nn; // Se asigna el nuevo nodo en act
		}
	}
	
	return 0;
}

/*
	 Función para obtener los datos de la tabla hash
	 Debe devolver el contenido almacenado a menos que no haya(NULL)
*/
void *get_value_from_hstable(tabla_h *tablilla, char *key, unsigned int key_len)
{
	if( !tablilla || !key) //Si no hay tabla o no hay clave, entonces es porque:
	{
		printf("Algo esta en NULL\n");
		return NULL;
	}
	
	int i = valor_hash(key,key_len) % TAMANNO_MAXIMO; //Se obtiene el valor hash
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
void eliminar_tabla(tabla_h *tablilla)
{
    if (tablilla) 	// Si existe la tabla
	{
        if (tablilla->table) //Y adicionalmente hay tabla en sí 
		{
            int i = 0; 
            for (i = 0; i<TAMANNO_MAXIMO; i++)	// Se recorre todo
			{
                nodo_h *act = tablilla->table[i];
                nodo_h *borr = NULL; 	//Este sera
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

typedef struct commodity
{
	char name[32];	//nombre del producto
	float price;	//precio
}Com;

void printf_com_info(Com *com)
{
	printf("name=%s\tprice=%.1f\n", com->name, com->price);
	return ;
}

int main(int argc, char **argv)
{
	tabla_h *Hs_table = crear_tabla();
	if(!Hs_table)
	{
		printf("No se pudo crear la tabla hash\n");
		return -1;
	}
	char name[32] = {0};
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		Com *tmp_com = (Com *)calloc(1,sizeof(Com));
		// No juzgues primero la asignación de memoria
		sprintf(tmp_com->name, "com%d", i);
		tmp_com->price = rand() % 1000;
		
		annadir_nodo_hash(Hs_table, tmp_com->name, strlen(tmp_com->name), tmp_com);
	}

	for(i = 0; i < 100; i++)
	{
		memset(name, 0, sizeof(name));
		sprintf(name, "com%d", i);
		Com *get_com = get_value_from_hstable(Hs_table, name, strlen(name));
		if(get_com)
		{
			printf_com_info(get_com);
		}
	}

	eliminar_tabla(Hs_table);

	return 0;
}

