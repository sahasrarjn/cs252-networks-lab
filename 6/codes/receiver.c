/*
This is the socket code for recevier (server) side of the TCP setup used for this assignment
TCP connection can be set for either reno or cubic (both available of linux systems)

Usage: 
gcc -o receiver receiver.c
./sender {reno|cubic}
*/


/* Headers */
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
#include <sys/time.h>
#include <sys/stat.h>

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     1500   // Max buffer size
struct stat st;             // file stat struct, used to get file size of the 

int
main(int argc, char * argv[])
{
  // Declarations
  struct sockaddr_in sin, cx;
  socklen_t cxlen = sizeof(cx);
  char buf[MAX_LINE];
  char *file_path = "recv.txt";
  int buf_len, addr_len;
  int sock, new_sock;
  int fp, lenn;
  ssize_t bytes_read;
  char tcp_type[MAX_LINE];
  socklen_t len;
  int reno_cubic = 0;
  struct timeval t0, t1;
  
  // Usage instrcutions
  if(argc != 2){
    fprintf(stderr, "usage: ./receiver {reno|cubic}\n");
    exit(1);
  }

  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);
  
  bzero((char*) &cx, sizeof(cx)); 

  /* setup active open */
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
  

  /* Bind to the SERVER_PORT */
  if ((bind(sock, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
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


  /* Listen (TCP connection) */
  if ((listen(sock, 5)) != 0) {
    perror("listen");
    exit(0);
  }
  
  /* Accept (TCP connection) */
  if((new_sock = accept(sock, (struct sockaddr *)&cx, &cxlen)) < 0) {
    perror("simplex-talk: accept");
    exit(1);
  }

  // open file with create, truncate, ... options 
  fp = open(file_path, 
                O_WRONLY | O_CREAT | O_TRUNC, 
                S_IRUSR | S_IWUSR);
  if(fp == -1){
    perror("simplex-talk: file-open");
    exit(1);
  }
	
 /* wait for connection, then receive and store data to the file */
  while(1) {

    gettimeofday(&t0,NULL); // start timer
    do {
      // Read data from the socket
      bytes_read = read(new_sock, buf, MAX_LINE); // check if sizeof(buf) works
      if(bytes_read == -1){
        perror("simplex-talk: read");
        exit(1);
      }

      // Write data to the file
      if(write(fp, buf, bytes_read) == -1){
        perror("simplex-talk: write");
        exit(1);
      }
    } while(bytes_read > 0);
    gettimeofday(&t1,NULL); // end timer

    if(bytes_read == 0){
      // Transfer complete
      break;
    }
    
  }

  /* Calculate throughput value for the flow */
  stat(file_path, &st);
  double filesize = st.st_size*8;
  double time = (t1.tv_usec-t0.tv_usec) + (t1.tv_sec-t0.tv_sec)*1000000;
  long long thput = filesize/time * 1000000;

  printf("%lld\n", thput);


  /* Close file and sockets */
  close(fp);
  close(new_sock);
	close(sock);
  return 0;
}
