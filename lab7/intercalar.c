// Nombre   	: intercalar.c
// Proposito	: Lee dos archivos de texto y crea un tercero con las líneas de los dos intercaladas.
// Autor	    : Alex H. Pfoccori Quispe y Marjorie R. Rodriguez Casas
// FCreacion	: 16/08/2022
// Compilacion  : gcc intercalar.c -o intercalar.exe -Wall
// Ejecucion    : ./intercalar.exe archivo1.txt archivo2.txt archResult.txt -lm

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(int argc,char **argv) 
{
    // Variables
    int cont1 = 0;
    int cont2 = 0;
    int contT = 0;
    int fdo1, fdo2, fdd;
    char *or1;
    char *or2;
    char *des;
    char *p1;
    char *p2;
    char *q;
    struct stat bstat1;
    struct stat bstat2;

    // Verificar los argumentos
    if(argc != 4 )
    {
        fprintf(stderr,"Uso: %s origen1 origen2 destino\n", argv[0]);
        exit(1);
    }

    // Abrir el primer archivo de origen
    if( (fdo1=open (argv[1], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 1");
        exit(1);
    }

    // Abrir el segundo archivo de origen
    if( (fdo2= open(argv[2], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 2");
        close(fdo1);
        exit(1);
    }

    // Crear el archivo de destino
    if( (fdd=open(argv[3], O_CREAT|O_TRUNC|O_RDWR)) <0)
    {
        perror("No se puede crear el archivo de destino");
        close(fdo1);
        close(fdo2);
        exit(1);
    }

    // Determinar la longitud del primer archivo de origen
    if(fstat(fdo1, &bstat1)<0 )
    {
        perror("Error en fstat del archivo origen 1");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    // Determinar la longitud del segundo archivo de origen
    if(fstat(fdo2, &bstat2)<0 )
    {
        perror("Error en fstat del archivo origen 2");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    // Establecer que la longitud del archivo destino es igual
    // a la suma de las longitudes de los archivos de origen
    if( ftruncate(fdd,bstat1.st_size + bstat2.st_size) < 0 ) 
    {
        perror("Error en ftruncate del archivo destino");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    // Se proyecta el primer archivo de origen
    if((or1=mmap((caddr_t)0,bstat1.st_size, PROT_READ,MAP_PRIVATE,fdo1,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo de origen 1");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    // Se proyecta el segundo archivo de origen
    if((or2=mmap((caddr_t)0,bstat2.st_size, PROT_READ,MAP_PRIVATE,fdo2,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo de origen 2");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    // Se proyecta el archivo de destino
    if((des=mmap((caddr_t)0,bstat1.st_size+bstat2.st_size, PROT_WRITE,MAP_SHARED,fdd,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo de destino");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    // Se cierran los archivos
    close(fdo1);
    close(fdo2);
    close(fdd);

    p1=or1;
    p2=or2;
    q=des;

    int Aux = bstat1.st_size + bstat2.st_size;
    
    while (contT < Aux)
    {   if (cont1 < bstat1.st_size) {
            while(*p1 !='\n') {
                *q++ = *p1++;
                cont1++;
            }
            
            *q++=*p1++;
            cont1++;
        }
        if (cont2 < bstat2.st_size) {
            while(*p2 !='\n') {
                *q++ = *p2++;
                cont2++;
            }
            
            *q++=*p2++;
            cont2++;
        }
        contT = cont1 + cont2;
    }

    munmap(or1,bstat1.st_size);
    munmap(or2,bstat2.st_size);
    munmap(des,bstat1.st_size+bstat2.st_size);
    return 0;
}
