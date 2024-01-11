#include <iostream>
#include <fstream>
#include "B_Ticket.h"
#include <termios.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using std::cout;

int MainPage::getch()
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

void MainPage::Page_1()
{
    cout << "------------------------------------------------\n";
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 2; j++)
        {
            switch (main_p1[i][j])
            {
            case 1:
                cout << "  경기 일정\n";
                break;
            case 2:
                cout << "  조별 경기 일정\n";
                break;
            case 3:
                cout << "  참가국 및 조별정보\n";
                break;
            case 4:
                cout << "  한국 감독 및 선수 명단\n";
                break;
            case 5:
                cout << "  개최지 및 기본정보\n"
                     << "------------------------------------------------\n";
                break;
            case 6:
                cout << "  예매하기\n";
                break;
            case 7:
                cout << "  예매확인\n";
                break;
            case 8:
                cout << "  로그아웃\n";
                break;
            case 99:
                cout << "            ▶";
                break;

            default:
                cout << "              ";
                break;
            }
        }
}

int MainPage::P1_Move()
{
    int key, xpos, ypos, temp;
    while (1)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 2; j++)
                if (main_p1[i][j] == 99)
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
                temp = main_p1[xpos][ypos];
                main_p1[xpos][ypos] = main_p1[xpos - 1][ypos];
                main_p1[xpos - 1][ypos] = temp;
            }
            break;
        case 66:
            if (xpos != 7)
            {
                temp = main_p1[xpos][ypos];
                main_p1[xpos][ypos] = main_p1[xpos + 1][ypos];
                main_p1[xpos + 1][ypos] = temp;
            }
            break;
        case 10:
            return xpos;
        default:
            break;
        }
        Page_1();
    }
}

void MainPage::Page_plan(int n)
{
    char check[150];
    char check_cpy[50];
    char check_day[50];
    int day = 13 + n;
    sprintf(check_day, "%d일", day);
    std::ifstream Inlist("/home/aiot/C/Planer");
    while (Inlist.getline(check, 150))
    {
        if (strstr(check, check_day))
            cout << check << "\n";
    }
    cout << "------------------------------------------------\n";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
        {
            switch (plan_arr[i][j])
            {
            case 1:
                cout << "   다음\n";
                break;
            case 2:
                cout << "   이전\n";
                break;
            case 3:
                cout << "   홈\n";
                break;
            case 99:
                cout << "            ▶";
                break;

            default:
                cout << "              ";
                break;
            }
        }
}

int MainPage::Page_plan_move(int n)
{
    int key, xpos, ypos, temp;
    while (1)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++)
                if (plan_arr[i][j] == 99)
                {
                    xpos = i;
                    ypos = j;
                }
        key = getch();
        system("clear");

        switch (key)
        {
        case 65: // 하
            if (xpos != 0)
            {
                temp = plan_arr[xpos][ypos];
                plan_arr[xpos][ypos] = plan_arr[xpos - 1][ypos];
                plan_arr[xpos - 1][ypos] = temp;
            }
            break;
        case 66: // 상
            if (xpos != 2)
            {
                temp = plan_arr[xpos][ypos];
                plan_arr[xpos][ypos] = plan_arr[xpos + 1][ypos];
                plan_arr[xpos + 1][ypos] = temp;
            }
            break;
        case 10:
            return xpos;
        default:
            break;
        }
        Page_plan(n);
    }
}

void MainPage::Page_Gplan(int n)
{
    char check[150];
    const char *group[6] = {"A조", "B조", "C조", "D조", "E조", "F조"};
    std::ifstream Inlist;

    for (int i = 0; i < 14; i++)
        switch (Gplan_arr[i])
        {
        case 1:
            cout << " A.";
            break;
        case 2:
            cout << " B.";
            break;
        case 3:
            cout << " C.";
            break;
        case 4:
            cout << " D.";
            break;
        case 5:
            cout << " E.";
            break;
        case 6:
            cout << " F.";
            break;
        case 7:
            cout << " 홈\n";
            break;

        case 99:
            cout << "▶ ";
            break;

        default:
            cout << "  ";
            break;
        }
    cout << "------------------------------------------------\n";

    Inlist.open("Planer");
    while (Inlist.getline(check, 150))
        if (strstr(check, group[n]))
            cout << check << "\n";
    Inlist.close();
}

int MainPage::Page_Gplan_move(int n)
{
    int xpos, temp, key;
    while (1)
    {
        for (int i = 0; i < 14; i++)
            if (Gplan_arr[i] == 99)
            {
                xpos = i;
                break;
            }
        key = getch();
        system("clear");
        switch (key)
        {
        case 67: // 우
            if (xpos != 12)
            {
                temp = Gplan_arr[xpos];
                Gplan_arr[xpos] = Gplan_arr[xpos + 2];
                Gplan_arr[xpos + 2] = temp;
            }
            break;
        case 68: // 좌
            if (xpos != 0)
            {
                temp = Gplan_arr[xpos];
                Gplan_arr[xpos] = Gplan_arr[xpos - 2];
                Gplan_arr[xpos - 2] = temp;
            }
            break;
        case 10:
            return Gplan_arr[xpos + 1];
        default:
            break;
        }
        Page_Gplan(n);
    }
}

void MainPage::Page_country()
{
    cout << "------------------------------------------------\n"
         << " A조 : 카타르, 중국, 타지키스탄, 레바논\n"
         << " B조 : 오스트레일리아, 우즈베키스탄, 시리아, 인도\n"
         << " C조 : 이란, 아랍에미리트, 홍콩, 팔레스타인\n"
         << " D조 : 일본, 인도네시아, 이라크, 베트남\n"
         << " E조 : 한국, 말레이시아, 조르단, 바레인\n"
         << " F조 : 태국, 오만, 키르기스스탄, 사우디아라비아\n"
         << "------------------------------------------------\n"
         << "(아무키나 누르시면 나가집니다.)\n";
}

void MainPage::Page_playerlist()
{
    char line[100];
    std::ifstream Inlist("Korea_playerlist");
    while (Inlist.getline(line, 100))
        cout << line << std::endl;
    Inlist.close();
}

void MainPage::Page_info()
{
    cout << "------------------------------------------------\n"
         << "개최지 : 카타르 도하, 알 와크라, 알 라이얀, 알 코르\n"
         << "중계 : tvN, tvN SPORTS, 쿠팡플레이 \n"
         << "기간 : 2024년 1월 12일 (금) ~ 2월 10일 (일) (현지기준)\n"
         << "------------------------------------------------\n"
         << "(아무키나 누르시면 나가집니다.)\n";
}

void MainPage::Page_R_day(int n)
{
    char check[150];
    cout << "------------------------------------------------\n";
    for (int i = 0; i < 4; i++)
        switch (mrday[i])
        {
        case 1:
            cout << "날짜: 01/" << mrday_count;
            break;
        case 2:
            cout << " 🏠 \n";
            break;
        case 99:
            if (n == 0)
                cout << " ▶  ";
            else
                cout << "    ";
            break;
        default:
            cout << "    ";
            break;
        }
    cout << "------------------------------------------------\n";
    cout << "             방향키로 날짜 선택\n";
    cout << "------------------------------------------------\n";

    std::ifstream Inlist("Planer");
    mragame_count = 0;
    while (Inlist.getline(check, 150))
    {
        if (strstr(check, mday.c_str()))
        {
            switch (mrgame[mragame_count])
            {
            case 99:
                if (n != 0)
                    cout << "▶   " << check << "\n";
                else
                    cout << "    " << check << "\n";
                break;

            default:
                cout << "    " << check << "\n";
                break;
            }
            mragame_count++;
        }
    }
}

int MainPage::Page_R_day_move()
{
    std::string dayplus, check;
    std::ifstream Inlist;
    int posval;
    int stop = 0;
    while (1)
    {
        dayplus = "2024 01 ";
        int xpos, key, temp, key2;
        for (int i = 0; i < 4; i++)
            if (mrday[i] == 99)
                xpos = i;
        key = getch();
        system("clear");
        switch (key)
        {
        case 65:
            if (mrday_count < 26)
                mrday_count++;
            break;
        case 66:
            if (mrday_count > 13)
                mrday_count--;
            break;
        case 67:
            if (xpos != 2)
            {
                temp = mrday[xpos];
                mrday[xpos] = mrday[xpos + 2];
                mrday[xpos + 2] = temp;
            }
            break;
        case 68:
            if (xpos != 0)
            {
                temp = mrday[xpos];
                mrday[xpos] = mrday[xpos - 2];
                mrday[xpos - 2] = temp;
            }
            break;
        case 10:
            if (xpos == 2)
                return 0;
            Page_R_day(1);
            posval = Page_R_day_move2();
            Inlist.open("Planer");
            while (stop < posval) // 좌표값에 해당하는 경기 저장
            {
                getline(Inlist, check);
                if (!check.find(mday))
                {
                    mzone = check;
                    stop++;
                }
            }
            Inlist.close();
            return 1;
        default:
            break;
        }
        dayplus += std::to_string(mrday_count);
        mday = dayplus;
        Page_R_day();
    }
}

int MainPage::Page_R_day_move2()
{
    int xpos, key2, temp;
    while (1)
    {
        for (int i = 0; i <= mragame_count; i++)
            if (mrgame[i] == 99)
                xpos = i;
        key2 = getch();
        system("clear");
        switch (key2)
        {
        case 65:
            if (xpos > 0)
            {
                temp = mrgame[xpos];
                mrgame[xpos] = mrgame[xpos - 1];
                mrgame[xpos - 1] = temp;
            }
            break;
        case 66:
            if (xpos < mragame_count - 1)
            {
                temp = mrgame[xpos];
                mrgame[xpos] = mrgame[xpos + 1];
                mrgame[xpos + 1] = temp;
            }
            break;
        case 10:
            return xpos + 1;
        default:
            break;
        }
        Page_R_day(1);
    }
}

void MainPage::Page_R_zone()
{
    int arr[6][9] = {{0, 4, 4, 3, 3, 3, 3, 4, 4},
                     {0, 4, 4, 1, 1, 1, 1, 4, 4},
                     {0, 2, 1, 0, 0, 0, 0, 1, 2},
                     {0, 2, 1, 0, 0, 0, 0, 1, 2},
                     {0, 4, 4, 1, 1, 1, 1, 4, 4},
                     {0, 4, 4, 3, 3, 3, 3, 4, 4}};

    cout << "-------------------------------------------\n"
         << " MVIP 🟥 = 250000     "
         << " VIP  🟧 = 150000\n"
         << " GOLD 🟨 = 100000     "
         << " SIVER🟩 = 70000\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
            switch (arr[i][j])
            {
            case 1:
                cout << " 🟥 ";
                break;
            case 2:
                cout << " 🟧 ";
                break;
            case 3:
                cout << " 🟨 ";
                break;
            case 4:
                cout << " 🟩 ";
                break;

            default:
                cout << "    ";
                break;
            }
        cout << "\n";
    }
    cout << "-------------------------------------------\n";
    for (int i = 0; i < 10; i++)
        switch (zone_arr[i])
        {
        case 1:
            cout << " 🟥 ";
            break;
        case 2:
            cout << " 🟧 ";
            break;
        case 3:
            cout << " 🟨 ";
            break;
        case 4:
            cout << " 🟩 ";
            break;
        case 5:
            cout << " 🏠 \n";
            break;
        case 99:
            cout << "  ▶";
            break;
        default:
            cout << "   ";
            break;
        }
    cout << "-------------------------------------------\n";
}

int MainPage::Page_R_zone_move()
{
    int key, xpos, temp;
    const char *arr[4] = {"MVIP", "VIP", "GOLD", "SILVER"};
    while (1)
    {
        for (int i = 0; i < 10; i++)
            if (zone_arr[i] == 99)
            {
                xpos = i;
                break;
            }
        key = getch();
        system("clear");
        switch (key)
        {
        case 67:
            if (xpos != 8)
            {
                temp = zone_arr[xpos];
                zone_arr[xpos] = zone_arr[xpos + 2];
                zone_arr[xpos + 2] = temp;
            }
            break;
        case 68:
            if (xpos != 0)
            {
                temp = zone_arr[xpos];
                zone_arr[xpos] = zone_arr[xpos - 2];
                zone_arr[xpos - 2] = temp;
            }
            break;
        case 10:
            if (xpos == 8)
                return 0;
            mlocal = arr[xpos / 2];
            for (int i = 0; i < 6; i++)
                for (int j = 1; j < 9; j++)
                    if ((xpos / 2 + 1) != mstadium[i][j])
                        mstadium[i][j] = 77;
            return 1;
        default:
            break;
        }
        Page_R_zone();
    }
}

void MainPage::Page_R_seat()
{
    cout << "-------------------------------------------\n";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
            switch (mstadium[i][j])
            {
            case 1:
            case 2:
            case 3:
            case 4:
                cout << " ⬜ ";
                break;
            case 77:
                cout << " ❌ ";
                break;
            case 88:
                cout << " ✅ ";
                break;
            case 99:
                cout << " ⬛ ";
                break;
            default:
                cout << "    ";
                break;
            }
        cout << "\n";
    }
    cout << "-------------------------------------------\n";
    cout << "좌석선택(여러개 선택가능): 엔터  선택완료:q/Q\n";
    cout << "-------------------------------------------\n";
}

int MainPage::Page_R_seat_move()
{
    int key, xpos, ypos, temp1, temp2;
    temp1 = 0;
    mrnum = 0;
    while (1)
    {
        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 9; j++)
                if (mstadium[i][j] == 99)
                {
                    xpos = i;
                    ypos = j;
                }
        key = getch();
        system("clear");
        switch (key)
        {
        case 65:
            if (xpos != 0 && mstadium[xpos - 1][ypos] != 0)
            {
                temp2 = mstadium[xpos - 1][ypos];
                mstadium[xpos - 1][ypos] = mstadium[xpos][ypos];
                mstadium[xpos][ypos] = temp1;
                temp1 = temp2;
            }
            break;
        case 66:
            if (xpos != 5 && mstadium[xpos + 1][ypos] != 0)
            {
                temp2 = mstadium[xpos + 1][ypos];
                mstadium[xpos + 1][ypos] = mstadium[xpos][ypos];
                mstadium[xpos][ypos] = temp1;
                temp1 = temp2;
            }
            break;
        case 67:
            if (ypos != 8 && mstadium[xpos][ypos + 1] != 0)
            {
                temp2 = mstadium[xpos][ypos + 1];
                mstadium[xpos][ypos + 1] = mstadium[xpos][ypos];
                mstadium[xpos][ypos] = temp1;
                temp1 = temp2;
            }
            break;
        case 68:
            if (ypos != 1 && mstadium[xpos][ypos - 1] != 0 && xpos + ypos != 0)
            {
                temp2 = mstadium[xpos][ypos - 1];
                mstadium[xpos][ypos - 1] = mstadium[xpos][ypos];
                mstadium[xpos][ypos] = temp1;
                temp1 = temp2;
            }
            break;
        case 10:
            if (temp1 < 5 && temp1 != 0)
            {
                temp1 = 88;
            }
            else if (temp1 == 88)
            {
                temp1 = mstadium_rst[xpos][ypos];
            }
            break;
        case 81:
        case 113:
            for (int i = 0; i < 6; i++)
                for (int j = 0; j < 9; j++)
                    if (mstadium[i][j] == 88 || mstadium[i][j] == 99 && temp1 == 88)
                    {
                        mrnum++;
                        if (i == 0)
                        {
                            mseat += "A";
                            mseat += std::to_string(j);
                            mseat += ".";
                        }
                        else if (i == 1)
                        {
                            mseat += "B";
                            mseat += std::to_string(j);
                            mseat += ".";
                        }
                        else if (i == 2)
                        {
                            mseat += "C";
                            mseat += std::to_string(j);
                            mseat += ".";
                        }
                        else if (i == 3)
                        {
                            mseat += "D";
                            mseat += std::to_string(j);
                            mseat += ".";
                        }
                        else if (i == 4)
                        {
                            mseat += "E";
                            mseat += std::to_string(j);
                            mseat += ".";
                        }
                        else
                        {
                            mseat += "F";
                            mseat += std::to_string(j);
                            mseat += ".";
                        }
                    }
            if (mlocal == "MVIP")
                mtotal += 250000 * mrnum;
            else if (mlocal == "VIP")
                mtotal += 150000 * mrnum;
            else if (mlocal == "GOLD")
                mtotal += 100000 * mrnum;
            else
                mtotal += 70000 * mrnum;
            return 0;
        default:
            break;
        }
        Page_R_seat();
    }
}

void MainPage::Page_purchase()
{
    cout << mzone << "\n"
         << "구역: " << mlocal << "\n"
         << "좌석: " << mseat << "\n"
         << "인원수: " << mrnum << std::endl
         << "가격: " << mtotal << std::endl
         << "----------------------------------------------------\n";
    for (int i = 0; i < 4; i++)
        switch (mpurchse[i])
        {
        case 1:
            cout << "  결제";
            break;
        case 2:
            cout << "  취소\n";
            break;
        case 99:
            cout << "   ▶ ";
            break;
        default:
            cout << "     ";
            break;
        }
}

int MainPage::Page_purchase_move(const User &player)
{
    int xpos, temp, key;
    std::ofstream Outlist;
    while (1)
    {
        for (int i = 0; i < 4; i++)
            if (mpurchse[i] == 99)
                xpos = i;
        key = getch();
        system("clear");
        switch (key)
        {
        case 67:
            if (xpos != 2)
            {
                temp = mpurchse[xpos];
                mpurchse[xpos] = mpurchse[xpos + 2];
                mpurchse[xpos + 2] = temp;
            }
            break;
        case 68:
            if (xpos != 0)
            {
                temp = mpurchse[xpos];
                mpurchse[xpos] = mpurchse[xpos - 2];
                mpurchse[xpos - 2] = temp;
            }
            break;
        case 10:
            if (xpos == 0)
            {
                Outlist.open(player.mnum, std::ios::app);
                Outlist << mzone << "\n"
                        << mlocal << "\n"
                        << mseat << "\n"
                        << mrnum << std::endl
                        << mtotal << std::endl
                        << rand() << std::endl;
                Outlist.close();
                Outlist.open("StadiumPos", std::ios::app);
                Outlist << mzone << mseat << std::endl;
                Outlist.close();
                mseat = "";
                mtotal = 0;
                mrnum = 0;
                return 1;
            }
            mtotal = 0;
            mrnum = 0;
            return 0;
            break;
        default:
            break;
        }
        Page_purchase();
    }
}

void MainPage::Seat_reset()
{
    std::ifstream Inlist("StadiumPos");
    char c1, c2;
    char check[5];
    std::string pos;
    int i, j, pc = 0;
    while (getline(Inlist, pos, '.'))
    {
        if (!pos.find("2024") || !pos.find("\n2024"))
        {
            if (pos[0] == '\n')
                pos.erase(0, 1);
            pos += '.';
            if (pos.compare(mzone) == 0)
            {
                pc = 1;
                continue;
            }
            else
                pc = 0;
        }
        if (pc == 1)
        {
            for (i = 0; i < 6; i++)
            {
                c1 = i + 65;
                if (!pos.find(c1))
                    break;
            }
            for (j = 1; j < 10; j++)
            {
                c2 = j + 48;
                check[0] = c1;
                check[1] = c2;
                check[2] = '\0';
                if (!pos.find(check))
                    break;
            }
            if (j != 10 && pc == 1)
            {
                mstadium[i][j] = 77;
            }
        }
    }
    Inlist.close();
}

void MainPage::Seat_Freset()
{
    std::copy(&mstadium_rst[0][0], &mstadium_rst[0][0] + 54, &mstadium[0][0]);
}

void MainPage::Show_reserve(const User &player)
{
    std::string one;
    std::ifstream Inlist(player.mnum);
    int count = 0;
    while (getline(Inlist, one))
    {
        switch (count)
        {
        case 0:
            cout << "경기 : " << one << std::endl;
            count++;
            break;
        case 1:
            cout << "구역 : " << one << std::endl;
            count++;
            break;
        case 2:
            cout << "좌석 : " << one << std::endl;
            count++;
            break;
        case 3:
            cout << "인원 : " << one << std::endl;
            count++;
            break;
        case 4:
            cout << "가격 : " << one << std::endl;
            count++;
            break;
        case 5:
            cout << "예매번호 : " << one << std::endl;
            count = 0;
            break;
        default:
            break;
        }
    }
    Inlist.close();
    cout << "------------------------------------------------\n";
    cout << "(아무키나 누르시면 나가집니다.)\n";
    std::cin.get();
}