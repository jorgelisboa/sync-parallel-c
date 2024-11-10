#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Mutex para proteger a variável de condição
pthread_mutex_t lock;
pthread_cond_t cond_var;

// Função da Thread 1 (envia um sinal para Thread 2)
void* thread1_func(void* arg) {
    printf("Thread 1: Processando...\n");

    // Simula um atraso com "sleep" (usado em sistemas Unix-like)
    sleep(1);

    // Bloqueia o mutex antes de enviar o sinal para garantir exclusão mútua
    pthread_mutex_lock(&lock);
    printf("Thread 1: Enviando sinal para Thread 2...\n");

    // Envia o sinal para que a Thread 2 possa continuar
    pthread_cond_signal(&cond_var);

    // Libera o mutex para outras threads poderem usá-lo
    pthread_mutex_unlock(&lock);

    return NULL;
}

// Função da Thread 2 (espera pelo sinal da Thread 1)
void* thread2_func(void* arg) {
    printf("Thread 2: Esperando sinal de Thread 1...\n");

    // Bloqueia o mutex e espera pelo sinal
    pthread_mutex_lock(&lock);

    // Espera até que a Thread 1 envie o sinal com `pthread_cond_signal`
    pthread_cond_wait(&cond_var, &lock);

    // Quando o sinal é recebido, a Thread 2 acorda e continua
    printf("Thread 2: Recebeu sinal, continuando execução...\n");

    // Libera o mutex após a execução
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inicializa o mutex e a variável de condição
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_var, NULL);

    // Cria as threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Espera as threads terminarem (junta as threads)
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destrói o mutex e a variável de condição após o uso
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_var);

    return 0;
}
