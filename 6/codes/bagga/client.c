#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX 1501*8
#define SA struct sockaddr

char terminate[]="exit";
void func(int sockfd)
{
	char buff[MAX];
	int n;
	FILE * fp;
    /* open the file for writing*/
    fp = fopen ("./send.txt","r");
	// for (;;) {
	// 	bzero(buff, sizeof(buff));
	// 	printf("Enter the string : ");
	// 	n = 0;
	// 	while ((buff[n++] = getchar()) != '\n')
	// 		;
	// 	write(sockfd, buff, sizeof(buff));
	// 	bzero(buff, sizeof(buff));
	// 	read(sockfd, buff, sizeof(buff));
	// 	printf("From Server : %s", buff);
	// 	if ((strncmp(buff, "exit", 4)) == 0) {
	// 		printf("Client Exit...\n");
	// 		break;
	// 	}
	// }
    //int v=2;
	while (1) {
    // Read data into buffer.  We may not have enough to fill up buffer, so we
    // store how many bytes were actually read in bytes_read.
    int bytes_read = fread(&buff, sizeof(char), sizeof(buff),fp);
    //fgets(buff, sizeof(buff), (FILE*)fp);
    //int bytes_read=sizeof(buff);
    if (bytes_read == 0){ // We're done reading from the file
        break;
    }
    
    if (bytes_read < 0) {
        // handle errors
    }
    //printf("%s",buff);
    
    // You need a loop for the write, because not all of the data may be written
    // in one call; write will return how many bytes were written. p keeps
    // track of where in the buffer we are, while we decrement bytes_read
    // to keep track of how many bytes are left to write.
    void *p = buff;
    while (bytes_read > 0) {
        int bytes_written = write(sockfd, p, bytes_read);
        if (bytes_written <= 0) {
            // handle errors
        }
        bytes_read -= bytes_written;
        p += bytes_written;
    }
}
}

int main(int argc, char* argv[])
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	int PORT=atoi(argv[2]);
	// socket create and varification
	int opt=1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	char buf[256];
    socklen_t len;
	if(!strcmp(argv[1],"reno")){
    	// printf("bopp\n");
    	strcpy(buf, "reno");			
	}
    else if (!strcmp(argv[1],"cubic")){
    	strcpy(buf, "cubic");
    }
    len = strlen(buf);
    
	if (setsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, len)!=0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    len = sizeof(buf);

    if (getsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, &len) != 0)
    {
        perror("getsockopt");
        return -1;
    }

    printf("New: %s\n", buf);
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
