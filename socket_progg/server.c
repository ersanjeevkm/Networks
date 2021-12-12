#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080

int main()
{
    int sock_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024], msg[1024];
    scanf("%s", msg);
    
    // Creating socket file descriptor
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        return -1;
    }
       
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
       
    // Forcefully attaching socket to the port 8080
    if (bind(sock_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    { 
        perror("bind failed");
        return -1;
    }
    if (listen(sock_fd, 3) < 0)
    {
        perror("listen");
        return -1;
    }
    if ((new_socket = accept(sock_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        return -1;
    }
    
    read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    write(new_socket , msg , 1024);
    printf("Hello message sent\n");
    return 0;
}