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

void Move(int *sock, int *pos, int team);
void error_handling(char *messeage);
void Map_print(void);
int win(void);
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
    argc = 3;
    argv[1] = "10.10.20.123";
    argv[2] = "10000";
    int sock, change1, change2;
    int pos[4] = {0, 0, 0, 0}; // 1.xpos 2.ypos 3.���� 4.wincheck
    int first = 0;
    char message[BUF_SIZE];

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

    read(sock, pos, sizeof(pos));

    while (1) // �����Լ�
    {
        if (pos[2] == 1)
        {
            Move(&sock, pos, 10);
            read(sock, pos, sizeof(pos));
            change1 = pos[0];
            change2 = pos[1];
            omok_plate[change1][change2] = 20;
        }
        else
        {
            read(sock, pos, sizeof(pos));
            change1 = pos[0];
            change2 = pos[1];
            omok_plate[change1][change2] = 10;
            Move(&sock, pos, 20);
        }
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

void Move(int *sock, int *pos, int team)
{
    int ent, temp, x, y, key, user1;
    user1 = *sock;
    ent = 0;
    temp = omok_plate[8][7];
    omok_plate[8][7] = 30;

    system("clear");
    Map_print();
    // if (pos[3] == 0)
    //     printf("YOUR TURN!!");
    // else
    //     printf("LOSE~~~~~");
    printf("YOUR TURN!!");

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
                omok_plate[x][y] = team;

            Map_print();
            pos[0] = x;
            pos[1] = y;
            int result = win();
            pos[3] = result;
            write(user1, pos, sizeof(pos));
            if (pos[3] != 0)
            {
                puts("WIN!!!!");
                break;
            }
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
                    printf("\u2500\u25c6");
                else if (j == 0)
                    printf("\u25c6\u2500");
                else
                    printf("\u2500\u25c6\u2500");
                break;
            case 10:
                if (j == 14)
                {
                    printf("\u2500\x1b[31m\u25cf\x1b[0m");
                }
                else if (j == 0)
                    printf("\x1b[31m\u25cf\x1b[0m\u2500");
                else
                    printf("\u2500\x1b[31m\u25cf\x1b[0m\u2500");
                break;
            case 20:
                if (j == 14)
                    printf("\u2500\x1b[34m\u25cf\x1b[0m");
                else if (j == 0)
                    printf("\x1b[34m\u25cf\x1b[0m\u2500");
                else
                    printf("\u2500\x1b[34m\u25cf\x1b[0m\u2500");
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

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return c;
}

int win(void)
{

    for (int i = 1; i < 15; i++) // ���� ����
    {
        for (int j = 1; j < 15; j++)
        {
            if (omok_plate[i][j] == 10 && omok_plate[i][j + 1] == 10 && omok_plate[i][j + 2] == 10 && omok_plate[i][j + 3] == 10 && omok_plate[i][j + 4] == 10)
                return 1;
            if (omok_plate[i][j] == 20 && omok_plate[i][j + 1] == 20 && omok_plate[i][j + 2] == 20 && omok_plate[i][j + 3] == 20 && omok_plate[i][j + 4] == 20)
                return 2;

            if (omok_plate[i][j] == 10 && omok_plate[i + 1][j] == 10 && omok_plate[i + 2][j] == 10 && omok_plate[i + 3][j] == 10 && omok_plate[i + 4][j] == 10)
                return 1;
            if (omok_plate[i][j] == 20 && omok_plate[i + 1][j] == 20 && omok_plate[i + 2][j] == 20 && omok_plate[i + 3][j] == 20 && omok_plate[i + 4][j] == 20)
                return 2;
        }
    }

    for (int i = 2; i < 15; i++) // �밢��
    {
        for (int j = 2; j < 15; j++)
        {
            if (omok_plate[i - 2][j - 2] == 10 && omok_plate[i - 1][j - 1] == 10 && omok_plate[i][j] == 10 && omok_plate[i + 1][j + 1] == 10 && omok_plate[i + 2][j + 2] == 10)
                return 1;
            else if (omok_plate[i + 2][j - 2] == 10 && omok_plate[i + 1][j - 1] == 10 && omok_plate[i][j] == 10 && omok_plate[i - 1][j + 1] == 10 && omok_plate[i - 2][j + 2] == 10)
                return 1;

            if (omok_plate[i - 2][j - 2] == 20 && omok_plate[i - 1][j - 1] == 20 && omok_plate[i][j] == 20 && omok_plate[i + 1][j + 1] == 20 && omok_plate[i + 2][j + 2] == 20)
                return 2;
            else if (omok_plate[i + 2][j - 2] == 20 && omok_plate[i + 1][j - 1] == 20 && omok_plate[i][j] == 20 && omok_plate[i - 1][j + 1] == 20 && omok_plate[i - 2][j + 2] == 20)
                return 2;
        }
    }
    return 0;
}
