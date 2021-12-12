#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 5760

int main()
{
    int sock_fd;
    struct sockaddr_in address;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
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

    printf("connect sucessful\n");

    int operator, op1, op2, result;
    
    printf("Enter operation:\n 1:Addition \n 2: Subtraction \n 3: Multiplication \n 4: Divison \n");
    scanf("%d", &operator);
    printf("Enter operands:\n");
    scanf("%d%d", &op1, &op2);

    write(sock_fd, &operator, sizeof(operator));
    write(sock_fd, &op1, sizeof(op1));
    write(sock_fd, &op2, sizeof(op2));

    read(sock_fd, &result, sizeof(result));

    printf("Operation result from server = %d\n", result);
    close(sock_fd);
    return 0;
}