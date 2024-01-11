#include <iostream>
#include <cmath>
#include "coordin.h"

using namespace std;

int main()
{
    base one;
    carcul car_one;

    cout << "정수 두개를 입력하세으.: ";
    cin >> one.a >> one.b;

    car_one = ab_to_cal(one);
    show_calcul(car_one);

    return 0;
}

carcul ab_to_cal(base abpos)
{
    carcul two;
    two.sum = abpos.a + abpos.b;
    two.mlt = abpos.a * abpos.b;

    return two;
}

void show_calcul(carcul poss)
{
    cout << "두 정수의 합은" << poss.sum << " 두 정수의 곱은 " << poss.mlt << " 이다." << endl;
}