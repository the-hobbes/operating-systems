# Link the pthread library by pass it as an arg to the compiler
all: target1 target2 target3 target4

target1:
	gcc -pthread -o detached 1_detached.c

target2:
	gcc -pthread -o thread_creation 2_thread_creation.c

target3:
	gcc -pthread -o thread_creation_argument 3_thread_creation_argument.c

target4:
	gcc -pthread -o thread_creation_corrected 4_thread_creation_corrected.c
