// Nombre		: crearNHijos.c
// Proposito	: Crea N hijos para un proceso
// Autor		: E. Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	// Variables
	pid_t forkReturn;
	int i;
	int n = 5;

	// Indicar proposito del programa
	puts("\n===ESTE PROGRAMA CREA N PROCESOS HIJOS Y CADA UNO MUESTRA SU IDENTIFICADOR Y EL DE SU PADRE===\n");

	// Procesar
	for(i = 0; i < n; i++) {
		forkReturn = fork();
		if(forkReturn == 0) {
			// Proceso que se ejecuta en el hijo
			break; // Si es el hijo, salir del bucle
		}
	}

	// Mostrar resultados
	printf("%d; El padre del proceso %d es %d \n", i, getpid(), getppid());
	while(1);
	// Salir
	return 0;
}
