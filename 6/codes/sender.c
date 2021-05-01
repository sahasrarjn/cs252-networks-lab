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

#define SERVER_PORT 5432
#define MAX_LINE 256    // Check this for large files

int
main(int argc, char * argv[])
{
  int fp;
  struct hostent *hp;
  struct sockaddr_in sin;
  char *host;
  char *file_path = "send.txt";
  char buf[MAX_LINE];

  int reno_cubic = 0; // Change this to automate!!!! 1:reno, 0:cubic
  char tcp_type[MAX_LINE];

  struct timeval t0, t1;
  
  int sock; // sockfd
  int len;

  // open file
  fp = open(file_path, O_RDONLY);
  if(fp == -1){
    perror("sinplex-talk: file-open");
    exit(1);
  }

  if (argc==2) {
    host = argv[1];
  }
  else {
    fprintf(stderr, "usage: simplex-talk host\n");
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
  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }

  // select tcp
  if(reno_cubic == 1){
    strcpy(tcp_type, "reno");
  }else{
    strcpy(tcp_type, "cubic");
  }
  len = strlen(buf);

  if(setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0){
    perror("setsockopt");
    return -1;
  }


  if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
    perror("simplex-talk: connect");
    close(sock);
    exit(1);
  }


  while(1){
    int bytes_read = read(fp, buf, sizeof(buf));
    if(bytes_read == 0)
      break;

    if(bytes_read < 0){
      printf("simlpex-talk: no bytes read\n");
      exit(1);
    }


    gettimeofday(&t0,NULL);
    if (write(sock, buf, bytes_read) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    gettimeofday(&t1,NULL);

    printf("Time taken to transfer the file: %ld sec\n", t1.tv_sec-t0.tv_sec);

  }

  // free(host);
  close(fp);
  exit(EXIT_SUCCESS);
}








