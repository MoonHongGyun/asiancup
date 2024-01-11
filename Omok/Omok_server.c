#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define Clnt_MAX 2
#define BUF_SIZE 1024

void error_handling(char *messeage);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    int pos[4];
    int clnt_cnt = 0;
    int clnt_socks[Clnt_MAX];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 2) == -1)
        error_handling("listen() error");

    while (clnt_cnt < Clnt_MAX)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connect client %d \n", clnt_cnt + 1);
        clnt_socks[clnt_cnt] = clnt_sock;
        clnt_cnt++;
    }
    pos[2] = 1;
    write(clnt_socks[0], pos, sizeof(pos));
    pos[2] = 0;
    write(clnt_socks[1], pos, sizeof(pos));

    while (1)
    {
        read(clnt_socks[0], pos, sizeof(pos));
        pos[2] = 0;
        write(clnt_socks[1], pos, sizeof(pos));

        read(clnt_socks[1], pos, sizeof(pos));
        pos[2] = 1;
        write(clnt_socks[0], pos, sizeof(pos));
    }
    close(serv_sock);
    close(clnt_sock);
    return 0;
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}