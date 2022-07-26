// Nombre	: exclusionMutua.c
// Proposito	: muestra la exclusion mutua mediante semaforos
// Autor	: Edwin Carrsco
// FC		: 20/07/2021
// Ejecución	: ./exclusionMutua.exe

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semaforo;


void *tareaHilo() {
	sem_wait(&semaforo);
	printf("\033[0;31m");
	printf("\nEl hilo %ld esta en su seccion critica\n", pthread_self());
	sleep(3);
	printf("\033[0;33m");
	printf("El hilo %ld sade su seccion critica\n", pthread_self());
	sem_post(&semaforo);
	return 0;
}

int main() {
	pthread_t h1;
	pthread_t h2;
	sem_init(&semaforo, 0, 1);
	pthread_create(&h1, NULL, tareaHilo, NULL);
	sleep(2);
	pthread_create(&h2, NULL, tareaHilo, NULL);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	sem_destroy(&semaforo);
	return 0;
}
