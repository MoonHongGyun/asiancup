#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <termios.h>

void Map_print(void);
int getch();
int win(void);

#define LEFT 65
#define RIGHT 66
#define UP 68
#define DOWN 67
#define ENTER 10

int omok_plate[15][15] = {
    {6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8}};

int main(void)
{
    int key, temp, x, y, ent = 0;

    while (1)
    {
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
                    omok_plate[x][y] = 10;
                Map_print();
                printf("%d", win());
                ent++;
                break;
            default:
                break;
            }
        }
        temp = omok_plate[8][7];
        omok_plate[8][7] = 30;
        ent = 0;
        system("clear");
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
                ent++;
                break;
            default:
                break;
            }
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
                printf("─┼─");
                break;
            case 2:
                printf("─┬─");
                break;
            case 3:
                printf("─┤");
                break;
            case 4:
                printf("─┴─");
                break;
            case 5:
                printf("├─");
                break;
            case 6:
                printf("┌─");
                break;
            case 7:
                printf("─┐");
                break;
            case 8:
                printf("─┘");
                break;
            case 9:
                printf("└─");
                break;
            case 30:
                if (j == 14)
                    printf("─◆");
                else if (j == 0)
                    printf("◆─");
                else
                    printf("─◆─");
                break;
            case 10:
                if (j == 14)
                {
                    printf("─\x1b[30m\u25cf\x1b[0m");
                }
                else if (j == 0)
                    printf("\x1b[30m\u25cf\x1b[0m─");
                else
                    printf("─\x1b[30m\u25cf\x1b[0m─");
                break;
            case 20:
                if (j == 14)
                    printf("─●");
                else if (j == 0)
                    printf("●─");
                else
                    printf("─●─");
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

int win(void)
{

    for (int i = 1; i < 15; i++) // 가로 세로
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

    for (int i = 2; i < 15; i++) // 대각선
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