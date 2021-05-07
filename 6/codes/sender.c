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
  int fp, lenn;
  struct hostent *hp;
  struct sockaddr_in sin;
  char *host;
  char *file_path = "send.txt";
  char buf[MAX_LINE];

  char tcp_type[MAX_LINE];
  
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
    fprintf(stderr, "usage: simplex-talk host reno/cubic\n");
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

  int opt=1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
      perror("setsockopt");
      exit(EXIT_FAILURE);
  }

  // select tcp
  if(!strcmp(argv[2],"reno")){
      strcpy(buf, "reno");      
  }
  else if (!strcmp(argv[2],"cubic")){
    strcpy(buf, "cubic");
  }
  lenn = strlen(buf);
  if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, lenn)!=0)
  {
      perror("setsockopt");
      exit(EXIT_FAILURE);
  }

  lenn = sizeof(buf);

  if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buf, &lenn) != 0)
  {
      perror("getsockopt");
      exit(1);
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

    // printf("%s\n", buf);


    if (write(sock, buf, bytes_read) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    
  }

  
  // free(host);
  close(fp);
  close(sock);
  exit(EXIT_SUCCESS);
}







