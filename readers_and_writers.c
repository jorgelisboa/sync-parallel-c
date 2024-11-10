#include <pthread.h>
#include <stdio.h>

pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex para proteger o recurso de escrita
pthread_mutex_t reader_count_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex para proteger o contador de leitores
int reader_count = 0;  // Contador de leitores ativos

void *reader(void *arg) {
    // Protege o incremento de leitores para evitar concorrência
    pthread_mutex_lock(&reader_count_mutex);
    reader_count++;
    // Se é o primeiro leitor, bloqueia o recurso para impedir escritores
    if (reader_count == 1) {
        pthread_mutex_lock(&resource_mutex);
    }
    pthread_mutex_unlock(&reader_count_mutex);

    // Seção crítica de leitura
    printf("Leitor %d está lendo\n", *(int *)arg);

    // Protege o decremento do contador de leitores
    pthread_mutex_lock(&reader_count_mutex);
    reader_count--;
    // Se é o último leitor, libera o recurso para os escritores
    if (reader_count == 0) {
        pthread_mutex_unlock(&resource_mutex);
    }
    pthread_mutex_unlock(&reader_count_mutex);

    return NULL;
}

void *writer(void *arg) {
    // Escritores bloqueiam o recurso completamente para garantir exclusividade
    pthread_mutex_lock(&resource_mutex);

    // Seção crítica de escrita
    printf("Escritor %d está escrevendo\n", *(int *)arg);

    // Libera o recurso para outros leitores ou escritores
    pthread_mutex_unlock(&resource_mutex);
    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];  // Menor número de threads para facilitar o acompanhamento
    int ids[3] = {1, 2, 3};

    // Criação das threads leitoras
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    // Criação das threads escritoras
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // Espera o término de todas as threads
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
