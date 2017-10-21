#include <ctype.h>        // toupper()
#include <stdio.h>        // input and output
#include <stdlib.h>       // things like exit()
#include <sys/types.h>    // data types used in system calls
#include <string.h>       // for memset
#include <sys/socket.h>   // definitions of structures needed for sockets
#include <netinet/in.h>   // for internet domain addresses
#include <unistd.h>       // read/write syscalls

void error(char *msg) {
    // when things go bad...
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // we don't use error here, since perror uses the value of errno, which is
    // set based on the status of the last system call. That's useful for socket
    // stuff, but not here since we aren't doing a syscall.
    printf("No socket provided\n");
    exit(1);
  }
  
  int enable_address_reuse;
  int return_value; // number of characters read/written over the socket
  int socket_fd;
  int client_socket_fd;
  int port_number;
  int client_address_length;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char buffer[256];  // a place for the server to put characters read in

  // make the socket
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);  // domain,type,protocol
  if (socket_fd < 0) {
    error("Error opening up the socket\n");
  }
  // waiting 2 minutes for TCP to release the port sucks, so release it
  enable_address_reuse = 1;
  if (setsockopt(socket_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR,
                 &enable_address_reuse,
                 sizeof(int)) < 0) {
    error("setsockopt(SO_REUSEADDR) failed");
  }
  port_number = atoi(argv[1]);
  // set fields in internet address struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port_number);
  // use the bind syscall to bind the socket to the address (host:port)
  if (bind(
        socket_fd,
        (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
    error("Binding error occurred\n");
  }
  // listen syscall; socket file descriptor, # of waiting connections
  listen(socket_fd, 2);
  // accept syscall blocks current thread until a client connects to the server
  client_address_length = sizeof(client_address);
  client_socket_fd = accept(socket_fd, // socket of server
                            // pointer to the address of the client on the other
                            // end of the connection
                            (struct sockaddr *) &client_address,
                            // size of the client address
                            &client_address_length);
  memset(buffer, 0, 256);  // initialize buffer to 0's
  // read system call reads data from the socket into the buffer. read() will
  // block until there is something to read in the socket. 
  return_value = read(client_socket_fd, buffer, 255);
  if (return_value < 0) {
    error("Problem reading from the socket\n");
  }
  char output[return_value];
  int i = 0;
  while(buffer[i]) {
    output[i] = toupper(buffer[i]);
    i++;
  }
  printf("%s\n", output);
 return 0; 
}

