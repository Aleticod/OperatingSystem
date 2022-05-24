// Nombre			: busquedaAutor.c
// Proposito		: Administra un catalogo de libros
// Autores			: A. Harvey Pfoccori y Marjorie Rodriguez Casas
// FCreacion		: 22/05/2022
// FModif			: 24/05/2022

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define tam 5		// Maximo numero de libros en catalogo

// Definicion de la estructura tLibro
struct tLibro {
	char titulo[51]; // Array string  titulo de tamanio 50
	char autor[51];  // Array string  autor de tamanio 50
};

// Leer datos de un nuevo libro
void leerDatos(struct tLibro * libro) {
	printf("Ingrese el titulo (tam max 50 letras): ");
	scanf("%[^\n]%*c", libro -> titulo);
	fflush(stdin);
	printf("Ingrese el autor (tam max 50 letras): ");
	scanf("%[^\n]%*c", libro -> autor);
}

// Mostrar datos del libro (titulo y autor)
void mostrarDatos(struct tLibro * libro) {
	printf("Titulo: %s\t\tAutor: %s\n", libro -> titulo, libro -> autor);
}

// Buscar un libro por titulo
bool buscarTitulo(struct tLibro c[], char criterio[]) {
	int i;
	for(i = 0; i < tam; i++) {
		if(strcmp(c[i].titulo, criterio) == 0)
			return true;
	}
	return false;
}

// Buscar un libro por autor
bool buscarAutor(struct tLibro c[], char criterio[]) {
	int i;
	for(i = 0; i < tam; i++) {
		if(strcmp(c[i].autor,criterio) ==0)
			return true;
	}
	return false;
}

// Menu
void mostrarMenu() {
	puts("");
	puts("********* SISTEMA DE GESTION DE LIBROS **********");
	puts("*                                               *");
	puts("*    1. Insertar Libros                         *");
	puts("*    2. Mostrar Catalogo                        *");
	puts("*    3. Buscar por titulo                       *");
	puts("*    4. Buscar por autor                        *");
	puts("*    5. Salir                                   *");
	puts("*                                               *");
	puts("*************************************************");
	puts("");
}

int main () {
	// Variables
	struct tLibro catalogo[tam];
	char datos[51];
	char aux[2];
	int opcion;
	int i = 0;
	int j;

	do {
		// Indicar que hacer al programa
		mostrarMenu();

		// Leer datos
		printf("\nIngrese una opcion (1-5): ");
		scanf("%[^\n]%*c", aux);
		opcion = atoi(aux);
		switch(opcion) {
			case 1:
				// Agregar titulo y autor
				if(i < tam) {
					leerDatos(&catalogo[i]);
					i++;
				}
				break;
			case 2:
				// Mostrar catalogo
				for(j = 0; j < tam; j++)
					mostrarDatos(&catalogo[j]);
				break;
			case 3:
				// Mostrar buscar por titulo
				printf("Ingrese el titulo del texto (tam max 50 letras): ");
				scanf("%[^\n]%*c", datos);
				puts(datos);
				if(buscarTitulo(catalogo,datos))
					printf("\nUrraaaa!!! El titulo existe en la biblioteca\n\n");
				else
					printf("\nUppsss!!!! El titulo no existe en la biblioteca\n\n");
				break;
			case 4:
				// Mostrar buscar por autor
				printf("Ingrese el autor del texto (tam max 50 letras): ");
				scanf("%[^\n]%*c", datos);
				puts(datos);
				if(buscarAutor(catalogo,datos))
					printf("\nUrraaaa!!!! El autor existe en la biblioteca\n\n");
				else
					printf("\nUppss!!!! El autor no existe en el biblioteca\n\n");
				break;
			case 5:
				break;
			default:
				puts("La opcion no es correcta");
				break;
		}
	} while(opcion != 5);
}
