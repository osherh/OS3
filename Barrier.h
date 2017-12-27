#ifndef BARRIER_H_
#define BARRIER_H_

#include <semaphore.h>
#include <pthread.h>

class Barrier {
public:
	Barrier(unsigned int num_of_threads);
	void wait();
	~Barrier();

protected:

        sem_t wait_for_threads_sem;
        sem_t protect_count_sem;        //protects the counter
        unsigned int barrier_waiting_threads;    //when equal #num_of_threads, wake up all threads
        unsigned int num_of_threads;

};

#endif // BARRIER_H_

