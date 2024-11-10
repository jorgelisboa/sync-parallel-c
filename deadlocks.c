#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Declaração de dois mutexes compartilhados
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Função executada pela primeira thread
void* thread1_func(void* arg) {
    printf("Thread 1: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);  // Bloqueia o mutex1
    printf("Thread 1: Mutex1 bloqueado.\n");

    usleep(100000);  // Simula algum trabalho (100 ms)

    printf("Thread 1: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);  // Tenta bloquear mutex2
    printf("Thread 1: Mutex2 bloqueado.\n");

    // Libera os mutexes
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    printf("Thread 1: Mutexes liberados.\n");
    return NULL;
}

// Função executada pela segunda thread
void* thread2_func(void* arg) {
    printf("Thread 2: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);  // Bloqueia o mutex2
    printf("Thread 2: Mutex2 bloqueado.\n");

    usleep(100000);  // Simula algum trabalho (100 ms)

    printf("Thread 2: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);  // Tenta bloquear mutex1
    printf("Thread 2: Mutex1 bloqueado.\n");

    // Libera os mutexes
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    printf("Thread 2: Mutexes liberados.\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Criação das threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Aguarda a finalização das threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroi os mutexes
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}
