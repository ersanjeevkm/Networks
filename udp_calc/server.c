// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#define PORT 6000
#define MAXLINE 1000

int main()
{
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
		
		int operator, op1, op2, result;
		char o1[100], o2[100], o3[100];

		recvfrom(sock_fd, o1, sizeof(o1), 0, (struct sockaddr*)&cliaddr, (socklen_t*)&addrlen);
		recvfrom(sock_fd, o2, sizeof(o2), 0, (struct sockaddr*)&cliaddr, (socklen_t*)&addrlen);
		recvfrom(sock_fd, o3, sizeof(o3), 0, (struct sockaddr*)&cliaddr, (socklen_t*)&addrlen);

		operator = atoi(o1);
		op1 = atoi(o2);
		op2 = atoi(o3);

		switch(operator) {
            case 1: result=op1 + op2;
                    printf("Result is: %d + %d = %d\n",op1, op2, result);
                    break;
            case 2: result=op1 - op2;
                    printf("Result is: %d - %d = %d\n",op1, op2, result);
                    break;
            case 3: result=op1 * op2;
                    printf("Result is: %d * %d = %d\n",op1, op2, result);
                    break;
            case 4: result=op1 / op2;
                    printf("Result is: %d / %d = %d\n",op1, op2, result);
                    break;
			case 5:
					return 0;
            default: 
                    printf("ERROR: Unsupported Operation");
    	}	

		char res[100];
		sprintf(res, "%d", result);
		sendto(sock_fd, res, MAXLINE, 0, (struct sockaddr*)&cliaddr, addrlen);
	}

    close(sock_fd);
	
    return 0;
}
