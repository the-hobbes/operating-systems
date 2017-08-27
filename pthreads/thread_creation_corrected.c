#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void* threadFunc (void *pArg) {
  int *p = (int*)pArg;  // the address of i
  int myNum = *p;  // the value of i (the value at the address of i)
  printf("Thread number %d\n", myNum);
  return 0;
}

int main (void) {
  int tNum[NUM_THREADS];
  int i;
  pthread_t tid[NUM_THREADS];

  for (i = 0; i < NUM_THREADS; i++) { /* create and fork threads */
    tNum[i] = i;
    /* Fix the race condition here.

      Instead of passing in the value of the address of i to the threadFunc,
      instead we first copy the value into an element of an array tNum. We pass
      the address of the element in the array, creating a kind of private store
      for the value of each of the elements we create. Each thread has a private
      copy of the input element, that won't change (&tNum[i] will always be the
      value of whatever i was when the element was set).

      Remember that the order will still be dependent on how the threads are
      scheduled, but we wont get duplicate or omitted output now.
    */
    pthread_create(&tid[i], NULL, threadFunc, &tNum[i]);
  }
  for (i = 0; i < NUM_THREADS; i++) { /* wain/join threads */
    pthread_join(tid[i], NULL);
  }
  return 0;
}

