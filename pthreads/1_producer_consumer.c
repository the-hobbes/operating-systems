#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUF_SIZE 3 // size of shared buffer

int buffer[BUF_SIZE];  // the shared buffer
int add = 0;					 // an index representing where to add next element
int rem = 0;					 // an index representing where to remove next element
int num = 0;					 // the number of elements in the buffer

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;		// mutex lock for buffer
pthread_cond_t c_cons = PTHREAD_COND_INITIALIZER; // consumer waits on this condition var
pthread_cond_t c_prod = PTHREAD_COND_INITIALIZER; // producer waits on this cv

// two functions for producers and consumers respectively
void *producer (void *param);
void *consumer (void *param);

int main(int argc, char *argv[]) {
	
	pthread_t tid1, tid2; // thread identifiers
	int i;

	// the first thread executes the producer function
	if (pthread_create(&tid1, NULL, producer, NULL) != 0) {
		fprintf(stderr, "Unable to create producer thread\n");
		exit(1);
	}

	// the second thread executes the consumer function
	if (pthread_create(&tid1, NULL, consumer, NULL) != 0) {
		fprintf(stderr, "Unable to create consumer thread\n");
		exit(1);
	}

	// join the threads
	pthread_join(tid1, NULL); // wait for producer to exit
	pthread_join(tid2, NULL); // wait for consumer to exit
	printf("Parent quitting\n");
}

void *producer(void *param) {
	// During iteration, the producer thread tries create elements added to the shared
	// buffer. 
	int i;
	for (int i = 0; i <= 20; ++i) {
		pthread_mutex_lock(&m);  // start mutex lock
			if (num > BUF_SIZE) {
				// overflow? exit.
				exit(1);
			}
			while(num == BUF_SIZE) {
				// the buffer is full, so block until a consumer consumes some
				pthread_cond_wait(&c_prod, &m);
			}
			// change shared variable values, inside the mutex
			buffer[add] = i; // the buffer isn't full, so add an element
			add = (add+1) % BUF_SIZE;
			num++;
		pthread_mutex_unlock(&m);  // end mutex lock
		// signal the consumer that it can consume, if it is waiting (since we started 
		// with nothing in the buffer). signal to wake up only one consumer thread.
		pthread_cond_signal(&c_cons);
		printf("Producer: inserted %d\n", i);
		fflush(stdout);
	}
	printf("Producer quitting\n");
	fflush(stdout);
	return 0;
}

void *consumer(void *param) {
	int i;

	while(1) {  // infinitly, try to remove elements from the buffer...
		pthread_mutex_lock(&m);
			if (num < 0) {
				// underflow, buffer not initialized or something wierd happened
				exit(1);
			}
			while(num == 0) {
				// block if buffer is empty (producer will signal when there's an element)
				pthread_cond_wait(&c_cons, &m);
			}
			i = buffer[rem]; // buffer not empty, so remove an element
			// update which one to remove next, which is the current element + 1
			rem = (rem + 1) % BUF_SIZE;
			num--;  // decrease number of elements
		pthread_mutex_unlock(&m);
		// we always signal when we complete the consumption
		// signal the producer we've consumed an element, so there's room to produce more
		pthread_cond_signal(&c_cons);
		printf("Consume value %d\n", i);
		fflush(stdout);
	}
}
