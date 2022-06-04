// Nombre		: entornoProc.c
// Proposito	: Imprime informacion del entorno de un proceso
// Autor		: E. Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>

extern char **environ; // Variable externa

int main() {
	// Variables
	char **var;

	// Indicar proposito del programa
	puts("\n===ESTE PROGRAMA MUESTRA INFORMACION DEL ENTORNO DE UN PROCESO===\n");

	// Procesar y mostrar resultados

	for(var = environ; *var != NULL; ++var)
		printf("%s\n",*var);

	// Salir
	return 0;
}
