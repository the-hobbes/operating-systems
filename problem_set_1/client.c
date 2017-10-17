#include <stdio.h>
#include <stdlib.h>

char *SERVER_ADDRESS;
char *SERVER_PORT;


int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Two arguments: the server address, and the port\n");
    exit(1);
  }
  SERVER_ADDRESS = argv[1];
  SERVER_PORT = argv[2];

  //TODO: actual socket stuff
}
