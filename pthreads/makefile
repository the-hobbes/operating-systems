# Link the pthread library by pass it as an arg to the compiler
all: target1 target2 target3 target4

target1:
	gcc -pthread -o detached detached.c

target2:
	gcc -pthread -o thread_creation thread_creation.c

target3:
	gcc -pthread -o thread_creation_argument thread_creation_argument.c

target4:
	gcc -pthread -o thread_creation_corrected thread_creation_corrected.c