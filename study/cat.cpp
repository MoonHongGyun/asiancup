#include <iostream>
#include "cat.h"

Stock::Stock()
{
    std::cout << "call in default creater.\n";
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const std::string &co, long n, double pr)
{
    std::cout << "call in" << co << " using creater.\n";
    company = co;

    if (n < 0)
    {
        std::cout << "stock isn't a negative quantity, "
                  << company << " shares setup 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}

Stock::~Stock()
{
    std::cout << "Bye, " << company << "!\n";
}

void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        std::cout << "the number of stocks purchased cannot be negative, "
                  << "the transaction has been cancled.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if (num < 0)
    {
        cout << "the number of stocks selling cannot be negative, "
             << "the transaction has been cancled.\n";
    }
    else if (num > shares)
    {
        cout << "You can't sell more shares than you hold, "
             << "the transaction has been cancled.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show()
{
    using std::cout;
    using std::ios_base;
    ios_base::fmtflags orig =
        cout.setf(ios_base::fixed, ios_base::floatfield);
    std::streamsize prec = cout.precision(3);

    cout << "company: " << company
         << "the number of shares: " << shares << "\n";
    cout << "stock price: $" << total_val << '\n';

    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}