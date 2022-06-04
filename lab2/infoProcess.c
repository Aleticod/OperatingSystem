// Nombre		: infoProcess.c
// Proposito	: Muestra informacion del usuario y el grupo de usuario que ejecuta un proceso
// Autor		: E. Carrasco
// FCreacion	:
// FModif		:

#include <stdio.h>
#include <unistd.h>

int main() {
	// Indicar el proposito del programa
	puts("\n===ESTE PROGRAMA MUESTRA INFORMACION DEL USUARIO QUE EJECUTA EL PROCESO===\n");

	// Mostrar resultados
	printf("Identificador de usuario: %d\n", getuid());
	printf("Identificador de usuario efectivo: %d\n", geteuid());
	printf("Identificador del grupo: %d\n", getgid());
	printf("Identificador de grupo efectivo: %d\n", getegid());

	// Salir
	return 0;
}
