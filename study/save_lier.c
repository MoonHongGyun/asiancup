#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

void error_handling(char *messeage);
void NameCreate(int sock);
void MapPrint(int sock);
void *RecvMsg(int sock);
void *SendMsg(int sock);

#define MAX_CLNT 2
#define BUF_SIZE 1024

typedef struct user
{
    char name[MAX_CLNT][50];
    char msg[BUF_SIZE];
    char message[MAX_CLNT][BUF_SIZE];
    int play_cnt;
} USER;

USER info;
int turn = 0;

int main(int argc, char *argv[])
{
    // argc = 3;
    // argv[1] = "127.0.0.1";
    // argv[2] = "10001";

    int sock;
    int str_len;
    struct sockaddr_in serv_adr;
    socklen_t adr_size;
    pthread_t id_ts, id_tr;
    info.play_cnt = 0;

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
    system("clear");
    MapPrint(sock);
    pthread_create(&id_ts, NULL, SendMsg, sock);
    pthread_create(&id_tr, NULL, RecvMsg, sock);
    pthread_join(id_ts, NULL);
    pthread_join(id_tr, NULL);
    return 0;
}

void *SendMsg(int sock)
{
    char msg_T[BUF_SIZE];
    fgets(msg_T, sizeof(msg_T), stdin);
    while (1)
    {
        if (!strcmp(msg_T, "q\n") || !strcmp(msg_T, "Q\n"))
        {
            close(sock);
            exit(1);
        }
        else if (!strcmp(msg_T, "1\n") || !strcmp(msg_T, "2\n") || !strcmp(msg_T, "3\n") || !strcmp(msg_T, "4\n") || !strcmp(msg_T, "5\n") || !strcmp(msg_T, "6\n"))
        {
            sleep(2);
            write(sock, atoi(msg_T), sizeof(atoi(msg_T)));
        }
        else
        {
            sleep(2);
            write(sock, msg_T, sizeof(msg_T));
        }
        memset(msg_T, 0, sizeof(msg_T));
    }
}

void *RecvMsg(int sock)
{
    char msg_t[BUF_SIZE];
    read(sock, info.msg, sizeof(info.msg));
    MapPrint(sock);
    printf("%s\n", info.msg);
    read(sock, &info, sizeof(info));
    turn++;
    MapPrint(sock);
    read(sock, info.msg, sizeof(info.msg));
    printf("%s\n", info.msg);
    read(sock, info.msg, sizeof(info.msg));
    printf("%s\n", info.msg);
}

void NameCreate(int sock)
{
    char name[50] = {0};
    puts("이름을 입력하세요.");
    fgets(name, sizeof(name), stdin);
    write(sock, name, sizeof(name));
    system("clear");
    while (info.play_cnt < MAX_CLNT)
    {
        read(sock, &info, sizeof(info));
        printf("%s\n", info.msg);
    }
}

void MapPrint(int sock)
{
    system("clear");
    for (int i = 0; i < 6; i++)
    {
        switch (i)
        {
        case 1:
            printf("1.라이어는 일반인과 카테고리만 같은 주제가 주어집니다.\n2.투표시간은 15초 입니다.\n3.최다득표수가 라이어일 경우 라이어는 제시어를 맞출기회를 얻습니다.\n4.득표수가 동점일경우 같은 카테고리의 다른 제시어로 재경기\n");
            break;
        case 3:
            printf("타이머 %d\n", 15);
            break;
        case 5:
            if (turn == 1)
            {
                for (int j = 0; j < MAX_CLNT; j++)
                {
                    for (int k = 0; info.message[j][k] != NULL; k++)
                    {
                        printf("%c", info.message[j][k]);
                    }
                    printf("\n");
                }
            }
            else
                for (int j = 0; j < MAX_CLNT; j++)
                    printf("\n");
            break;
        default:
            for (int l = 0; l < 15; l++)
                printf("───");
            printf("\n");
            break;
        }
    }
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}