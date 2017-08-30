#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void* threadFunc (void *pArg) {
  int *p = (int*)pArg;  // the address of i
  int myNum = *p;  // the value of i (the value at the address of i)
  
  /* The output of this printf statement will be non-determinitic!
    The value of i in pArg can be from 0-3, in any order, since we have no
    control over how the threads are scheduled.
    
    Values can even repeat, or be omitted. Why is this possible? Take for
    example an output of 0, 2, 2, 3.
    i is defined in main, and is globally visible. When its value changes in one
    thread, all other threads see the new value. 

    This means its possible for the loop in the main method to increase the
    value of i before it is set in the threadFunc, changing it from 1 to 2 for
    example from under threadFunc. The address of i stays the same, but the
    value that lives there won't.

    So it's not like we lost the value, but rather two threads see the value of
    i is 2.

    This is called a data race, or race condition, when a thread tries to read a
    value while another thread modifies it.

    See thread_creation_corrected.c for a solution to this.
  */
  printf("Thread number %d\n", myNum);
  return 0;
}

int main (void) {
  int i;
  pthread_t tid[NUM_THREADS];

  for (i = 0; i < NUM_THREADS; i++) {
    /* create and fork threads */
    pthread_create(&tid[i], NULL, threadFunc, &i);
  }
  for (i = 0; i < NUM_THREADS; i++) {
    /* wain/join threads */
    pthread_join(tid[i], NULL);
  }
  return 0;
}

