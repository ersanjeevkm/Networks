// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#define PORT 5000
#define MAXLINE 1000
// Driver code
int main()
{
	char buffer[100];
	char message[100];
	int sock_fd;
	struct sockaddr_in servaddr, cliaddr;

    int addrlen = sizeof(cliaddr);

	// Create a UDP Socket
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);		

	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// bind server address to socket descriptor
	bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	//receive the datagram

	while(1){
	
		recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, (socklen_t*)&addrlen);

		if(strcmp(buffer, "exit") == 0)
			break;
		printf("%s\n", buffer);
		
		scanf("%s", message);
		// send the response
		sendto(sock_fd, message, MAXLINE, 0, (struct sockaddr*)&cliaddr, addrlen);
	}
    close(sock_fd);
	
    return 0;
}
