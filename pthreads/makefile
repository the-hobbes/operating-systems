# Link the pthread library by pass it as an arg to the compiler
all: target1 target2

target1:
	gcc -pthread -o pthread_detached detached.c

target2:
	gcc -pthread -o thread_creation thread_creation.c