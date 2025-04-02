/*
 * Laboratorio 2
 *
 * Autor: Yurgen Cambronero
 * Fecha: 08 de Agosto de 2022
 */
#include <stdio.h> // se agrega para poder usar el printf

void par_impar (int num) {
	if (num % 2 == 0) {	// Si al efectuar la operación mod 2 de el numero dado da 0
		printf("%d es par \n", num);	// Se imprime que es par
	} else {
		printf("%d es impar \n", num);	// En caso contrario significa que es impar
	}
}

void fibo (int n) {
	/* Declaración de variables */
	int contador = 1;
	int n2 = 0;
	int n1 = 1;
	int fibonacci = 0;
	
	/* Función en sí */
	while (n != contador) { 	// Se crea un ciclo hasta que n y contador sean iguales
		if (contador == 1) { 	// Si el contador es 1, entonces es 1
			n2 = 1; 	// Se le da de valor a n2 siendo la posicion n-2
			contador ++;	// Se le suma al contador 1 para continuar
			printf("%d ", 1);	// Se imprime el número
		} else if (contador == 2) { 	// Lo mismo que en el if
			n1 = 1; 	// En la posicion n-1 se le da el valor 1
			contador ++;
			printf("%d ", 1);
		} else {
			fibonacci = n2 + n1; 	// Se suman los números en posicion n-2 y n-1
			n2 = n1; 	// Aquí en la posición n-2 se le da el valor de n-1
			n1 = fibonacci; 	// Y n-1 se convierte en fibonacci
			contador ++; 	// Al contador se le suma 1
			printf("%d ", fibonacci); 	// Se imprime el número
		}
	}
	
	fibonacci = n2 + n1; 	// Lo mismo con el else
	printf("%d\n", fibonacci);
}

void factorial (int n) {
	/* Declaración de variables */
	int contador = 1;
	int factorial_actual = 1;
	
	/* Función en sí */
	while (n >= contador) { 	// Se crea un ciclo hasta que n y contador sean iguales
			factorial_actual *= contador; // Se multiplica el fact. act. por cont.
			contador ++; // Se le suma uno al contador
	}
	
	printf("El factorial de %d es %d\n", n, factorial_actual); // Se imprime el resultado
}

int for_largo_de_n (int n) {
	/* Declaración de variables */
	int largo = 0;
	int n_inicial = n;
	
	/* Función en sí */
	for (; n > 0; largo ++) { 	// Cuando n sea menor a 0 se detiene el ciclo
		n /= 10; 	// n se va dividiendo entre 10
	}
	return largo;

}

int while_largo_de_n (int n) {
	/* Declaración de variables */
	int largo = 0;
	int n_inicial = n;
	
	/* Función en sí */
	while (n > 0) { 	// Cuando n sea menor a 0 se detiene el ciclo
		n /= 10; 	// n se va dividiendo entre 10
		largo ++;	// Y se le suma 1 a la variable largo
	}
	return largo;

}

void for_sumatoria (int n) {
	/* Declaración de variables */
	int contador = 0;
	int suma_actual = 0;
	
	/* Función en sí */
	for (; n >= contador; contador ++) { 	// Ciclo hasta que n y contador sean iguales
			suma_actual += contador; // Se suma la suma act. con contador
	}
	
	printf("La sumatoria de 0 a %d es %d\n", n, suma_actual); // Se imprime el resultado
}

void while_sumatoria (int n) {
	/* Declaración de variables */
	int contador = 0;
	int suma_actual = 0;
	
	/* Función en sí */
	while (n >= contador) { 	// Ciclo hasta que n y contador sean iguales
			suma_actual += contador; 	// Se suma la suma act. con contador
			contador ++; 	// Se le suma 1 al contador
	}
	
	printf("La sumatoria de 0 a %d es %d\n", n, suma_actual); // Se imprime el resultado
}

int invertir_numero (int n) {
	/* Declaración de variables */
	int n_original = n;
	int inverso = 0;
	int n_actual = 0;
	int largo = for_largo_de_n(n) - 1; 	// Se le quita 1 para la operacion del val. pos
	int contador = 1;
	
	/* Sacar el valor posicional */
	for (; largo > 0; contador *= 10) { 	// Contador es el valor posicional
		largo -= 1;
	}
	
	/* Función en sí */
	while (n > 0) { 	// Se crea el ciclo
		n_actual = n % 10; 	// Se saca el numero menos significativo
		n /= 10; 	// Se le quita el número a el n
		n_actual *= contador; 	// Se le da la posicion al n_actual
		inverso += n_actual; 	// Se añade al inverso
		contador /= 10; 	// EL contador se divide por 10 para bajar de pos.
	}
	return inverso; 	// Se devuelve el inverso
}

void es_Palindromo (int n) {
	/* Declaración de variables */
	int inverso = invertir_numero(n); 	// Se saca el inverso
	
	/* Función en sí */
	if (n == inverso) { 	// Si el n es igual al inverso entonces es palindromo
		printf("%d es palíndromo!\n", n);
	} else {
		printf("%d no es palíndromo :c\n", n); 	// Sino no es palindromo
	}
}
	

int main(int argc, char **argv){
	
	par_impar(5);
	par_impar(520);
	par_impar(9);
	
	fibo(5);
	fibo(15);
	fibo(7);
	
	factorial(5);
	factorial(10);
	factorial(8);
	
	printf("El largo de %d es %d\n", 350, for_largo_de_n(350));
	printf("El largo de %d es %d\n", 729823, for_largo_de_n(729823));
	printf("El largo de %d es %d\n", 17234, for_largo_de_n(17234));
	
	printf("El largo de %d es %d\n", 350, while_largo_de_n(350));
	printf("El largo de %d es %d\n", 729823, while_largo_de_n(729823));
	printf("El largo de %d es %d\n", 17234, while_largo_de_n(17234));
	
	for_sumatoria(5);
	for_sumatoria(15);
	for_sumatoria(30);
	
	while_sumatoria(5);
	while_sumatoria(15);
	while_sumatoria(30);
	
	printf("El inverso de %d es %d\n", 12, invertir_numero(12));
	printf("El inverso de %d es %d\n", 10, invertir_numero(10));
	printf("El inverso de %d es %d\n", 55, invertir_numero(55));
	
	es_Palindromo(12);
	es_Palindromo(10);
	es_Palindromo(55);
	
	return 0;
}
