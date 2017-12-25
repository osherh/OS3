#ifndef BARRIER_H_
#define BARRIER_H_

#include <semaphore.h>

class Barrier {
public:
	Barrier(unsigned int num_of_threads);
	void wait();
	~Barrier();

protected:
    typedef struct pthread_barrier_waiting_node {
        struct pthread_barrier_waiting_node *next;
        unsigned int pid;           //the current thread to wake up
        int cont;
    } thread_barrier_waiting_node;

    typedef struct {
        struct pthread_barrier_waiting_node *waiting_threads;      // list of waiting threads
        sem_t wait_for_threads_sem;
        sem_t protect_count_sem;        //protects the counter
        int barrier_waiting_threads;    //when equal #num_of_threads, wake up all threads
        unsigned int num_of_threads;
    } thread_barrier;
};

#endif // BARRIER_H_

