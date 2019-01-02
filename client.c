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
  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
}
