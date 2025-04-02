#include <stdio.h>

int if_else(){
	/* Este es el comentario al inicio del if */

	if ( 0 ) {	// Este es un comentario de línea
		printf("No pasa nada\n");
		
	} else if ( 0 ) {	// En C no existen los valores true y false
		printf("Tampoco pasa nada\n");
		
	} else {
		printf("¡Aquí toyyy!\n");
	}
}

int ciclo(){
	/* esta sección se refiere al uso de while */
	
	int contador = 0
	
	// muestra la siguiente secuencia: "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, "
	while (contador < 10) {
		printf("%d, ", contador);
		contador++;
	}	
}

int para(){
	/*
	 * Esra sección se refiere al uso de for
	 *
	 * Es importante destacar que python no tiene un for cómo este
	 *
	 * Este for muestra la siguiente secuencia: "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, "
	 */
	 
	 for (int contador=0; contador < 10; contador++) {	// Aquí sucede todo en una línea
	 	printf("%d, ", contador);
	 }
}

/* char 1 byte (-128 a 127)
 * short 2 bytes
 * int 4 bytes
 * long 8 bytes
 * float 4 bytes (IEEE754)
 * double 8 bytes (IEEE754)
 */
 
int variables(){
	int variable;	// se reserva un espacio de 5 Bytes con un valor desconocido (n. r.)
	int variable = 0;	//se reserva un espacio de 4 Bytes con un valor de 0
	int variable = valor_1 + valor_2;	// se reservab 4 bytes y el valor será el
						// resultado de valor_1 + valor_2
}

/* Función main:
 *	Esta función es la primera función en ejecutarse cuando se invoca el programa
 *
 *	se puede escribir de varias formas:
 *
 *	int main(){...}
 *	int main(int argc, char ++argv){...}
 */
 
 int main(){
 
 	printf("Hola mundo!\n");
 	
 	return 0;
 }

int main(int argc, char **argv){
	
	printf("Hola %s!", argv[1]);
	
	return 0;
}

int print(){
	/* Esta sección hace referencia al uso del printf
	 *	printf(<formato>, <valor>, <valor>, ...);
	 */
	 
	 printf("color: %s \t numero: %d \t flotante: %5.2f \n", "Rojo", 1573, 12.5);
	 
	/* %s = arreglos de caracteres
	 * %d números
	 * %f números flotantes
	 * %p valor puntero (direcciones de memoria)
	 * %c caracter
	 */
	 
	/* Secuencias de escape
	 * \t imprime un tab
	 * \n imprime un cambio de línea
	 * \r imprime un retorno de carro
	 * \" imprime una comilla doble
	 * \' imprime una comilla simple
	 */
}

/* "void" es una función que no retorna nada */



