// Nombre	    : spinlock.c
// Proposito	: Uso de la sincronizacion spinlock
// Autor	    : Alex H. Pfoccori Quispe y Marjorie Rodriguez Casa
// FCreacion	: 31/06/2022
//
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TAMBUF 10

int buffer[TAMBUF];
int elementos = 0;

// Declaracion del spinlock que controlara el proceso
pthread_spinlock_t lock;

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

            //inicio del spinlock (bloquear los otros procesos)
            pthread_spin_lock(&lock);

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

            //finalizacion del spinlock (desbloquear otro proceso)
            pthread_spin_unlock(&lock);
            sleep(3);
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
            //inicio del spinlock (bloquear los otros procesos)
            pthread_spin_lock(&lock);


            // Sacar un elemento del buffer
            consumido = buffer[indicec];
            elementos --;

            // Marcar posición consumida
            buffer[indicec] = asterisco;

            // Actualizar indecec
            indicec = (indicec + 1) % TAMBUF;

            // Mostrar elemento consumido
            printf("\t\t\t\t\tSacando: %c\n", consumido);

            //finalizacion del spinlock (desbloquear otro proceso)
            pthread_spin_unlock(&lock);
        }
		
	}

	pthread_exit(0);
}

int main() {
	// Declaracion de hilos
	pthread_t idprod;
	pthread_t idcons;

	srand(time(0));
    // Inicializacion del spinlock
	pthread_spin_init(&lock, 1);

	printf("\n tamaño del buffere %d\n\n", TAMBUF);
	printf("Para terminar la simulacion presiona CTRL + C\n\n");

	pthread_create (&idprod, NULL, productor, NULL);
	pthread_create (&idcons, NULL, consumidor, NULL);
	
	pthread_join(idprod, NULL);
	pthread_join(idcons, NULL);

	return 0;
}	