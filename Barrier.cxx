#include "Barrier.h"

Barrier::Barrier(unsigned int num_of_threads) {
    pthread_barrier_t* barrier = new pthread_barrier_t();
    barrier->num_of_threads = num_of_threads;
    barrier->count = 0;
    sem_init(&(barrier->wait_for_threads_sem), 0, num_of_threads);
    sem_init(&(barrier->critical_code_sem), 0, 1);
}

void Barrier::wait() {
//    while (1) {
//        sem_wait(&wait_for_threads_sem);
//        sem_post(&wait_for_threads_sem);
//       sleep(1);
//     }
}

Barrier::~Barrier() {
    sem_destroy(&wait_for_threads_sem);
}

//Semaphore *sem = check_malloc(sizeof(Semaphore));
//int n = sem_init(sem, 0, value);
// if (n != 0) perror_exit("sem_init failed");
// return sem;