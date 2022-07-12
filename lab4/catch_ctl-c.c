// Nombre       : catch_ctl-c.c
// Proposito    : Muestra la secuencia 0, 1, 2, 3 y maneja la senial SIGINT (presion de la tecla ctl + c)
// Author       : Edwin Carrasco Poblete

#include <signal.h> // Manejo de signals
#include <unistd.h> // Funcion sleep()
#include <stdio.h>
#include <stdlib.h>

static void sigHandler(int sig) {
    // Mensaje que se muestra al recibir una senial
    printf("Se recibio senial\n");
}

int main () {
    // Variables
    int j;

    // Indicar proposito del programa
    printf("ESTE PROGRAMA IMPRIME NUMEROS DE MANERA CRECIENTE Y MONITOREA LA COMBINACION DE TECLA CTL + C\n");

    // Registramos nuestro manejador de seniales
    if(signal(SIGINT, sigHandler) == SIG_ERR)
        exit(1);

    // Mostrar resultados
    for (j = 0; ; j++) {
        printf("%d\n", j);
        sleep(3);
    }

    // Salir
    return 0;
}
