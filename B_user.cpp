#include <iostream>
#include <fstream>
#include <cstring>
#include "B_Ticket.h"
#include <termios.h>

using std::cin;
using std::cout;

int User::getch()
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

User::User()
{
    for (int i = 0; i < 30; i++)
    {
        id[i] = '\0';
        pw[i] = '\0';
        pnum[i] = '\0';
        email[i] = '\0';
    }
}

void User::Membership()
{
    int pass = 0;
    int check_count = 0;
    int cp = 1;
    int big = 0, small = 0, special = 0;
    int limit = 0;
    char check[30] = {
        0,
    };
    std::ifstream Inlist;
    std::ofstream Outlist;

    // ID
    while (cp == 1)
    {
        cp = 0;
        Inlist.open("userIDdata");
        cout << "ID: ";
        cin.getline(id, 30);
        while (Inlist.getline(check, 30))
        {
            if (!strcmp(id, check))
            {
                system("clear");
                cout << "중복되었습니다. 다시 입력하세요.\n";
                cp = 1;
                Inlist.close();
                break;
            }
        }
    }
    cp = 1;
    Inlist.close();

    // PW
    system("clear");

    while (pass == 0)
    {
        cout << "PW(숫자,대문자,소문자를 최소 1개씩이용): ";
        cin.getline(pw, 30);
        while (pw[check_count])
        {
            if (pw[check_count] >= 65 && pw[check_count] <= 90)
                big++;
            else if (pw[check_count] >= 97 && pw[check_count] <= 122)
                small++;
            else if (pw[check_count] >= 48 && pw[check_count] <= 57)
                special++;
            check_count++;
        }
        if (big > 0 && small > 0 && special > 0)
            pass = 1;
        else
        {
            cout << "잘못 입력하였습니다 다시 입력해주세요.\n";
            big = 0;
            small = 0;
            special = 0;
            check_count = 0;
        }
    }
    // 전화번호
    system("clear");
    while (cp == 1)
    {
        cp = 0;
        check_count = 0;
        Inlist.open("userPNUMdata");
        pass = 0;
        special = 0;
        while (pass == 0)
        {
            cout << "전화번호('-'없이 입력): ";
            cin.getline(pnum, 30);
            while (pnum[check_count])
            {
                if (limit == 0 && pnum[check_count] == '0' || limit == 2 && pnum[check_count] == '0')
                {
                    special++;
                    limit++;
                }
                if (limit == 1 && pnum[check_count] == '1')
                {
                    special++;
                    limit++;
                }
                if (pnum[check_count] >= 48 && pnum[check_count] <= 57)
                    special++;
                else
                    special += 100;
                check_count++;
            }
            if (special == 14 && strlen(pnum) == 11)
                pass = 1;
            else
            {
                limit = 0;
                special = 0;
                check_count = 0;
                cout << "잘못 입력하였습니다.\n";
            }
        }
        special = 0;
        limit = 0;
        while (Inlist.getline(check, 30))
        {
            if (!strcmp(pnum, check))
            {
                system("clear");
                cp = 1;
                cout << "중복되었습니다. 다시 입력해주세요.\n";
                limit = 0;
                special = 0;
                check_count = 0;
                Inlist.close();
                break;
            }
        }
    }
    cp = 1;
    Inlist.close();

    // 이메일
    system("clear");
    while (cp == 1)
    {
        cp = 0;
        check_count = 0;
        pass = 0;
        Inlist.open("userEMAILdata");
        while (pass == 0)
        {
            cout << "이메일: ";
            cin.getline(email, 30);
            if (strstr(email, "@") && email[strlen(email) - 4] == '.' && email[strlen(email) - 3] == 'c' && email[strlen(email) - 2] == 'o' && email[strlen(email) - 1] == 'm')
                pass = 1;
            else
                cout << "잘못된형식입니다 다시입력하세요.\n";
        }
        while (Inlist.getline(check, 30))
        {
            if (!strcmp(email, check))
            {
                system("clear");
                cp = 1;
                cout << "중복되었습니다. 다시 입력해주세요.\n";
                Inlist.close();
                break;
            }
        }
    }
    Inlist.close();

    Outlist.open("userIDdata", std::ios::app);
    Outlist << id << "\n";
    Outlist.close();

    Outlist.open("userPWdata", std::ios::app);
    Outlist << pw << "\n";
    Outlist.close();

    Outlist.open("userPNUMdata", std::ios::app);
    Outlist << pnum << "\n";
    Outlist.close();

    Outlist.open("userEMAILdata", std::ios::app);
    Outlist << email << "\n";
    Outlist.close();

    mnum = id;
    mnum += "1111";
    Outlist.open("userMNUMdata");
    Outlist << mnum
            << "\n";
    Outlist.close();
    Outlist.open(mnum);
    Outlist.close();
}

int User::Login()
{
    int count = 1;
    int nothing = 1;
    char check[30] = {
        0,
    };
    std::string scheck;
    char star = 'a';
    std::ifstream Inline;
    while (1)
    {
        cout << "엔터만 입력하면 나가집니다.\n";
        cout << "ID: ";
        cin.getline(id, 30);
        if (id[0] == '\0')
            return 0;
        cout << "PW: ";
        int starnum = 0;
        while (1)
        {
            star = getch();
            if (star == '\n')
                break;
            pw[starnum] = star;
            cout << '*';
            starnum++;
        }
        pw[starnum] = '\0';

        Inline.open("userIDdata");
        while (Inline.getline(check, 30))
        {
            nothing++;
            if (!strcmp(check, id))
                break;
            count++;
        }
        Inline.close();
        if (count == nothing)
        {
            cout << "로그인 실패\n";
            count = 1;
            nothing = 1;
            continue;
        }
        else
        {
            Inline.open("userPWdata");
            for (int i = 0; i < count; i++)
                Inline.getline(check, 30);
            Inline.close();
            if (!strcmp(check, pw))
            {
                cout << "로그인 성공\n";
            }
            else
            {
                cout << "로그인 실패\n";
                count = 1;
                nothing = 1;
                continue;
            }
        }
        Inline.open("userMNUMdata");
        for (int i = 0; i < count; i++)
            getline(Inline, scheck);
        Inline.close();
        mnum = scheck;
        return 1;
    }
}

void User::Find_ID()
{
    int count = 1;
    int nothing = 1;
    char check[30];
    std::ifstream Inline;
    while (1)
    {
        cout << "전화번호: ";
        cin.getline(pnum, 30);
        cout << "이메일: ";
        cin.getline(email, 30);
        Inline.open("userPNUMdata");
        while (Inline.getline(check, 30))
        {
            nothing++;
            if (!strcmp(check, pnum))
                break;
            count++;
        }
        Inline.close();
        if (nothing == count)
        {
            cout << "입력하신 정보와 일치하는 아이디는 없습니다.\n";
            count = 1;
            nothing = 1;
            continue;
        }
        else
        {
            Inline.open("userEMAILdata");
            for (int i = 0; i < count; i++)
                Inline.getline(check, 30);
            Inline.close();
            if (!strcmp(check, email))
            {
                Inline.open("userIDdata");
                for (int j = 0; j < count; j++)
                    Inline.getline(check, 30);
                cout << "(아무키나 누르시면 넘어갑니다.)ID: " << check;
                cin.get();
            }
            else
            {
                cout << "입력하신 정보와 일치하는 아이디는 없습니다.\n";
                count = 1;
                nothing = 1;
                continue;
            }
        }
        break;
    }
}

void User::Find_PW()
{
    int count = 1;
    int nothing = 1;
    char check[30];
    std::ifstream Inline;
    while (1)
    {
        cout << "ID: ";
        cin.getline(id, 30);
        cout << "전화번호: ";
        cin.getline(pnum, 30);
        cout << "이메일: ";
        cin.getline(email, 30);
        Inline.open("userPNUMdata");
        while (Inline.getline(check, 30))
        {
            nothing++;
            if (!strcmp(check, pnum))
                break;
            count++;
        }
        Inline.close();
        if (nothing == count)
        {
            cout << "입력하신 정보와 일치하는 아이디는 없습니다.\n";
            count = 1;
            nothing = 1;
            continue;
        }
        else
        {
            Inline.open("userEMAILdata");
            for (int i = 0; i < count; i++)
                Inline.getline(check, 30);
            Inline.close();
            if (!strcmp(check, email))
            {
                Inline.open("userIDdata");
                for (int j = 0; j < count; j++)
                    Inline.getline(check, 30);
                Inline.close();
                if (!strcmp(check, id))
                {
                    Inline.open("userPWdata");
                    for (int k = 0; k < count; k++)
                        Inline.getline(check, 30);
                    cout << "(아무키나 누르시면 넘어갑니다.)PW: " << check;
                    cin.get();
                }
            }
            else
            {
                cout << "입력하신 정보와 일치하는 아이디는 없습니다.\n";
                count = 1;
                nothing = 1;
                continue;
            }
        }
        break;
    }
}
