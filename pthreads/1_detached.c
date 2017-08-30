/* PThread detached thread creation */

#include <stdio.h>
#include <pthread.h>

void* foo (void *arg) { /* thread main */
  /* View the output by attaching strace to the binary when you run it */
  printf("Foobar!\n");
  pthread_exit(NULL);
}

int main (void) {
  printf("Got to main!\n");

  int i;
  pthread_t tid;

  /* Create an initialize an attribute object */
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  /* When the thread is created, create it detached */
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  /* Scheduling scope is system, to share resources w/others in the system */  
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  /* Make the thread */
  pthread_create(&tid, &attr, foo, NULL);

  return 0;
}

