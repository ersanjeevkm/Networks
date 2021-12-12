#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
 
#define PORT 8080
   
int main()
{
    int sock_fd;
    struct sockaddr_in address;
    char buffer[1024], msg[1024];

    scanf("%s", msg);

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
       
    
    if (connect(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    write(sock_fd , msg , 1024);
    printf("Hello message sent\n");
    read(sock_fd , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}