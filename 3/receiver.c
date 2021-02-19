#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// Frame structure
struct frame{
	int ack;
    int seqNo;
    char data[1024];
};

int main(int argc, char *argv[]){

	if (argc != 4){
		printf("Usage: receiver.c <ReceiverPort> <SenderPort> <PacketDropProbability>");
		exit(0);	
	}

	FILE *fptr;
	fptr = fopen("receiver.txt","w");

    // reading CLI arguments
	int ReceiverPort = atoi(argv[1]);
	int SenderPort = atoi(argv[2]);
	float dropProb;
	sscanf(argv[3],"%f",&dropProb);
	int sockfd;
	struct sockaddr_in receiver, sender;
	char buffer[1024];
	socklen_t socket_size;

	struct frame rec, send;	

    // Socket binding
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
	
	memset(&receiver, '\0', sizeof(receiver));
	memset(&sender, '\0', sizeof(sender));
	receiver.sin_family = AF_INET;
	receiver.sin_port = htons(ReceiverPort);
	receiver.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sockfd, (struct sockaddr*)&receiver, sizeof(receiver)) < 0){
		perror("bind failure");
		exit(EXIT_FAILURE);
	}
	socket_size = sizeof(sender);

	srand(time(0));
	int seqNo=1; // First packet should have seq no = 1

    // While loop to read frames
	while(1){
		int rec_size = recvfrom(sockfd, &rec, sizeof(rec), 0, (struct sockaddr*)&sender, &socket_size);

		if(strcmp("exit", rec.data)==0){
			// Stop the receiver (exit code)
			break;
		}

		// Check the received data
		if (rec_size > 0 && seqNo == rec.seqNo && rec.ack == 0){
			if(seqNo == rec.seqNo){
				printf("%s\n", rec.data);
				fprintf(fptr, "%s\n", rec.data);

				float random = (float)rand()/RAND_MAX;
				if(random < dropProb){
					// No ACK generated
					printf("Frame dropped\n");
					fprintf(fptr, "Frame dropped\n");
					continue;
				}else{
					// Generate ACK
					send.seqNo = rec.seqNo+1;
					send.ack = 1;
					strcpy(send.data, "Acknowledgment:");
					char sqn[100];

					sprintf(sqn, "%d", send.seqNo);
					strcat(send.data, sqn);

					sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr*)&sender, socket_size);
					printf("%s\n", send.data);
					fprintf(fptr, "%s\n", send.data);
					seqNo++;
				}
			}else{
				// Incorrect seq no
				send.seqNo = seqNo+1;
				send.ack = 1;
				strcpy(send.data, "Acknowledgment:");
				char sqn[100];
				
				sprintf(sqn, "%d", send.seqNo);
				strcat(send.data, sqn);

				sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr*)&sender, socket_size);
				printf("%s\n", send.data);
				fprintf(fptr, "%s\n", send.data);
			}
		
		}else{
			printf("Frame Not Received\n");
			fprintf(fptr, "Frame Not Received\n");
		}
	}

	close(sockfd);
	fclose(fptr);
	return 0;
}
