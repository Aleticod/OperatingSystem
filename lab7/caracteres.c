// Nombre   	: caracteres.c
// Propósito	: Muestra la frecuencia de caracteres en inglés de un archivo de texto proyectado en memoria.
// Autor	    : Alex H. Pfoccori Quispe y Marjorie R. Rodriguez Casas
// FCreacion	: 16/08/2022
// Compilacion  : gcc caracter.c -o caracter.exe -Wall
// Ejecucion    : ./caracter.exe archivo1.txt

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc,char **argv) 
{
    int i;
    int fd;
    char counter=0;
    char *ar;
    char *p;
    struct stat bstat;

    // Verificar argumentos
    if(argc != 2 )
    {
        fprintf(stderr,"Uso: %s origen origen \n", argv[0]);
        exit(1);
    }

    // Abrir archivos
    if( (fd=open (argv[1], O_RDONLY))<0 )
    {
        perror("No se puede abrir el archivo de origen ");
        exit(1);
    }

    // Determinamos la longitud del archivo
    if(fstat(fd, &bstat)<0 )
    {
        perror("Error en fstat del archivo ");
        close(fd);
        exit(1);
    }

    // Se proyecta el archivo
    if((ar=mmap((caddr_t)0,bstat.st_size, PROT_READ,MAP_PRIVATE,fd,0))==MAP_FAILED)
    {
        perror("Error en la proyeccion del archivo ");
        close(fd);
        exit(1);
    }

    // Se cierra el archivo
    close(fd);
    
    // Calculo de frecuencias
    char A[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    int k;
    p=ar;
    for(k=0;k<26;k++){
        
        for(i=0;i<bstat.st_size;i++){   
            if(tolower(*p++)==A[k])
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

    // Se eliminan las proyecciones
    munmap(ar,bstat.st_size);
    return 0;
}
