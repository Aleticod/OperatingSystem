// Nombre       : hiloImpresor.c
// Proposito    : Imprime "P" y crea un hilo que imprime 'h'
// Autor        : Edwin Carrasco
// FCreacion    : 06/12/2017
// Compilacion  : gcc hiloImpresor.c -o hiloImpresor -lpthread -Wall

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// La funcion que va a ejecutar el hilo
void printChar (void) {
    while(1) {
        fputc('h',stderr);
    }

    // Terminar hilo
    pthread_exit(0);
}

int main() {
    // Variables
    pthread_t hilo;
    int iret;

    // Creamos un hilo que ejecuta el modulo printChar()
    iret = pthread_create(&hilo, NULL, (void*) printChar, NULL);

    printf("Este es el valor de iret: %i", iret);

    if(iret == -1) {
        exit(errno);
    }

    while(1) { // El proces imprime el caracer 'p'
        fputc('P',stderr);
    }

    // salir
    exit(0);
 }
