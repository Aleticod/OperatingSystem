// Nombre       : infoAccessFile.c
// Proposito    : Mostrar la informacion de un elemento pasado como argumento
// Autor        : Alex H. Pfoccori Quispe
// FCreacion    : 30/08/2022
// FMod         : --
// Compilacion  : gcc infoAccessFile.c -o infoAccessFile.exe -Wall
// Ejecucion    : ./infoAccessFile.exe archivo.txt

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main( int argc, char *argv[]) {

    // Variables y constantes
    const char *FILE;
    struct stat infoAcess;
    int ret;

    // Procesar y mostrar resultados
    if(argc < 2) {
        fprintf(stderr, "Uso del programa: %s <archivo> \n", argv[0]);
        return 1;
    }

    // Pasamos el argumento a la constante FILE
    FILE = argv[1];

    printf("Obteniendo permisos de modo de acceso para %s: \n", FILE);

    ret = stat(FILE, &infoAcess);

    if(ret == -1) {
        fprintf(stderr, "Error en el archivo\n");
        exit(1);
    }

    printf("Tipo de elemento de: %s\n", FILE);

    // Procesar tipo elemento
    if(S_ISREG(infoAcess.st_mode)) {
        puts("  |-> Archivo regular\n");
    }
    else if(S_ISDIR(infoAcess.st_mode)) {
        puts("  |-> Directorio\n");
    }
    else if(S_ISLNK(infoAcess.st_mode)) {
        puts("  |-> Link simbolico\n");
    }
    
    printf("Informacion de acceso de: %s\n", FILE);

    //Procesar informacion de acceso del elemento
    printf(" Informacion de acceso para PROPIETARIO\n");

    if(infoAcess.st_mode & S_IRUSR){
        printf("   + Lectura\n");
    }
    if(infoAcess.st_mode & S_IWUSR){
        printf("   + Escritura\n");
    }
    if(infoAcess.st_mode & S_IXUSR){
        printf("   + Ejecucion\n");
    }
    
    putchar('\n');

    printf(" Informacion de acceso para GRUPO\n");
    if(infoAcess.st_mode & S_IRGRP){
        printf("   + Lectura\n");
    }
    if(infoAcess.st_mode & S_IWGRP){
        printf("   + Escritura\n");
    }
    if(infoAcess.st_mode & S_IXGRP){
        printf("   + Ejecucion\n");
    }

    putchar('\n');

     printf(" Informacion de acceso para OTROS\n");
    if(infoAcess.st_mode & S_IROTH){
        printf("   + Lectura\n");
    }
    if(infoAcess.st_mode & S_IWOTH){
        printf("   + Escritura\n");
    }
    if(infoAcess.st_mode & S_IXOTH){
        printf("   + Ejecucion\n");
    }
    putchar('\n');

}