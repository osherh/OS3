#include "Barrier.h"

Barrier::Barrier(unsigned int num_of_threads) {
    thread_barrier* barrier = new thread_barrier();
    barrier->num_of_threads = num_of_threads;
    barrier->barrier_waiting_threads = 0;
    sem_init(&(barrier->wait_for_threads_sem), 0, num_of_threads);
    sem_init(&(barrier->protect_count_sem), 0, 1);
}

void Barrier::wait() {
    //wait for the counter
    sem_wait(&protect_count_sem);
    if(barrier_waiting_threads != num_of_threads - 1){
        ++barrier_waiting_threads;
        //releases it
        sem_wait(&wait_for_threads_sem);
        //TODO add currnet thread to waiting threads list
    } else{  //we are the last thread
        // reset counter and free it
        barrier_waiting_threads = 0;
        //free all of the other threads from their waiting.
        //TODO: empty waiting threads list
        // post once for each waiting thread
        int i;
        for (i = 0; i < (num_threads - 1); i++) {
            sem_post(&barrier_sem);
            --barrier_waiting_threads;
        }
    }
    sem_post(&protect_count_sem);
}

Barrier::~Barrier() {
    sem_destroy(&wait_for_threads_sem);
    sem_destroy(&protect_count_sem);
    delete barrier;
}

//Semaphore *sem = check_malloc(sizeof(Semaphore));
//int n = sem_init(sem, 0, value);
// if (n != 0) perror_exit("sem_init failed");
// return sem;