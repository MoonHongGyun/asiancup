#include <iostream>
#include "cat.h"

int main()
{
    {
        using std::cout;
        cout << "Create new objects using creater.\n";
        Stock stock1("NanoSmart", 12, 20.0);
        stock1.show();
        Stock stock2 = Stock("Boffo Objects", 2, 2.0);
        stock2.show();

        cout << "stock1 substitude stock2.\n";
        stock2 = stock1;
        cout << "Print stock1 and stock2.\n";
        stock1.show();
        stock2.show();

        cout << "Reset object using creater.\n";
        stock1 = Stock("Nifty Fooda", 10, 50.0);
        cout << "renewed stock1:\n";
        stock1.show();
        cout << "End the program.\n";
    }
    return 0;
}