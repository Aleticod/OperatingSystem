// Nombre       : espearHilo.c
// Proposito    : Crear dos hilos y esperar a que terminen
// Autor        : Edwin Carrasco
// FCreacion    : 06/12/2007
// Compilar     : gcc esperarHilo.c -o esperarHilo -Wall -pthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void tarea (void) { // tarea que realiza el hilo
    printf("\tSoy el hilo con el Id: %u\n", (unsigned int)pthread_self());
    pthread_exit(0);
}

int main() {
    // Variables
    pthread_t hilo1;
    pthread_t hilo2;
    int iret1, iret2;

    // Indicar el proposito del programa
    printf("SE CREAN DOS HILOS QUE MUESTRAN SUS IDENTIFICADORES\n");

    // Procesar
    iret1 = pthread_create(&hilo1, NULL, (void*) tarea, NULL);
    
    printf("El valor del iret1 es: %i\n", iret1);

    if(iret1 != 0) {
        exit(errno);
    }  

    iret2 = pthread_create(&hilo2, NULL, (void*) tarea, NULL);

    printf("El valor del iret2 es: %i\n", iret2);
   
    if(iret1 != 0) {
        exit(errno);
    }

    printf("El programa principal %d sigue ejecutandose\n", getpid());

    // Eperar la conclusion de los hilos

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("Los hilos creados han terminado\n");
    printf("El programa principal tambien termina...\n");

    // Salir
    exit(0);
}
