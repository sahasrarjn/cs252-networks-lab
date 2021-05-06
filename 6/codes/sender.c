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
#define MAX_LINE 256    // Check this for large files
struct stat st;


int
main(int argc, char * argv[])
{
  int fp;
  struct hostent *hp;
  struct sockaddr_in sin;
  char *host;
  char *file_path = "send.txt";
  char buf[MAX_LINE];

  char tcp_type[MAX_LINE];

  struct timeval t0, t1;
  
  int sock; // sockfd
  socklen_t len;

  // open file
  fp = open(file_path, O_RDONLY);
  if(fp == -1){
    perror("sinplex-talk: file-open");
    exit(1);
  }

  if (argc==3) {
    host = argv[1];
  }
  else {
    fprintf(stderr, "usage: simplex-talk host isReno\n");
    exit(1);
  }

  int reno_cubic = 0; // Change this to automate!!!! 1:reno, 0:cubic


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
  int len2 = strlen(tcp_type);

  setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, tcp_type, len2);
  // if(setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, len) != 0){
  //   perror("setsockopt");
  //   return -1;
  // }


  if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
  {
    perror("simplex-talk: connect");
    close(sock);
    exit(1);
  }



  gettimeofday(&t0,NULL);
  while(1){
    int bytes_read = read(fp, buf, sizeof(buf));
    if(bytes_read == 0)
      break;

    if(bytes_read < 0){
      printf("simlpex-talk: no bytes read\n");
      exit(1);
    }


    if (write(sock, buf, bytes_read) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    
  }
  gettimeofday(&t1,NULL);

  stat(file_path, &st);
  double filesize = st.st_size*8;
  double time = (t1.tv_usec-t0.tv_usec)/1000000 + (t1.tv_sec-t0.tv_sec);
  //double time_sec = time_usec/1000000.0;


  printf("Throughput(bits/sec): \n%lf\n", filesize/time);

  // free(host);
  close(fp);
  close(sock);
  exit(EXIT_SUCCESS);
}







