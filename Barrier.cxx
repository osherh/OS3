#include "Barrier.h"
#include <stdio.h>

Barrier::Barrier(unsigned int num_of_threads) {
    this->num_of_threads = num_of_threads;
    barrier_waiting_threads = 0;
    sem_init(&(wait_for_threads_sem), 0, num_of_threads);
    sem_init(&(protect_count_sem), 0, 1);
}

void Barrier::wait() {
    //wait for the counter
    sem_wait(&protect_count_sem);
    ++barrier_waiting_threads;
    sem_post(&protect_count_sem);
    while(barrier_waiting_threads != num_of_threads){
        sem_wait(&wait_for_threads_sem);
        barrier_waiting_threads++;
    }
    //we are the last thread
    // reset counter and free it
    //printf("Done\n");

    //free all of the other threads from their waiting.
    // post once for each waiting thread
    unsigned int i;
    for (i = 0; i < (num_of_threads - 1); i++) {
        sem_post(&wait_for_threads_sem);
        sem_wait(&protect_count_sem);
        --barrier_waiting_threads;
        sem_post(&protect_count_sem);
    }
}

Barrier::~Barrier() {
    sem_destroy(&wait_for_threads_sem);
    sem_destroy(&protect_count_sem);
}
