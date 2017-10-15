#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
  Write a multi-threaded C program that gives readers priority over writers
  concerning a shared (global) variable. Essentially, if any readers are
  waiting, then they have priority over writer threads -- writers can only
  write when there are no readers. The program must adhere to the following
  constraints:
  - Multiple readers/writers must be supported (5 of each is fine)
  - Readers must read the shared variable X number of times
  - Writers must write the shared variable X number of times
  - Readers must print:
    - The value read
    - The number of readers present when value is read
  - Writers must print:
    - The written value
    - The number of readers present were when value is written (should be 0)
  - Before a reader/writer attempts to access the shared variable it should wait
    some random amount of time
  - Use pthreads, mutexes, and condition variables to synchronize access to the
    shared variable
*/

#define NUM_THREADS 5
int SHARED_VARIABLE = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t write_ok = PTHREAD_COND_INITIALIZER;
pthread_cond_t read_ok = PTHREAD_COND_INITIALIZER;

void *writer (void *param);
void *reader (void *param);

int main (void) {
  int i;
  pthread_t writer_threads[NUM_THREADS];
  pthread_t reader_threads[NUM_THREADS];
  
  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&writer_threads[i], NULL, writer, NULL) != 0) {
      fprintf(stderr, "Unable to create writer thread\n");
    }
    if(pthread_create(&reader_threads[i], NULL, reader, NULL) != 0) {
      fprintf(stderr, "Unable to create reader thread\n");
    }
  }

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(writer_threads[i], NULL);
    pthread_join(reader_threads[i], NULL);
  }
  fprintf(stdout, "Parent thread quitting\n");
  return 0;
}

void *writer (void *param) {
  return 0;
}

void *reader (void *param) {
  return 0;
}
