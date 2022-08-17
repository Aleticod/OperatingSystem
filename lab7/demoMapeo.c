// Nombre       : demoMapeo.c
// Proposito    : Muestra el caracter ubicado en una posicion de un archivo
// Author       : Edwin Carrasco Poblete
// FCreacion    : 25/04/2013
// Ejecutar     : ./demoMapeo.exe archOrig.txt 5

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char *argv[] ){
    // Variables
    int fd;

    int offset;
    char *data;
    struct stat sbuf;

    // Verificar que le programa se haya invocado correctamente
    if (argc != 3) {
        fprintf(stderr, "Uso: demoMapeo.exe <Archivo> <Posicion>\n");
        exit(1);
    }

    // Indicar proposito del program
    printf("ESTE PROGRAMA MUESTRA EL CARACTER DE UN ARCHIVO, EN UNA POSICION PASADA COMO ARGUMENTO\n");

    // Procesar
    if( ( fd = open(argv[1], O_RDONLY)) == -1) {
        perror("Error en operacion de apertura de archivo\"open\"");
        exit(1);
    }

    if(stat (argv[1], &sbuf) == -1) {
        perror("Error en operaciones\"stat\"");
        exit(1);
    }

    offset = atoi(argv[2]);
    if (offset < 0 || offset > sbuf.st_size - 1) {
        fprintf(stderr, "La posicion debe estar en el rango 0 - %ld\n", sbuf.st_size - 1);
        exit(1);
    }

    data = mmap( (caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);

    if(data == (caddr_t)(-1)) {
        perror("Error al mapear el archivo (mmap)");
        exit(1);
    }

    // Mostrar resultados
    printf("El byte en la posicion %d es %c\n", offset, data[offset]);

    // Salir
    return 0;
}