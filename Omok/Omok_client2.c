#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>

#define BUF_SIZE 1024
#define LEFT 65
#define RIGHT 66
#define UP 68
#define DOWN 67
#define ENTER 10

void Move(int *sock, int *pos);
void error_handling(char *messeage);
void Map_print(void);
int win(int xpos, int ypos);
int getch();

int omok_plate[15][15] = {
    {6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8}};

int main(int argc, char *argv[])
{
    int sock, change1, change2;
    int pos[2];

    struct sockaddr_in serv_adr;
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
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
    else
        puts("connected.............");
    while (1)
    {
        read(sock, pos, sizeof(pos));
        change1 = pos[0];
        change2 = pos[1];
        omok_plate[change1][change2] = 10;
        Move(&sock, pos);
    }
    close(sock);
    return 0;
}

void error_handling(char *messeage)
{
    fputs(messeage, stderr);
    fputc('\n', stderr);
    exit(1);
}

void Move(int *sock, int *pos)
{
    int ent, temp, x, y, key, user1;
    user1 = *sock;
    ent = 0;
    temp = omok_plate[8][7];
    omok_plate[8][7] = 30;

    Map_print();

    while (ent == 0)
    {
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++)
                if (omok_plate[i][j] == 30)
                {
                    x = i;
                    y = j;
                }
        key = getch();
        switch (key)
        {
        case RIGHT:
            if (x != 14)
            {
                system("clear");
                omok_plate[x][y] = temp;
                temp = omok_plate[x + 1][y];
                omok_plate[x + 1][y] = 30;
                Map_print();
            }
            break;
        case LEFT:
            if (x != 0)
            {
                system("clear");
                omok_plate[x][y] = temp;
                temp = omok_plate[x - 1][y];
                omok_plate[x - 1][y] = 30;
                Map_print();
            }
            break;
        case UP:
            if (y != 0)
            {
                system("clear");
                omok_plate[x][y] = temp;
                temp = omok_plate[x][y - 1];
                omok_plate[x][y - 1] = 30;
                Map_print();
            }
            break;
        case DOWN:
            if (y != 14)
            {
                system("clear");
                omok_plate[x][y] = temp;
                temp = omok_plate[x][y + 1];
                omok_plate[x][y + 1] = 30;
                Map_print();
            }
            break;
        case ENTER:
            system("clear");
            if (temp == 10 || temp == 20)
            {
                Map_print();
                continue;
            }
            else
                omok_plate[x][y] = 20;
            Map_print();
            pos[0] = x;
            pos[1] = y;
            write(user1, pos, sizeof(pos));
            win(x, y);
            ent++;
            break;
        default:
            break;
        }
    }
}

void Map_print(void)
{

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            switch (omok_plate[i][j])
            {
            case 1:
                printf("\u2500\u253c\u2500");
                break;
            case 2:
                printf("\u2500\u252c\u2500");
                break;
            case 3:
                printf("\u2500\u2524");
                break;
            case 4:
                printf("\u2500\u2534\u2500");
                break;
            case 5:
                printf("\u251c\u2500");
                break;
            case 6:
                printf("\u256d\u2500");
                break;
            case 7:
                printf("\u2500\u256e");
                break;
            case 8:
                printf("\u2500\u256f");
                break;
            case 9:
                printf("\u2570\u2500");
                break;
            case 30:
                if (j == 14)
                    printf("\u2500\x1b[33m\u25c6\x1b[0m");
                else if (j == 0)
                    printf("\x1b[33m\u25c6\x1b[0m\u2500");
                else
                    printf("\u2500\x1b[33m\u25c6\x1b[0m\u2500");
                break;
            case 10:
                if (j == 14)
                {
                    printf("\u2500\x1b[30m\u25cf\x1b[0m");
                }
                else if (j == 0)
                    printf("\x1b[30m\u25cf\x1b[0m\u2500");
                else
                    printf("\u2500\x1b[30m\u25cf\x1b[0m\u2500");
                break;
            case 20:
                if (j == 14)
                    printf("\u2500\u25cf");
                else if (j == 0)
                    printf("\u25cf\u2500");
                else
                    printf("\u2500\u25cf\u2500");
                break;
            default:
                break;
            }
        }
        printf("\n");
    }
}

int getch()
{
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);        // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                     // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                    // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 터미널에 설정 입력
    c = getchar();                              // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래의 설정으로 복구
    return c;
}

int win(int xpos, int ypos)
{
    int W_cnt = 0;
    for (int i = 0; i < 11; i++)
    {
        for (int j = i; j < i + 5; j++)
            if (omok_plate[xpos][j] == 10)
                W_cnt++;
        if (W_cnt == 5)
            exit(0);
        else
            W_cnt = 0;
    }

    for (int i = 0; i < 11; i++)
    {
        for (int j = i; j < i + 5; j++)
            if (omok_plate[j][ypos] == 10)
                W_cnt++;
        if (W_cnt == 5)
            exit(0);
        else
            W_cnt = 0;
    }
    int xlimit = xpos, ylimit = ypos;
    W_cnt = 0;
    while (xlimit != 15 && ylimit != 15)
    {
        xlimit--;
        ylimit++;
    }
    if (ylimit < 11 && xlimit == 0)
    {
        for (int i = 0; i < 11 - ylimit; i++)
        {
            for (int j = 0; j < 5; j++)
                if (omok_plate[xlimit + i + j][ylimit + i + j] == 20)
                    W_cnt++;
            if (W_cnt == 5)
                exit(0);
        }
    }
    else if (ylimit == 0 && xlimit < 11)
    {
        for (int i = 0; i < 11 - xlimit; i++)
        {
            for (int j = 0; j < 5; j++)
                if (omok_plate[xlimit + i + j][ylimit + i + j] == 20)
                    W_cnt++;
            if (W_cnt == 5)
                exit(0);
        }
    }
    xlimit = xpos;
    ylimit = ypos;
    W_cnt = 0;
    while (xlimit != 0 && ylimit != 15)
    {
        xlimit++;
        ylimit--;
    }
    if (xlimit < 11 && ylimit == 0)
    {
        for (int i = 0; i < 11 - xlimit; i++)
        {
            for (int j = 0; j < 5; j++)
                if (omok_plate[xlimit - i - j][ylimit + i + j] == 20)
                    W_cnt++;
            if (W_cnt == 5)
                exit(0);
        }
    }
    else if (xlimit == 0 && ylimit < 11)
    {
        for (int i = 0; i < 11 - ylimit; i++)
        {
            for (int j = 0; j < 5; j++)
                if (omok_plate[xlimit - i - j][ylimit + i + j] == 20)
                    W_cnt++;
            if (W_cnt == 5)
                exit(0);
        }
    }
}
