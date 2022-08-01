// Nombre   	: barrier.c
// Proposito	: Uso de sincronizacion con barrier
// Autor	    : Alex H. Pfoccori Quispe
// FCreacion	: 31/07/2022
//
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TAMBUF 10

int buffer[TAMBUF];
int elementos = 0;

// Declaracion de la barrera
pthread_barrier_t barrera;

// Productor
void *productor(void *arg) {
	// Variables
	int j;
	int indicep = 0;
	int producido;

	while(1) {
		// producir un elemento
		producido = (rand() % 26) + 65;

        if (elementos == 0 || elementos < TAMBUF) {
           // se inicia barrier wait
            pthread_barrier_wait(&barrera);

            // agregar elemento al buffer
            buffer[indicep] = producido;
            elementos ++;

            // actualizar indecep
            indicep = (indicep + 1) % TAMBUF;

            // Mostrar elemento producido
            printf("Agregando: %c\n", producido);

            // Mostrar el buffer
            for( j = 0; j < TAMBUF; j++)
                printf("%c\t", buffer[j]);

            printf("\n\n");

            sleep(3);
        }
        else {
            continue;
        }
		
	}

	pthread_exit(0);
}

// Consumidor
void *consumidor(void *arg) {
	// Variables
	int indicec = 0;
	int consumido;
	int asterisco = 42;

	while(1) {
		sleep(4);
        if (elementos != 0 || elementos <= TAMBUF ) {
            // Se inicia barrier wait
            pthread_barrier_wait(&barrera);   

            // Sacar un elemento del buffer
            consumido = buffer[indicec];
            elementos --;

            // Marcar posición consumida
            buffer[indicec] = asterisco;

            // Actualizar indecec
            indicec = (indicec + 1) % TAMBUF;

            // Mostrar elemento consumido
            printf("\t\t\t\t\tSacando: %c\n", consumido);
        }
		
	}

	pthread_exit(0);
}

int main() {
	// Declaracion de hilos
	pthread_t idprod;
	pthread_t idcons;

	srand(time(0));

    // Inicializamos barrier
	pthread_barrier_init(&barrera, NULL, 1);

	printf("\n tamaño del buffere %d\n\n", TAMBUF);
	printf("Para terminar la simulacion presiona CTRL + C\n\n");

	pthread_create (&idprod, NULL, productor, NULL);
	pthread_create (&idcons, NULL, consumidor, NULL);
	
	pthread_join(idprod, NULL);
	pthread_join(idcons, NULL);

    // Destuimos el barrier
    pthread_barrier_destroy(&barrera);

	return 0;
}	