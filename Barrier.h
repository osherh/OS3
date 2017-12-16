#ifndef BARRIER_H_
#define BARRIER_H_

#include <semaphore.h>

class Barrier {
public:
	Barrier(unsigned int num_of_threads);
	void wait();
	~Barrier();

protected:
    typedef struct pthread_barrier_waiting_node
    {
        struct pthread_barrier_waiting_node *next;
        kernel_pid_t pid;           //the currnent thread to wake up
        int cont;
    } pthread_barrier_waiting_node_t;

    typedef struct
    {
        struct pthread_barrier_waiting_node *next;      // list of waiting threads
        sem_t wait_for_threads_sem;
        sem_t critical_code_sem;
        int count;      //when count == #num_of_threads, wake up all threads
        unsigned int num_of_threads;
    } pthread_barrier_t;

};

#endif // BARRIER_H_

