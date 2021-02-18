#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>


int main(){
    srand(time(0));
    int a = 20;
    while(a--){
        printf("%f \n", (float)(rand())/(float)(RAND_MAX));
    }
}