// Nombre   	: caracteres.c
// Propósito	: Muestra la frecuencia de caracteres en inglés de un archivo de texto proyectado en memoria.
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
    int fd;
    char counter=0;
    char *ar;
    char *p;
    struct stat bstat;

    if(argc != 2 )
    {
        fprintf(stderr,"Uso: %s origen origen \n", argv[0]);
        exit(1);
    }

    if( (fd=open (argv[1], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen ");
        exit(1);
    }

    if(fstat(fd, &bstat)<0 )
    {
        perror("Error en fstat del archivo ");
        close(fd);
        exit(1);
    }


    if((ar=mmap((caddr_t)0,bstat.st_size, PROT_READ,MAP_PRIVATE,fd,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo ");
        close(fd);
        exit(1);
    }

    char A[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    close(fd);
    int k;
    p=ar;
    for(k=0;k<26;k++){
        
        for(i=0;i<bstat.st_size;i++){   
            if(*p++==A[k])
            {
                counter++;
            }
    }
    p=ar;
    if(counter != 0){
        printf("La letra %c aparece %d veces en el archivo \n",A[k],counter);
    }
    counter=0;
    }
    munmap(ar,bstat.st_size);
    return 0;
}
