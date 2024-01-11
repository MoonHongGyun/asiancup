#include <iostream>
#include <fstream>
#include <termios.h>
#include <cstring>
#include "B_Ticket.h"

using namespace std;

int main()
{
    int back;
    Start start;
    // start.Map();
    while (1)
    {
        system("clear");
        start.Map();
        User user;
        back = 0;
        // // cout << start.Move();
        switch (start.Move())
        {
        case 0:
            user.Membership();
            break;
        case 1:
            if (user.Login() == 1)
            {
                MainPage mp;
                while (back == 0)
                {
                    system("clear");
                    mp.Page_1();
                    int n, m;
                    switch (mp.P1_Move())
                    {
                    case 0:
                        mp.Page_plan();
                        m = 0;
                        while (1)
                        {
                            n = mp.Page_plan_move(m);
                            if (n == 2)
                                break;
                            else if (n == 1)
                            {
                                if (m == 0)
                                    m = 0;
                                else
                                    m--;
                            }
                            else
                                m++;
                            mp.Page_plan(m);
                        }
                        break;
                    case 1:
                        m = 0;
                        mp.Page_Gplan(0);
                        while (1)
                        {
                            n = mp.Page_Gplan_move(m) - 1;
                            if (n == 6)
                                break;
                            m = n;
                            mp.Page_Gplan(m);
                        }
                        break;
                    case 2:
                        mp.Page_country();
                        cin.get();
                        break;
                    case 3:
                        mp.Page_playerlist();
                        cin.get();
                        break;
                    case 4:
                        mp.Page_info();
                        cin.get();
                        break;
                    case 5:
                        mp.Page_R_day();
                        while (1)
                        {
                            if (mp.Page_R_day_move() == 0)
                                break;
                            mp.Seat_Freset();
                            mp.Page_R_zone();
                            if (mp.Page_R_zone_move() == 0)
                                break;
                            mp.Seat_reset();
                            mp.Page_R_seat();
                            mp.Page_R_seat_move();
                            mp.Page_purchase();
                            if (mp.Page_purchase_move(user) < 2)
                                break;
                        }
                        break;
                    case 6:
                        mp.Show_reserve(user);
                        break;
                    case 7:
                        back = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        case 2:
            user.Find_ID();
            break;
        case 3:
            user.Find_PW();
            break;
        case 4:
            exit(1);
        default:
            break;
        }
    }
}