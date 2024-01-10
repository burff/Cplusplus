#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printf("Usage:%s <port> <buffer_size>\n", argv[0]);
        exit(1);
    }

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    int recv_buf = atoi(argv[2]);
    int len = sizeof(recv_buf);

    setsockopt(serv_sock, SOL_SOCKET, SO_RCVBUF, &recv_buf, sizeof(recv_buf));
    getsockopt(serv_sock, SOL_SOCKET, SO_RCVBUF, &recv_buf, (socklen_t*)&len);
    printf("the tcp recv buffer after setting is %d\n", recv_buf);

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind error");
        exit(-1);
    }
 
    if(listen(serv_sock, 5) == -1)
    {
        perror("listen error");
        exit(-1);
    }

    struct sockaddr_in clnt_addr;
    socklen_t clnt_len = sizeof(clnt_addr);

    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_len);

    if(clnt_sock < 0)
    {
        printf("errno is: %d \n", errno);
    }
    else
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        while(recv(clnt_sock, buffer, BUFFER_SIZE-1, 0))
        {
        }
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}