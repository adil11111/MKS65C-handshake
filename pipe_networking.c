#include "pipe_networking.h"


static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("Client Exited\n");
    remove("wkp");
    exit(0);
  }
}
/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int pipe=mkfifo("wkp", 0644);
  int fd;
  while (1) {
    fd = open("wkp", O_RDONLY);
    signal(SIGINT, sighandler);
    char * receiving = malloc(BUFFER_SIZE);
    read(fd, receiving, BUFFER_SIZE);
    printf("Client Says: %s", receiving);

    close(fd);
    
    fd = open("wkp", O_WRONLY);
    signal(SIGINT, sighandler);
    char sending[BUFFER_SIZE];
    strcpy(sending,"!.!");
    strcat(sending,receiving);
    //printf("%s\n",sending);
    write(fd, sending, BUFFER_SIZE);
    
    close(fd);
  }
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int pipe=mkfifo("wkp", 0644);
  int fd;
  while (1) {
    fd = open("wkp", O_WRONLY);
    
    char sending[BUFFER_SIZE];
    fgets(sending, BUFFER_SIZE, stdin);
    write(fd, sending, BUFFER_SIZE);
    
    close(fd);

    fd = open("wkp", O_RDONLY);
  
    char * receiving = malloc(BUFFER_SIZE);
    read(fd, receiving, BUFFER_SIZE);
    printf("Server Received Message: %s", receiving);

    close(fd);
  }
  return 0;
}

