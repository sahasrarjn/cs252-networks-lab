#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     256

int
main(int argc, char * argv[])
{
  struct sockaddr_in sin, cx;
  socklen_t cxlen = sizeof(cx);
  char buf[MAX_LINE];
  char *file_path = "recv.txt";
  int buf_len, addr_len;
  int sock, new_sock;
  int fp, lenn;
  ssize_t bytes_read;
  int reno_cubic = 0;
  
  if(argc != 2){
    fprintf(stderr, "usage: simplex-talk reno/cubic\n");
    exit(1);
  }

  char tcp_type[MAX_LINE];
  socklen_t len;

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);
  
 bzero((char*) &cx, sizeof(cx)); 

  /* setup passive open */
  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  // bzero(&servaddr, sizeof(servaddr));

  int opt=1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
      perror("setsockopt");
      exit(EXIT_FAILURE);
  }
  

  
  if(!strcmp(argv[1],"reno")){
      strcpy(buf, "reno");      
  }
  else if (!strcmp(argv[1],"cubic")){
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

  // printf("New: %s\n", buf);


  if ((bind(sock, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
  }
  
  if ((listen(sock, 5)) != 0) {
    perror("listen");
    exit(0);
  }
  
	
	
 /* wait for connection, then receive and print text */
  while(1) {
    if ((new_sock = accept(sock, (struct sockaddr *)&cx, &cxlen)) < 0) {
      perror("simplex-talk: accept");
      exit(1);
    }

    fp = open(file_path, 
                  O_WRONLY | O_CREAT | O_TRUNC, 
                  S_IRUSR | S_IWUSR);
    if(fp == -1){
      perror("simplex-talk: file-open");
      exit(1);
    }

    do {
      bytes_read = read(new_sock, buf, MAX_LINE); // check if sizeof(buf) works
      if(bytes_read == 1){
        perror("simplex-talk: read");
        exit(1);
      }

      if(write(fp, buf, bytes_read) == -1){
        perror("simplex-talk: write");
        exit(1);
      }
    } while(bytes_read > 0);

    close(fp);
    // while ((buf_len = recv(new_sock, buf, sizeof(buf), 0)))
    //   fputs(buf, stdout);
    close(new_sock);
   // close(sock);
  }
	close(sock);
  return 0;
}
