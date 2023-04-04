#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

#define SHARED_MEM_NAME "/shmem"
#define SEM_PRODUCER_NAME "/sem_producer"
#define SEM_CONSUMER_NAME "/sem_consumer"
#define SEM_MUTEX_NAME "/sem_mutex"
#define BUFFER_SIZE 2

struct SharedBuffer {
    int buffer[BUFFER_SIZE];
    int index;
};

void *produce(void *param) {
    int item;
    sem_t *semProducer = sem_open(SEM_PRODUCER_NAME, 0);
    sem_t *semConsumer = sem_open(SEM_CONSUMER_NAME, 0);
    sem_t *semMutex = sem_open(SEM_MUTEX_NAME, 0);
    SharedBuffer *sharedBuffer = (SharedBuffer *)param;

    for (int i = 0; i < 10; ++i) {
        item = i;
        sem_wait(semProducer);
        sem_wait(semMutex);

        sharedBuffer->buffer[sharedBuffer->index++] = item;
        std::cout << "Produced: " << item << std::endl;

        sem_post(semMutex);
        sem_post(semConsumer);
        sleep(1);
    }

    sem_close(semProducer);
    sem_close(semConsumer);
    sem_close(semMutex);

    pthread_exit(0);
}

int main() {
    pthread_t producerThread;
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error opening shared memory");
        exit(1);
    }
    ftruncate(shm_fd, sizeof(SharedBuffer));
    SharedBuffer *sharedBuffer = (SharedBuffer *)mmap(0, sizeof(SharedBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_unlink(SEM_PRODUCER_NAME);
    sem_unlink(SEM_CONSUMER_NAME);
    sem_unlink(SEM_MUTEX_NAME);

    sem_t *semProducer = sem_open(SEM_PRODUCER_NAME, O_CREAT, 0666, BUFFER_SIZE);
    sem_t *semConsumer = sem_open(SEM_CONSUMER_NAME, O_CREAT, 0666, 0);
    sem_t *semMutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0666, 1);

    sharedBuffer->index = 0;
    pthread_create(&producerThread, NULL, produce, (void *)sharedBuffer);

    pthread_join(producerThread, NULL);

    sem_close(semProducer);
    sem_close(semConsumer);
    sem_close(semMutex);
    munmap(sharedBuffer, sizeof(SharedBuffer));
    shm_unlink(SHARED_MEM_NAME);

    return 0;
}
