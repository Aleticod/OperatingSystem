// Nombre		: craerHijo.c
// Proposito	: Muestra la relacion padre/hijo entre procesos
// Autor		: Edwin Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	// Variables
	pid_t idProceso; // Tipo de dato "identificador del proceso"

	idProceso = fork(); // Crear proceso hijo

	if(idProceso == 0) {
		// Solo se ejecuta en el proceso hijo
		printf("Soy el proceso hijo. mi id es: %d. ", getpid());
		printf("El id de mi padre es:  %d\n", getppid());
		while(1);
	}
	else {
		// Solo se ejecuta en el proceso padre
		printf("Soy el proceso padre. Mi id es: %d. ", getpid());
		printf("El id de mi padre es: %d\n", getppid());
		while(1);
	}

	// Salir
	return 0;
}
