#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <array>
#include <unistd.h>

using namespace std;
// void change_p(int *num, int turn);
// int main()
// {
//     const int sun_size = 7;
//     int sun[sun_size][sun_size] = {0};
//     int vertical = 2;
//     int turn = 0;
//     int *psun;
//     int *psun_next;
//     int *psun_last;
//     while (turn < 7)
//     {
//         if (turn < 7)
//             system("clear");
//         // 전값 복사
//         for (int i = 0; i < sun_size - 1; i++)
//         {
//             for (int j = 0; j < sun_size; j++)
//             {
//                 int *psun = &sun[i][j];
//                 int *psun_next = &sun[i + 1][j];
//                 *psun = *psun_next;
//             }
//         }
//         // 마지막열
//         if (turn == 0 || turn == 6)
//         {
//             for (int i = 0; i < 7; i++)
//             {
//                 int *psun_last = &sun[6][i];
//                 *psun_last = 0;
//             }
//             for (int k = 2; k < 5; k++)
//             {
//                 int *psun_last = &sun[6][k];
//                 *psun_last = 1;
//             }
//         }
//         else if (turn == 1 || turn == 5)
//         {
//             for (int i = 0; i < 7; i++)
//             {
//                 int *psun_last = &sun[6][i];
//                 *psun_last = 0;
//             }
//             for (int k = 1; k < 6; k++)
//             {
//                 int *psun_last = &sun[6][k];
//                 *psun_last = 1;
//             }
//         }
//         else
//             for (int k = 0; k < 7; k++)
//             {
//                 int *psun_last = &sun[6][k];
//                 *psun_last = 1;
//             }
//         // map print
//         for (int i = 0; i < sun_size; i++)
//         {
//             for (int j = 0; j < sun_size; j++)
//             {
//                 if (sun[i][j] == 0)
//                     cout << "  ";
//                 else
//                     cout << "🟧";
//             }
//             cout << endl;
//         }
//         turn++;
//         sleep(1);
//     }
//     cout << "  2024 갑진년" << endl;
// }
