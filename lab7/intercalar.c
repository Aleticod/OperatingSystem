// Nombre   	: intercalar.c
// Proposito	: Lee dos archivos de texto y crea un tercero con las líneas de los dos intercaladas.
// Autor	    : Alex H. Pfoccori Quispe y Marjorie R. Rodriguez Casas
// FCreacion	: 16/08/2022

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
    bool quien=true;
    int i,j;
    int fdo1, fdo2, fdd;
    char *or1;
    char *or2;
    char *des;
    char *p1;
    char *p2;
    char *q;
    struct stat bstat1;
    struct stat bstat2;

    if(argc != 4 )
    {
        fprintf(stderr,"Uso: %s origen1 origen2\n", argv[0]);
        exit(1);
    }

    if( (fdo1=open (argv[1], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 1");
        exit(1);
    }

    if( (fdo2= open(argv[2], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen 2");
        close(fdo1);
        exit(1);
    }

    if( (fdd=open(argv[3], O_CREAT|O_TRUNC|O_RDWR)) <0)
    {
        perror("No se puede crear el archivo de destino");
        close(fdo1);
        close(fdo2);
        exit(1);
    }
    if(fstat(fdo1, &bstat1)<0 )
    {
        perror("Error en fstat del archivo origen 1");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    if(fstat(fdo2, &bstat2)<0 )
    {
        perror("Error en fstat del archivo origen 2");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }

    if( ftruncate(fdd,bstat1.st_size + bstat2.st_size) < 0 ) 
    {
        perror("Error en ftruncate del archivo destino");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }
    if((or1=mmap((caddr_t)0,bstat1.st_size, PROT_READ,MAP_PRIVATE,fdo1,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo de origen 1");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }
    if((or2=mmap((caddr_t)0,bstat2.st_size, PROT_READ,MAP_PRIVATE,fdo2,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo de origen 2");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }
    if((des=mmap((caddr_t)0,bstat1.st_size+bstat2.st_size, PROT_WRITE,MAP_SHARED,fdd,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo de destino");
        close(fdo1);
        close(fdo2);
        close(fdd);
        unlink(argv[3]);
        exit(1);
    }


    close(fdo1);
    close(fdo2);
    close(fdd);

    p1=or1;
    p2=or2;
    q=des;
    int Aux= sqrt(bstat1.st_size + bstat2.st_size);
    for(i=0;i<Aux;i++)
    {
        while(*p1 !='\n')
            *q++ = *p1++;
        *p1++;
        *q++='\n';
        while(*p2 !='\n')
            *q++ = *p2++;
        *p2++;
        *q++='\n'; 
    }

    munmap(or1,bstat1.st_size);
    munmap(or2,bstat2.st_size);
    munmap(des,bstat1.st_size+bstat2.st_size);
    return 0;
}
