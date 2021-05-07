#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#define MAX 1501*8
#define SA struct sockaddr



// Function designed for chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	char buff1[MAX];
	int n;
	// infinite loop for chat
	FILE * fp;    /* open the file for writing*/
	fp = fopen ("./recv.txt","w");
	bzero(buff1, MAX);
	struct timeval start_time;
	struct timeval end_time;
	gettimeofday(&start_time, NULL);	
	for (;;) {
		bzero(buff, MAX);
		// read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));
		if (strcmp(buff1, buff) == 0) {
			break;
		}
		// print buffer which contains the client contents
		//printf("%s", buff);
		fprintf(fp,"%s", buff);
		bzero(buff, MAX);
		n = 0;
		// copy server message in the buffer
		// while ((buff[n++] = getchar()) != '\n')
		// 	;

		// // and send that buffer to client
		// write(sockfd, buff, sizeof(buff));

		// // if msg contains "Exit" then server exit and chat ended.
		// if (strncmp("exit", buff, 4) == 0) {
		// 	printf("Server Exit...\n");
		// 	break;
		// }
	}
	gettimeofday(&end_time, NULL);
	// printf("%ld\n",start_time.tv_usec );
	// printf("%ld\n",end_time.tv_usec );
	float timetaken=(end_time.tv_sec-start_time.tv_sec)+(end_time.tv_usec-start_time.tv_usec)/1000000.0;
	printf("Throughput(in bits/sec): %f\n",40000000.0/timetaken);
	FILE * wr;    /* open the file for writing*/
	wr = fopen ("./data.txt","a");
	fprintf(wr, "%f\n", 40000000.0/timetaken);
}

// Driver function
int main(int argc, char* argv[])
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	int opt=1;
	int PORT=atoi(argv[2]);
	// socket create and verification
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
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	char buf[256];
    socklen_t lenn;
//            	strcpy(buf, "reno");
	if(!strcmp(argv[1],"reno")){
    	// printf("bopp\n");
    	strcpy(buf, "reno");			
	}
    else if (!strcmp(argv[1],"cubic")){
    	strcpy(buf, "cubic");
    }
    lenn = strlen(buf);
	if (setsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, lenn)!=0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    lenn = sizeof(buf);

    if (getsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buf, &lenn) != 0)
    {
        perror("getsockopt");
        return -1;
    }

    printf("New: %s\n", buf);
	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
