// Nombre       : copair.c
// Proposito    : Copia una archivo utilizando archivos proyectados
// Autor        : Edwin Carrasco
// Fcreacion    : 14/12/2007
// Compilar     : ggc -o copiar copiar.exe -Wall

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    // Variables

    int i;
    int fdo;
    int fdd;
    char *org;
    char *dst;
    char *p;
    char *q;
    struct stat bstat;

    // Verificar los argumentos de entrada

    if (argc != 3) {
        fprintf(stderr, "Uso: %s orig dest \n", argv[0]);
        exit(1);
    }

    // Abre el archivo origen para lectura
    if ( (fdo = open(argv[1], O_RDONLY)) < 0) {
        perror("No se puede abrirse el archivo origin");
        exit(1);
    }

    // Crea el archivo destino
    if ( (fdd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR)) < 0) {
        perror("No se puede crearse el archivo destino");
        close(fdo);
        exit(1);
    }

    // Determinar la longitud del archivo origen

    if( fstat(fdo, &bstat) < 0) {
        perror("Error en la fstat del archivo origen");
        close(fdo);
        close(fdd);
        unlink(argv[2]);
        exit(1);
    }

    // Establecer que la cantidad del archivo destino es igual
    // a la del origen

    if( ftruncate(fdd, bstat.st_size) < 0) {
        perror ("Error en ftruncate del archivo destino");
        close(fdo);
        close(fdd);
        unlink(argv[2]);
        exit(1);
    }

    // Se proyecta el archivo origen
    if( (org =mmap((caddr_t)0, bstat.st_size, PROT_READ, MAP_PRIVATE, fdo, 0)) == MAP_FAILED) {
        perror("Error en la proyeccion del archov origen");
        close(fdo);
        close(fdd);
        unlink(argv[2]);
        exit(1);
    }

    // Se proyecta el archivo destino

    if(( dst =mmap((caddr_t)0, bstat.st_size, PROT_WRITE, MAP_SHARED, fdd, 0)) == MAP_FAILED) {
        perror("Error en la proyeccion del archivo destino");
        close(fdo);
        close(fdd);
        unlink(argv[2]);
        exit(1);
    }

    // Se cierran los archivos
    close(fdo);
    close(fdd);

    // Bucle de copia
    p=org;
    q=dst;
    for (i = 0; i < bstat.st_size; i++)
        *q++ = *p++;

    // Se eliminan las proyecciones
    munmap(org, bstat.st_size);
    munmap(dst, bstat.st_size);

    return 0;

}