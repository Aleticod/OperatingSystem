// Nombre   	: comparar.c
// Proposito	: Compara dos archivos utilizando archivos proyectados en memoria.
// Autor	    : Alex H. Pfoccori Quispe y Marjorie R. Rodriguez Casas
// FCreacion	: 16/08/2022
// Compilacion  : gcc comparar.c -o comparar.exe -Wall
// Ejecucion    : ./comparar.exe archivo1.txt archivo2.txt

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char **argv) 
{
    // Variables
    int i;
    int fd1, fd2;   // Apertura de archivo
    char *ar1;      // Recibiran las proyecciones
    char *ar2;
    char *p;
    char *q;
    struct stat bstat1;
    struct stat bstat2;

    // Verificacion de los argumentos
    if(argc != 3 )
    {
        fprintf(stderr,"Uso: %s origen1 origen2 \n", argv[0]);
        exit(1);
    }

    // Abre el primer archivo de origen para lectura
    if( (fd1=open (argv[1], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 1");
        exit(1);
    }

    // Abre el segundo archivo de origen para lectura
    if( (fd2=open (argv[2], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 2 ");
        close(fd1);
        exit(1);
    }

    // Determina la longitud del primer archivo
    if(fstat(fd1, &bstat1)<0 )
    {
        perror("Error en fstat del archivo 1");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }

    // Determina la longitud del segundo archivo
    if(fstat(fd2, &bstat2)<0 )
    {
        perror("Error en fstat del archivo 2");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }

    // Se proyecta el archivo 1
    if((ar1=mmap((caddr_t)0,bstat1.st_size, PROT_READ,MAP_PRIVATE,fd1,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo 1");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }
    // Se proyecta el archivo 2
    if((ar2=mmap((caddr_t)0,bstat2.st_size, PROT_READ,MAP_PRIVATE,fd2,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo 2");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }

    // Se cierran los archivos
    close(fd1);
    close(fd2);
    
    // Comprobat
    p=ar1;
    q=ar2;

    // Primero comparamos los tamanios
    if(bstat1.st_size != bstat2.st_size)
    {
        printf("Los archivos no son iguales\n");
        munmap(ar1,bstat1.st_size);
        munmap(ar2,bstat2.st_size);
        exit(0);
    }

    // En el caso que ambos tienen el mismo tamanio
    for(i=0;i<bstat1.st_size;i++)
        if(*q++ != *p++)
        {
            break;
        }

    
    if(i != bstat1.st_size)
    {
            printf("Los archivos son diferentes \n");
    }
    else
    {
            printf("Los archivos son iguales \n");
    }

    munmap(ar1,bstat1.st_size);
    munmap(ar2,bstat2.st_size);

    // Salir
    return 0;
}
