// Nombre 		: nombreMasId.c
// Proposito	: Muestra el nombre y el identificador de un proceso
// Author		: Edwin Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>
#include <sys/types.h>  // Tipos de datos v.g. pid_t
#include <unistd.h>

int main (int argc, char *argv[]) {
	// Variables
	char *nombreDePrograma = argv[0]; // Lee el nombre del programa de la linea de comando
	pid_t processId;
	pid_t processIdFather;

	// Indicar proposito del programa
	puts("\n===ESTE PROGRAMA MUESTRA SU NOMBRE Y SU IDENTIFICADOR DE PROCESO===\n");

	// Procesar
	processId = getpid();
	processIdFather = getppid();

	// Mostrar resultados
	// Sumamos 2 para omitir los caracteres "./"

	printf("Mi nombre de programa es: %14s\n", nombreDePrograma + 2);
	printf("Mi identificador de proceso es: %6d\n\n", processId);
	printf("El identificador de mi padre es: %d\n", processIdFather);

	// Salir
	return 0;
}
