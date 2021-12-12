#include<stdio.h>
#include <unistd.h>
#include<string.h> 

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> 
#include <arpa/inet.h>
#define PORT 5760

int main()
{
    int sock_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        return -1;
    }      

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    if (bind(sock_fd, (struct sockaddr *)&address, sizeof(address))<0)
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

    int operator, op1, op2, result;

    read(new_socket, &operator, sizeof(operator));
    read(new_socket, &op1, sizeof(op1));
    read(new_socket, &op2, sizeof(op2));

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
            default: 
                    printf("ERROR: Unsupported Operation");
    }
    
    write(new_socket, &result, sizeof(result));   
    close(sock_fd);
    return 0;
}