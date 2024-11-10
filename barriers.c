#include <pthread.h>
#include <stdio.h>

#define THREADS 3  // Constante com o número de threads que serão criadas

pthread_barrier_t barrier;  // Barreira

// Função que cada thread irá executar (mostra o caminho delas até/depois as barreiras)
void *thread_func(void *arg) {
    int id = *(int *)arg;  // Converte o argumento para um ID de thread
    printf("Thread %d chegou na barreira\n", id);

    // A thread aguarda na barreira até que todas as threads cheguem neste ponto
    pthread_barrier_wait(&barrier);

    // Após todas as threads chegarem na barreira, elas prosseguem a partir deste ponto
    printf("Thread %d passou pela barreira\n", id);
    return NULL;
}

int main() {
    pthread_t threads[THREADS];  // Array para armazenar as threads
    int ids[THREADS];            // Array para armazenar os IDs das threads

    // Inicializa a barreira para sincronizar THREADS threads
    pthread_barrier_init(&barrier, NULL, THREADS);

    // Criação das threads
    for (int i = 0; i < THREADS; i++) {
        ids[i] = i + 1;  // Define o ID da thread (de 1 a THREADS)
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);  // Cria a thread e passa o ID como argumento
    }

    // Aguarda que todas as threads terminem
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);  // Bloqueia até que a thread 'i' termine
    }

    // Destrói a barreira
    pthread_barrier_destroy(&barrier);

    return 0;
}
