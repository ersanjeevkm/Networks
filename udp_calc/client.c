// udp client driver program
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 6000
#define MAXLINE 1000

// Driver code
int main()
{

	int sockfd;
	struct sockaddr_in servaddr;

	// clear servaddr
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// connect to server
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(0);
	}

	// request to send datagram
	// no need to specify server address in sendto
	// connect stores the peers IP and port

	while (1)
	{
		char o1[100], o2[100], o3[100];

		printf("Enter operation:\n 1:Addition \n 2: Subtraction \n 3: Multiplication \n 4: Divison \n 5: Exit\n");
		scanf("%s", &o1);
		printf("Enter operands:\n");
		scanf("%s", &o2);
		scanf("%s", &o3);


		sendto(sockfd, o1, MAXLINE, 0, NULL, NULL);
		sendto(sockfd, o2, MAXLINE, 0, NULL, NULL);
		sendto(sockfd, o3, MAXLINE, 0, NULL, NULL);

		if(atoi(o1) == 5)
			return 0;

		char result[100];
		recvfrom(sockfd, result, sizeof(result), 0, NULL, NULL);
		printf("RESULT: %s\n", result);
	}
	// close the descriptor
	close(sockfd);
	return 0;
}
