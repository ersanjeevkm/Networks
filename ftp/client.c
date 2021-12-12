#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8090

int main()
{
    int sock_fd;
    char buffer[256];
    struct sockaddr_in address;

    /* Create a socket first */
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT); // port
    address.sin_addr.s_addr = INADDR_ANY;

    /* Attempt a connection */
    if(connect(sock_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    /* Create file where data will be stored */
    FILE *fp;
    fp = fopen("sample1.txt", "ab");
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    int bytes;
    /* Receive data in chunks of 256 bytes */
    while((bytes = read(sock_fd, buffer, 256)) > 0)
    {
        printf("Bytes received %d\n",bytes);    
        // buffer[n] = 0;
        fwrite(buffer, 1,bytes,fp);
        // printf("%s \n", buffer);q
    }

    if(bytes < 0)
    {
        printf("\n Read Error \n");
    }


    return 0;
}
