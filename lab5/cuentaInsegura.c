// Nombre	: cuentaInsegura.c
// Proposito	: Opera sobre una cuenta bancaria sin control sin control de concurrecia
// Autor	: Edwin Carrasco
// FCreación	: 20/07/ 2021
// Ejecucion 	: ./cuentaInsegura.exe
//
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int saldo = 100;

void *depositoInseguro() {
	int a = saldo;
	a = a + 10;
	sleep(3);
	saldo = a;
	printf("El saldo del deposito es %d\n", saldo);
	return 0;
}

void *retiroInseguro() {
	int b = saldo;
	b = b - 20;
	sleep(3);
	saldo = b;
	printf("El saldo despues del retiro es %d\n", saldo);
	return 0;
}

int main() {
	pthread_t h1;
	pthread_t h2;
	pthread_create(&h1,NULL, retiroInseguro, NULL);
	pthread_create(&h2, NULL, depositoInseguro, NULL);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	printf("El saldo final es %d\n", saldo);
	return 0;
}
