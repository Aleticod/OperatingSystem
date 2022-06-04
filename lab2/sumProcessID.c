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
	pid_t forkReturn, pidHijo, pidPadre, sumPID;

	// Indicar el proposito del programa

	// Procesar
	forkReturn = fork(); // Creamos el proceso hijo

	if(forkReturn == 0) {
		// Este codigo se ejecuta solo en el proceso hijo
		int lim, cont;
		pidPadre = getppid();
		pidHijo = getpid();
		sumPID = pidPadre + pidHijo;
		lim = sumPID / 2;
		cont = 0;
		printf("Soy el proceso hijo. Mi id es: %d. ", getpid());
		printf("El id de mi padre es: %d\n", getppid());
		printf("La suma de los procesos se: %d\n", sumPID);
		for(int i = 1; i <= lim; i++) {
			if(sumPID % i == 0)
				cont++;
		}

		if(cont == 0)
			printf("La suma de PIDs es primo\n");
		else
			printf("La suma de PIDs no es primo\n");
		while(1);
	}
	else {
		printf("Soy el proceso padre. Mi id es: %d. ", getpid());
		printf("El id de mi padre es: %d\n", getppid());
		while(1);
	}

	// Salir
	return 0;
}
