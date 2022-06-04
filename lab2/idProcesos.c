// Nombre		: idProcesos.c
// Proposito	: Muestra el PID de procesos padre e hijo
// Autor		: E. Carrasco
// FCreacion	: 
// FModif		:

#include <stdio.h>
#include <unistd.h>

int main() {
	// Variables
	pid_t id_proceso;
	pid_t id_padre;

	// Indicar proposito del programa
	puts("\n== ESTE PROGRAMA MUESTRA EL IDENTIFICADOR DE UN PROCESO Y EL DE SU PROCESO PADRE ==\n");

	// Procesar
	id_proceso = getpid();
	id_padre = getppid();

	// Mostrar resultados
	printf("Identificador de proceso: %d\n", id_proceso);
	printf("Identificador del proceso padre: %d\n", id_padre);

	// Salir
	return 0;
}
