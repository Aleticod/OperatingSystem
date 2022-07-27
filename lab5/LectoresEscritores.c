// Nombre		: LectoresEscritores.c
// Proposito	: Resuelve el problema de lectores/escritores con semáforos.
// Autores		: Alex H. Pfoccori Quispe y Marjorie Rodriguez Casas
// FCreacion	: 26/07/2022
// FModif.		:

#include <stdio.h>
#include <string.h>
#include <semaphore.h>  // Librería de semáforos
#include <pthread.h>  // Librería de hilos
#include <unistd.h>

sem_t lleno;  // Semáforo que controla si el buffer está lleno
sem_t vacio;  // Semáforo que controla si el buffer está vacío
sem_t mutex;  // Semáforo que garantiza la exclusión mutua

void *lector(void *arg)
{
   while(1)
   {
	sem_wait(&vacio);		// Decrecer el contador vacío
	sem_wait(&mutex);		// Entrar en la región crítica
	
	printf("Leyendo...\n");   // Mostrar valor producido

	sem_post(&mutex);	// Salir de la operación
	sem_post(&lleno);	// Incrementar contador de ranuras llenas
	sleep(1);
     }
     pthread_exit(0);
}

void *escritor(void *arg)
{
   while(1){
	sleep(3);	// El consumo toma 3 segundos
	sem_wait(&lleno);	// Decrecer el contador lleno
	sem_wait(&mutex);	// Entrar en la región crítica

	printf("\t\t\t\t\tEscribiendo... : \n");
    sleep(5);
    printf("\t\t\t\t\tActualizando...: \n");
	sem_post(&mutex);	// Salir de la región crítica
	sem_post(&vacio);	// Incrementar contador de ranuras vacías
    }
    pthread_exit(0);
}


int main()
{
    // Declarar hilos
    pthread_t idlect; // Lector
    pthread_t idescr; // Escritor

    // Inicializar semáforos
    sem_init(&lleno, 0, 0);	// Al inicio hay 0 elementos llenos
    
    sem_init(&vacio, 0 , 8);  // Al inico hay 8 elementos vacíos

    sem_init(&mutex, 0, 1); 	// Solo un hilo puede entrar en su región crítica

    printf("\nTamaño del buffer %d\n\n",8);
    printf("Para terminar la simulacion presionar ctrl + c\n\n");

    // Crear hilos
    pthread_create(&idlect, NULL, lector, NULL);  // Lector
    pthread_create(&idescr, NULL, escritor, NULL);  // Escritor

    // Terminar hilos
    pthread_join(idlect, NULL);
    pthread_join(idescr, NULL);
}
