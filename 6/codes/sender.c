/*
This is the socket code for sender (client) side of the TCP setup used for this assignment
TCP connection can be set for either reno or cubic (both available of linux systems)

Usage: 
gcc -o sender sender.c
./sender {reno|cubic}

Must run this after starting the receiver (server) side or else it will show connection issue
*/


/* Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <sys/stat.h>


#define SERVER_PORT 5432
#define MAX_LINE 1500     // Max buffer size


int
main(int argc, char * argv[])
{
  // Declarations
  int fp, lenn;
  struct hostent *hp;
  struct sockaddr_in sin;
  char *host;
  char *file_path = "send.txt";
  char buf[MAX_LINE];
  char tcp_type[MAX_LINE];
  int sock;
  socklen_t len;
  host = "0.0.0.0";

  // open file
  fp = open(file_path, O_RDONLY);
  if(fp == -1){
    perror("sinplex-talk: file-open");
    exit(1);
  }

  // Usage instrcutions
  if (argc!=2) {
    fprintf(stderr, "usage: ./sender {reno|cubic}\n");
    exit(1);
  }


  /* translate host name into peer's IP address */
  hp = gethostbyname(host);
  if (!hp) {
    fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
    exit(1);
  }

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
  sin.sin_port = htons(SERVER_PORT);

  /* active open */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }

  /* Set socker option to reuse address and port again */
  int opt=1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
      perror("setsockopt");
      exit(EXIT_FAILURE);
  }

  // select tcp type, reno or cubic
  if(!strcmp(argv[1],"reno")){
      strcpy(buf, "reno");      
  }
  else if (!strcmp(argv[1],"cubic")){
    strcpy(buf, "cubic");
  }
  lenn = strlen(buf);

  // Set TCP type = {reno|cubic}
  if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, lenn)!=0)
  {
      perror("setsockopt");
      exit(EXIT_FAILURE);
  }



  /* Setup connection with the server */
  if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
    perror("simplex-talk: connect");
    close(sock);
    exit(1);
  }


  /* Send file content */
  while(1){
    // Read file contents
    int bytes_read = read(fp, buf, sizeof(buf));
    if(bytes_read == 0){
      // nothing left to send
      break;
    }

    if(bytes_read < 0){
      // Byte error
      printf("simlpex-talk: no bytes read\n");
      exit(1);
    }

    // Write to receiver socket
    if (write(sock, buf, bytes_read) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    
  }

  
  // Close file and socket
  close(fp);
  close(sock);
  exit(EXIT_SUCCESS);
}







