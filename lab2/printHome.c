// Nombre 		: printHome.c
// Proposito	: Imprime el contenido de la variable de entorno HOME
// Autor		: E. Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	// Variables
	char *home = NULL;

	// Indicar el proposito del programa
	puts("\n===ESTE PROGRAMA MUESTRA EL CONTENIDO DE LA VARIABLE HOME DEL SISTEMA===\n");

	// Procesar y mostrar
	home = getenv("HOME");

	if(home == NULL)
		printf("HOME no se encuentra definida\n");
	else
		printf("El valor de HOME es %s\n", home);

	// Salir
	return 0;
}
