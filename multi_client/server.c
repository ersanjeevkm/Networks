#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 8740
 
int main()
{
    int sock_fd, new_socket;
    struct sockaddr_in server_address, new_address;
    socklen_t serverLen = sizeof(server_address);
    socklen_t clientLen = sizeof(new_address);
    pid_t childpid;
   
    char msg[1024];

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    
    if (bind(sock_fd, (struct sockaddr *)&server_address, 
                                 sizeof(server_address))<0)
    { 
        perror("bind failed");
        return -1;
    }
    if (listen(sock_fd, 3) < 0)
    {
        perror("listen");
        return -1;
    }


    while(1)
    {
        new_socket = accept(sock_fd,(struct sockadddr*)&new_address,&clientLen);
        if(new_socket<0)
        {
            perror("Can't accept requests..\n");
            return 1;
        }
        printf("Connection accepted %d:%d\n",inet_ntoa(new_address.sin_addr),ntohs(new_address.sin_port));
        if((childpid=fork())==0)
        {
            close(sock_fd);
            while(1)
            {
                read(new_socket,msg,sizeof(msg));
                if(strcmp(msg,"exit")==0)
                {
                    printf("Client %d disconnected from server..\n",inet_ntoa(new_address.sin_addr));
                    return 1;
                }
                else
                {
                    printf("Client %d: %s\n",ntohs(new_address.sin_port),msg);
                    send(new_socket, msg, strlen(msg), 0);
                    bzero(msg,sizeof(msg));
                }
            }
        }
    }
    return 0;
}