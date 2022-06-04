
// Nombre		: crearProcesoHijo.c
// Proposito	: Crea un proceso hijo y muestra su ID
// Autor		: E. Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ; //Variable externa

int main() {
	//Variables
	pid_t forkReturn;

	// Indicar proposito del programa
	puts("===ESTE PROGRAMA CREA UN PROCESO Y MUESTRA EL ID DEL PROCESO CREADO Y DEL PROCESO CREADOR===\n");

	// Procesar
	forkReturn = fork(); // Creamos el proceso

	// Mostrar resultados
	if(forkReturn == 0) { // Who am I?
		// Este codigo se ejecuta solo en el proceso hijo
		printf("Soy el proceso Hijo, mi PID es %d\n", getpid());
	}

	else {
		// Este codigo solo se ejecuta en el proceso padre
		printf("Soy el proceso padre, mi PID es %d\n", getppid());
	}

	// Salir
	return 0;
}
