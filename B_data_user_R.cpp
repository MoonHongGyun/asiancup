#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream Outlist;
    Outlist.open("userIDdata");
    Outlist.close();
    Outlist.open("userPWdata");
    Outlist.close();
    Outlist.open("userEMAILdata");
    Outlist.close();
    Outlist.open("userPNUMdata");
    Outlist.close();
    Outlist.open("userMNUMdata");
    Outlist.close();
    Outlist.open("StadiumPos");
    Outlist.close();
}