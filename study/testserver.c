#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 10000
#define BUF_SIZE 1024

void error_handling(char *messeage);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;
    char message1[BUF_SIZE];
    char message2[BUF_SIZE];
    char message3[BUF_SIZE];
    int str_len;
    char *arr[3];
    int i = 0;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    argc = 2;
    argv[1] = "10000";

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
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        error_handling("accept() error");
    else
        printf("Connect client \n");

    str_len = recv(clnt_sock, message1, BUF_SIZE, 0);
    message1[str_len] = 0;
    arr[0] = message1;

    str_len = recv(clnt_sock, message2, BUF_SIZE, 0);
    message2[str_len] = 0;
    arr[1] = message2;

    str_len = recv(clnt_sock, message3, BUF_SIZE, 0);
    message3[str_len] = 0;
    arr[2] = message3;

    for (int j = 0; j < 3; j++)
    {
        printf("%s\n", arr[j]);
    }

    FILE *fp = fopen("save", "rt");
    char buffer[10000];
    char item[10000];
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        strcat(item, buffer);
    close(fp);
    int item_len = strlen(item);
    int sent_len = send(clnt_sock, item, item_len, 0);
    if (sent_len != item_len)
        error_handling("send() error");
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}