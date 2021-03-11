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

// Frame structure
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

    // reading CLI arguments
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

    // Socket binding
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){ 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&receiver, '\0', sizeof(receiver));
    memset(&sender, '\0', sizeof(sender));
    // Assigning port and inet address
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(receiverPort);
    receiver.sin_addr.s_addr = inet_addr("127.0.0.1");
    unsigned int size_rec = sizeof(receiver);

    // Few declerations for timer elements
    struct timeval tv;
    fd_set readfds;
    clock_t start, end;

    // While loop to send frames
    while(seqNo <= P){
        tv.tv_sec = RetransmissionTime;

        // Prepare frame
        send.seqNo = seqNo;
        send.ack = 0;
        strcpy(send.data, "Packet:");
        char sqn[100];
        
        sprintf(sqn, "%d", seqNo);
        strcat(send.data, sqn);
        
        int resend = 0;
        int temp_time = 0;

        // Send frame instructions
        send_frame:
            printf("%s\n", send.data);
            fprintf(fptr, "%s\n", send.data);
            start = clock();
            if(resend == 1){
                start = temp_time;
                tv.tv_sec = RetransmissionTime - start;
            }
            sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr*)&receiver, sizeof(receiver));
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
            int rec_size = recvfrom(sockfd, &rec, sizeof(rec), 0, (struct sockaddr*)&receiver, &size_rec);
            end = clock() - start + temp_time;

        if(rec_size > 0 && rec.ack == 1){
            if(rec.seqNo == seqNo+1){
                // Accept the ACK and send next packet
                seqNo++;
            }else{
                float timereq = (float)end/CLOCKS_PER_SEC;
                if(timereq > RetransmissionTime){
                    // Ignore the ACK
                    continue;
                }else{
                    // Invalid ACK, so program will send the frame again with the same timer
                    resend = 1;
                    temp_time = end;
                    goto send_frame;
                }
            }
        }else{
            // Timer Expired
            printf("Transmission Timer Expired\n");
            fprintf(fptr,"Transmission Timer Expired\n");
        }
    }

    // Closing the socket
    strcpy(send.data, "exit");
    sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr*)&receiver, sizeof(receiver));

    close(sockfd);
    fclose(fptr);
    return 0;
}
