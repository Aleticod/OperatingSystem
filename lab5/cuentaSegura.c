// Nombre	: cuentaSegura.c
// Proposito	: Opera sobre una cuenta bancaria controlando concurrencia
// Autor	: Edwin Carrasco
// FCreacion	: 20/07/2021
// Ejecucion	: ./cuentaSegura.exe
//
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semaforo;
int saldo = 100;

void *depositoSeguro() {
	sem_wait(&semaforo);
	int a = saldo;
	sleep(3);
	a = a + 10;
	saldo  = a;
	printf("El saldo despues del deposito es %d\n", saldo);
	sem_post(&semaforo);
	return 0;
}

void *retiroSeguro() {
	sem_wait(&semaforo);
	int b = saldo;
	sleep(3);
	b = b - 20;
	saldo = b;
	printf("El saldo despues del retiro es %d\n", saldo);
	sem_post(&semaforo);
	return 0;
}

int main() {
	pthread_t h1;
	pthread_t h2;
	sem_init(&semaforo, 0, 1);
	pthread_create(&h1, NULL, retiroSeguro, NULL);
	pthread_create(&h2, NULL, depositoSeguro, NULL);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	sem_destroy(&semaforo);
	printf("El saldo final es %d\n", saldo);
	return 0;
}

