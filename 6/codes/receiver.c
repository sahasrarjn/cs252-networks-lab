#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define SERVER_PORT  5432
#define MAX_PENDING  5
#define MAX_LINE     256

int
main()
{
  struct sockaddr_in sin;
  char buf[MAX_LINE];
  char *file_path = "recv.txt";
  int buf_len, addr_len;
  int s, new_s;
  ssize_t bytes_read;


  /* build address data structure */
  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(SERVER_PORT);

  /* setup passive open */
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("simplex-talk: socket");
    exit(1);
  }
  if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
    perror("simplex-talk: bind");
    exit(1);
  }
  listen(s, MAX_PENDING);

 /* wait for connection, then receive and print text */
  while(1) {
    if ((new_s = accept(s, (struct sockaddr *)&sin, &addr_len)) < 0) {
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
      bytes_read = read(new_s, buf, MAX_LINE); // check if sizeof(buf) works
      if(bytes_read == 1){
        perror("simplex-talk: read")
        exit(1);
      }

      if(write(fp, buf, bytes_read) == -1){
        perror("simplex-talk: write");
        exit(1);
      }
    } while(bytes_read > 0)

    close(fp);
    // while ((buf_len = recv(new_s, buf, sizeof(buf), 0)))
    //   fputs(buf, stdout);
    close(new_s);
  }
  return 0;
}







