#include "pipe_networking.h"



static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("Client Exited\n");
    remove("wkp");
    exit(0);
  }
}
int main() {
  signal(SIGINT, sighandler);
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
}
