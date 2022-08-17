// Nombre   	: comparar.c
// Proposito	: Compara dos archivos utilizando archivos proyectados en memoria.
// Autor	    : Alex H. Pfoccori Quispe y Marjorie R. Rodriguez Casas
// FCreacion	: 16/08/2022

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char **argv) 
{
    int i;
    int fd1, fd2;
    char *ar1;
    char *ar2;
    char *p;
    char *q;
    struct stat bstat1;
    struct stat bstat2;

    if(argc != 3 )
    {
        fprintf(stderr,"Uso: %s origen origen \n", argv[0]);
        exit(1);
    }

    if( (fd1=open (argv[1], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 1");
        exit(1);
    }
    if( (fd2=open (argv[2], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 2 ");
        close(fd1);
        exit(1);
    }

    if(fstat(fd1, &bstat1)<0 )
    {
        perror("Error en fstat del archivo 1");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }
    if(fstat(fd2, &bstat2)<0 )
    {
        perror("Error en fstat del archivo 2");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }
    // Proyectar archivo 1
    if((ar1=mmap((caddr_t)0,bstat1.st_size, PROT_READ,MAP_PRIVATE,fd1,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo 1");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }
    //Proyectar archivo 2
    if((ar2=mmap((caddr_t)0,bstat2.st_size, PROT_READ,MAP_PRIVATE,fd2,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo 2");
        close(fd1);
        close(fd2);
        unlink(argv[2]);
        exit(1);
    }
    close(fd1);
    close(fd2);
    
    // Comprobar
    

    p=ar1;
    q=ar2;
    if(bstat1.st_size != bstat2.st_size)
    {
        printf("Los archivos no son iguales\n");
        munmap(ar1,bstat1.st_size);
        munmap(ar2,bstat2.st_size);
        exit(0);
    }
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
    return 0;
}
