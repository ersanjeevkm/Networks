#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define PORT 8090
int main()
{
    int sock_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(sock_fd, (struct sockaddr *)&address, sizeof(address));

    if (listen(sock_fd, 3) < 0)
    {
        printf("Failed to listen\n");
        return -1;
    }

    new_socket = accept(sock_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    FILE *fp = fopen("sample.txt", "rb");
    if (fp == NULL)
    {
        printf("File opern error");
        return 1;
    }

    while (1)
    {
        /* First read file in chunks of 256 bytes */
        unsigned char buff[256] = {0};
        int nread = fread(buff, 1, 256, fp);
        printf("Bytes read %d \n", nread);

        if (nread > 0)
        {
            printf("Sending \n");
            write(new_socket, buff, nread);
        }

        if (nread < 256)
        {
            if (feof(fp))
                printf("End of file\n");
            if (ferror(fp))
                printf("Error reading\n");
            break;
        }
    }

    close(new_socket);

    return 0;
}