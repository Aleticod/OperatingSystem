// Nombre		: numeroPrimo.c
// Proposito	: Identifica si un numero es primo o no
// Autor		: Alex Harvey Pfoccori Quispe
// FCreacion	: 06/05/2022
// FModif		:

#include <stdio.h>

int main() {
	// Variables
	int num, cont, lim;
	cont = 0;

	// Proceso
	printf("Ingrese el numero: ");
	scanf("%i", &num);

	lim = num / 2 ;

	for(int i = 1; i <= lim; i++) {
		if(num % i == 0)
			cont++;
	}

	if(cont == 1)
		printf("El numero es primo\n");
	else
		printf("El numero no es primo\n");
}
