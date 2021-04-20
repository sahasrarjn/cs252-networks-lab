#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int main(int argc, char const *argv[])
{
	FILE *input_file;
	input_file = open("send.txt", O_RDONLY);
    if (input_file == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

	char buffer[256];
	int i=0;
	// while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
	while (i<30){
		// printf("%d\n", fgets(buffer, sizeof(buffer), input_file));
	    // Read data into buffer.  We may not have enough to fill up buffer, so we
	    // store how many bytes were actually read in bytes_read.
	    i++;
	    int bytes_read = read(input_file, buffer, sizeof(buffer));
	    if (bytes_read == 0) // We're done reading from the file
	        break;
	    
	    if (bytes_read < 0) {
	    	printf("No bytes read\n");
	    	exit(1);
	        // handle errors
	    }
	    
	    // You need a loop for the write, because not all of the data may be written
	    // in one call; write will return how many bytes were written. p keeps
	    // track of where in the buffer we are, while we decrement bytes_read
	    // to keep track of how many bytes are left to write.
	    void *p = buffer;
	    printf("%s\n", p);
	    // while (bytes_read > 0) {
	    //     // int bytes_written = write(output_socket, p, bytes_read);
	    //     printf("%d\n",bytes_read);
	    //     // if (bytes_written <= 0) {
	    //     //     // handle errors
	    //     // }
	    //     // bytes_read -= bytes_written;
	    //     // p += bytes_written;
	    // }
	}
	return 0;
}