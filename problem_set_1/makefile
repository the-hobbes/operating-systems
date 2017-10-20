# Link the pthread library by pass it as an arg to the compiler
# make && ./priority
all: target1 target2 target3 target4 target5

target1:
				gcc -pthread -o priority priority.c

target2:
				gcc -pthread -o client client.c

target3:
				gcc -pthread -o server server.c

target4:
				gcc -pthread -o echo_client echo_client.c

target5:
				gcc -pthread -o echo_server echo_server.c