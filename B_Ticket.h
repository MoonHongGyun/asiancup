#ifndef B_TICKET_H_
#define B_TICKET_H_

#include <iostream>

class Start
{
private:
    int page1[5][2] = {{99, 1},
                       {0, 2},
                       {0, 3},
                       {0, 4},
                       {0, 5}};

public:
    void Map();
    int Move();
    int getch();
};

class User
{
private:
    // char id[30];
    // char email[30];
    // char pw[30];
    // char pnum[30];

public:
    char id[30];
    char email[30];
    char pw[30];
    char pnum[30];
    std::string mnum;
    User();
    // User(char u_id[30], int u_pw, char u_email[30], int u_pnum);
    void Membership();
    int Login();
    void Find_ID();
    void Find_PW();
    int getch();
};

class MainPage
{
private:
    std::string mlocal, mseat, mzone, mday = "2024 01 13";
    int mtotal;
    int mrnum;
    int main_p1[8][2] = {{99, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}};
    int plan_arr[3][2] = {{99, 1}, {0, 2}, {0, 3}};
    int Gplan_arr[14] = {99, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7};
    int mrday[4] = {99, 1, 0, 2};
    int mrday_count = 13;
    int mstadium_rst[6][9] = {{99, 4, 4, 3, 3, 3, 3, 4, 4},
                              {0, 4, 4, 1, 1, 1, 1, 4, 4},
                              {0, 2, 1, 0, 0, 0, 0, 1, 2},
                              {0, 2, 1, 0, 0, 0, 0, 1, 2},
                              {0, 4, 4, 1, 1, 1, 1, 4, 4},
                              {0, 4, 4, 3, 3, 3, 3, 4, 4}};
    int mstadium[6][9] = {{99, 4, 4, 3, 3, 3, 3, 4, 4},
                          {0, 4, 4, 1, 1, 1, 1, 4, 4},
                          {0, 2, 1, 0, 0, 0, 0, 1, 2},
                          {0, 2, 1, 0, 0, 0, 0, 1, 2},
                          {0, 4, 4, 1, 1, 1, 1, 4, 4},
                          {0, 4, 4, 3, 3, 3, 3, 4, 4}};
    int zone_arr[10] = {99, 1, 0, 2, 0, 3, 0, 4, 0, 5};
    int mrgame[10] = {99, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int mragame_count;
    int mpurchse[4] = {99, 1, 0, 2};

public:
    void Page_1();
    int P1_Move();
    int getch();
    void Page_plan(int n = 0);
    int Page_plan_move(int n);
    void Page_Gplan(int n);
    int Page_Gplan_move(int n);
    void Page_country();
    void Page_playerlist();
    void Page_info();

    void Page_R_day(int n = 0);
    int Page_R_day_move();
    int Page_R_day_move2();

    void Page_R_zone();
    int Page_R_zone_move();

    void Page_R_seat();
    int Page_R_seat_move();

    void Page_purchase();
    int Page_purchase_move(const User &player);

    void Seat_reset();
    void Seat_Freset();

    void Show_reserve(const User &player);
};

#endif
