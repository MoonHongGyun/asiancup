#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void error_handling(char *messeage);
void NameCreate(int sock);
void *send_msg(void *arg);
void *recv_msg(void *arg);
void MessageSave(void);
void MapPrint(void);

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
int turn = 0;
char name[50] = {0};
char system_msg[4][BUF_SIZE] = {0};
char player_msg[6][BUF_SIZE] = {0};
int sm_cnt = 0;
int pm_cnt = 0;

int main(int argc, char *argv[])
{
    // argc = 3;
    // argv[1] = "127.0.0.1";
    // argv[2] = "10000";

    int sock;
    int str_len;
    struct sockaddr_in serv_adr;
    socklen_t adr_size;
    pthread_t snd_thread, rcv_thread;
    info.play_cnt = 0;
    int job_clnt;

    if (argc != 3)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    NameCreate(sock);
    pthread_create(&snd_thread, NULL, send_msg, (void *)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void *)&sock);
    pthread_join(snd_thread, NULL);
    pthread_join(rcv_thread, NULL);
    close(sock);
}

void NameCreate(int sock)
{
    puts("이름을 입력하세요.");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    write(sock, name, sizeof(name));
    system("clear");
    read(sock, info.msg, sizeof(info.msg));
    MessageSave();
    MapPrint();
}

void *send_msg(void *arg)
{
    int sock = *((int *)arg);
    char msg[BUF_SIZE];
    while (1)
    {
        fgets(msg, sizeof(msg), stdin);
        sprintf(info.msg, "%s: %s", name, msg);
        write(sock, info.msg, sizeof(info.msg));
    }
}

void *recv_msg(void *arg)
{
    int sock = *((int *)arg);

    while (1)
    {
        read(sock, info.msg, sizeof(info.msg));
        MessageSave();
        MapPrint;
    }
}

void MessageSave(void)
{
    char *check = strstr(info.msg, ":");
    if (check != NULL)
    {
        strcpy(player_msg[pm_cnt], info.msg);
        if (pm_cnt < 6)
            pm_cnt++;
    }
    else
    {
        strcpy(system_msg[sm_cnt], info.msg);
        if (sm_cnt == 3)
        {
            for (int i = 0; i < 4; i++)
                strcpy(player_msg[i], player_msg[i + 1]);
        }
        if (sm_cnt < 3)
            sm_cnt++;
    }
}

void MapPrint(void)
{
    system("clear");
    for (int i = 0; i < 4; i++)
        printf("%s", system_msg[i]);
    printf("====================================================");
    for (int i = 0; i < 6; i++)
        printf("%s", player_msg[i]);
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}