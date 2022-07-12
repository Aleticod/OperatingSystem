// Nombre       : alarma.c
// Proposito    : Ejecuta un programa hasta que llegue la senial de alarma
// Autor        : Edwin Carrasco

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

// Variable global
bool banderaAlarma = false;

void alarmHandler() {
    printf("\n\t\tSe recibio una senial de alarma del reloj\a\n");
    banderaAlarma = true;
}

int main() {
    // Variable
    int tiempoAlarma;

    // Indicar proposito del programa
    printf("ESTE PROGRAMA SE EJECUTA HASTA QUE LLEGUE UNA SENIAL DE ALARMA\n");

    // Leer datos
    printf("Ingrese el tiempo en segundos despues del cual se debe generar la alarma: ");
    scanf("%d", &tiempoAlarma);

    // Registrar manejador de alarma
    signal(SIGALRM, alarmHandler);

    // Programar Alarma
    alarm(tiempoAlarma);

    printf("\nDebe ocurrir una alarma en pocos instates ...\n");

    while(!banderaAlarma) { // bucle hasta que llegue senial de alarma
        printf("\n\tEsperando alarma ...\n");
        pause();
    }

    printf("\nEl programa termina por la senial de alarma \n\n");

    return 0;
}
