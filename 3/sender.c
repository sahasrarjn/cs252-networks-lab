#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


struct frame{
    int ack;
    int seqNo;
    char data[1024];
};

int main(int argc, char **argv){
    if (argc != 5){
        printf("Usage: sender.c <SenderPort> <ReceiverPort> <RetransmissionTimer> <NoOfPacketsToBeSent>");
        exit(0);
    }

    FILE *fptr;
    fptr = fopen("sender.txt", "w");

    int senderPort = atoi(argv[1]);
    int receiverPort = atoi(argv[2]);
    int RetransmissionTime = atoi(argv[3]);
    int P = atoi(argv[4]);

    int sockfd;
    struct sockaddr_in sender, receiver;
    socklen_t SocketSize;
    char buffer[1024];

    int seqNo=1;
    struct frame send, rec;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&receiver, '\0', sizeof(receiver));
    memset(&sender, '\0', sizeof(sender));
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(receiverPort);
    receiver.sin_addr.s_addr = inet_addr("127.0.0.1");
    unsigned int size_rec = sizeof(receiver);

    struct timeval tv;
    fd_set readfds;
    tv.tv_usec = RetransmissionTime;

    while(seqNo <= P){

        // Prepare frame
        send.seqNo = seqNo;
        send.ack = 0;
        strcpy(send.data, "Packet:");
        char sqn[100];

        // ---- here ---- 
        sprintf(sqn, "%d", seqNo);
        strcat(send.data, sqn);
        // ---- here ---- 

        printf("%s\n", send.data);
        fprintf(fptr, "%s\n", send.data);
        sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr*)&receiver, sizeof(receiver));
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
        int rec_size = recvfrom(sockfd, &rec, sizeof(rec), 0, (struct sockaddr*)&receiver, &size_rec);
        
        if(rec_size > 0 && rec.ack == 1 && rec.seqNo == seqNo+1){
            printf("%s\n", rec.data);
            fprintf(fptr, "%s\n", rec.data);
            seqNo++;
        }else{
            printf("Transmission Timer Expired\n");
            fprintf(fptr,"Transmission Timer Expired\n");
        }
    }

    strcpy(send.data, "exit");
    sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr*)&receiver, sizeof(receiver));

    close(sockfd);
    fclose(fptr);
    return 0;
}
