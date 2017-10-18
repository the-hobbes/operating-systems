#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>


char *SERVER_ADDRESS;
char *SERVER_PORT;


void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Two arguments: the server address, and the port\n");
    exit(1);
  }
  SERVER_ADDRESS = argv[1];
  SERVER_PORT = argv[2];

  int socket_fd;      // file descriptor for the socket
  int port_num;       // the port
  int return_value;   // the number of characters read/written

  struct sockaddr_in server_address;  // sockaddr_in defined in netinet/in.h

  port_num = atoi(SERVER_PORT);
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
        error("ERROR opening socket");
  }
  // initialize the address to all zeros
  memset((char *) &server_address, 0, sizeof(server_address));
  // set the fields in the sockaddr_in struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS); // INADDR_ANY;
  server_address.sin_port = htons(port_num); // converting to network byte order
  
  if (connect(
        socket_fd,
        (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    error("ERROR connecting");
  }
}
