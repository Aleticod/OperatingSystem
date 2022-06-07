// Nombre		: sumProcessID.c
// Proposito	: Verifica si la suma de los PIDs del padre e hijo es primo o no.
// Autores		: Alex H. Pfoccori Quispe y Marjorie Rodriguez Casas
// FCreacion	: 05/06/2022
// FModif.		:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	// Variables
	pid_t forkReturn, sumPID;

	// Indicar el proposito del programa
	puts("===ESTE PROGRAMA VERIFICA SI LA SUMA DE LOS PIDs DEL PADRE E HIJO ES PRIMO O NO===");
	// Procesar
	forkReturn = fork(); // Creamos el proceso hijo

	if(forkReturn == 0) {
		// Este codigo se ejecuta solo en el proceso hijo

		// Codigo que verifica si la suma es primo o no

		// Variables
		int lim, cont;

		// Procesar
		sumPID = getppid() + getpid();

		lim = sumPID / 2;
		cont = 0;

		printf("\nESTE PROCESO SE EJECUTA EN EL PROCESO HIJO\n");

		printf("La suma de los procesos es: %d\n", sumPID);
		for(int i = 1; i <= lim; i++) {
			if(sumPID % i == 0)
				cont++;
		}

		if(cont == 1)
			printf("La suma de PIDs es primo\n");
		else
			printf("La suma de PIDs no es primo\n");

		printf("Soy el proceso hijo. Mi id es: %d. ", getpid());
		printf("El id de mi padre es: %d\n", getppid());
		while(1);
	}
	else {

		// Este bloque se ejecuta en el proceso Padre
		printf("ESTE PROCESO SE EJECUTA EN EL PROCESO PADRE\n");
		printf("Soy el proceso padre. Mi PID es: %d. ", getpid());
		printf("El id de mi padre es: %d\n", getppid());
		while(1);
	}

	// Salir
	return 0;
}
