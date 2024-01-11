#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    int pass = 0;
    int check_count = 0;
    int cp = 1;
    int big = 0, small = 0, special = 0;
    int limit = 0;
    char email[30] = {
        0,
    };
    char pnum[30];
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
        cout << limit << std::endl;
        cout << special << std::endl;
        cout << strlen(pnum) << std::endl;
    }
}
dddd