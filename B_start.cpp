#include <iostream>
#include <fstream>
#include "B_Ticket.h"
#include <termios.h>

using std::cout;

void Start::Map()
{
    std::ifstream main_file("/home/aiot/C/Asiancup");
    char ch;
    while (main_file.get(ch))
        cout << ch;

    cout << "------------------------------------------------\n";
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 2; j++)
        {
            switch (page1[i][j])
            {
            case 1:
                cout << "  회원가입\n";
                break;
            case 2:
                cout << "  로그인\n";
                break;
            case 3:
                cout << "  ID 찾기\n";
                break;
            case 4:
                cout << "  PW 찾기\n";
                break;
            case 5:
                cout << "  종료하기\n";
                break;
            case 99:
                cout << "               ▶";
                break;

            default:
                cout << "                 ";
                break;
            }
        }
}

int Start::Move()
{
    int key, xpos, ypos, temp;
    while (1)
    {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 2; j++)
                if (page1[i][j] == 99)
                {
                    xpos = i;
                    ypos = j;
                }
        key = getch();
        system("clear");
        switch (key)
        {
        case 65:
            if (xpos != 0)
            {
                temp = page1[xpos][ypos];
                page1[xpos][ypos] = page1[xpos - 1][ypos];
                page1[xpos - 1][ypos] = temp;
            }

            break;
        case 66:
            if (xpos != 4)
            {
                temp = page1[xpos][ypos];
                page1[xpos][ypos] = page1[xpos + 1][ypos];
                page1[xpos + 1][ypos] = temp;
            }

            break;
        case 10:
            return xpos;
        default:
            break;
        }
        Map();
    }
}

int Start::getch()
{
    int a;

    struct termios old;
    struct termios n;

    tcgetattr(0, &old);

    n = old;
    n.c_lflag &= ~(ICANON | ECHO);
    n.c_cc[VMIN] = 1;
    n.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &n);
    a = getchar();
    tcsetattr(0, TCSAFLUSH, &old);

    return a;
}