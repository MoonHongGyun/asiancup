#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void error_handling(char *messeage);
void NameCreate(void *arg);
void *handle_clnt(void *arg);

#define MAX_CLNT 2
#define BUF_SIZE 1024

typedef struct user
{
    char name[MAX_CLNT][50];
    char msg[BUF_SIZE];
    char message[MAX_CLNT][BUF_SIZE];
    int play_cnt;
    int job;
} USER;

USER info;
int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
int lier;
// char *word = {'123'};
// char *L_word = {'456'};
int vote[MAX_CLNT] = {0};
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
    // argc = 2;
    // argv[1] = "10001";

    int serv_sock, clnt_sock;
    int str_len;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_size;
    pthread_t id_t;
    info.play_cnt = 0;

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    while (1)
    {
        adr_size = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_size);
        pthread_mutex_lock(&mutex);
        clnt_socks[clnt_cnt] = clnt_sock;
        info.play_cnt++;
        pthread_mutex_unlock(&mutex);

        NameCreate((void *)&clnt_sock);
        pthread_create(&id_t, NULL, handle_clnt, (void *)&clnt_sock);
        pthread_detach(id_t);

        clnt_cnt++;
    }
    close(serv_sock);
}

void *handle_clnt(void *arg)
{
    int clnt = *((int *)arg);
    while (1)
    {
        read(clnt, info.msg, sizeof(info.msg));
        // pthread_mutex_lock(&mutex);
        for (int i = 0; i < MAX_CLNT; i++)
            write(clnt_socks[i], &info, sizeof(info));
    }
}

void NameCreate(void *arg)
{
    int clnt = *((int *)arg);
    char name[50] = {0};

    read(clnt, name, sizeof(name));
    // name[strlen(name) - 1] = '\0';
    strcpy(info.name[clnt_cnt], name);
    sprintf(info.msg, "%s 님이 입장했습니다.", info.name[clnt_cnt]);
    printf("%s\n", info.msg);
    for (int i = 0; i < clnt_cnt + 1; i++)
        write(clnt_socks[i], &info, sizeof(info));
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}