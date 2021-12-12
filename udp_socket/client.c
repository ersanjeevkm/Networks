// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 5000
#define MAXLINE 1000

// Driver code
int main()
{
	char buffer[100];
	char message[100];
	int sockfd;
	struct sockaddr_in servaddr;
	
	// clear servaddr
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	
	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	// connect to server
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(0);
	}

	// request to send datagram
	// no need to specify server address in sendto
	// connect stores the peers IP and port

	while(1){
		scanf("%s", message);
		sendto(sockfd, message, MAXLINE, 0, NULL, NULL);
		
		if(strcmp(message, "exit") == 0)
			break;
		// waiting for response
		recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
		printf("%s\n", buffer);
	}
	// close the descriptor
	close(sockfd);
	return 0;
}
