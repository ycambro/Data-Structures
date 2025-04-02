/*
 * Laboratorio 3
 *
 * Autor: Yurgen Cambronero
 * Fecha: 11 de Agosto de 2022
 */

#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void eliminar_c (char* texto, char caracter) { 
	/* Declaracion de variables */
	int i = 0;
	int vacio = ' '; 	// Se le da un valor vacio
	
	/* Funcion en si */
	while (texto[i] != '\0') {
	
		if (texto[i] == caracter) { 	// Si se encuentra el caracter en el texto
			texto[i] = vacio; 	// Se convierte en vacio ese caracter
			i ++; 	// Se aumenta 1 al i, para seguir con la otra pos.
		}
		
		i++; 	// Sino, solo le se aumenta 1 al i.
	}
	
	printf("%s \n",texto);
}

void invertir_texto (char* texto) {
	/* Declaracion de variables */
	int len = strlen(texto); 	// Se saca el tamaño de el string
	int i = len-1;
	int i_inverso = 0;
	char* texto_inv = calloc(len+1, sizeof(char)); // Se crea el espacio para el texto inv.
	strcpy(texto_inv, texto);
	
	/* Funcion en si */
	while (i != 0) { 	// Mientras el i no sea cero
		texto_inv[i_inverso] = texto[i]; 	// Se pone la letra en el texto inv.
		i --; 	// A i se le resta 1 puesto que vamos de atras para adelante
		i_inverso ++; 	// A i_inverso se le suma 1
	}
	
	printf("%s\n",texto_inv);
}
	
	


int main(int argc, char **argv){
	
	/* De pila a Heap */
	char buffer[30] = "Hola soy una persona muy feliz";
	int tamaño_char = strlen(buffer);
	
	char* texto = calloc(tamaño_char+1, sizeof(char));
 	strcpy(texto, buffer);
 	
 	char* texto2 = calloc(tamaño_char+1, sizeof(char));
 	strcpy(texto2, buffer);
	
	/* Llamado de funciones */
	eliminar_c(texto,'a');
	
	invertir_texto(texto2);
	
	
	return 0;
}
