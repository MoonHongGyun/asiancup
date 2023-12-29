#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <string>
#include <array>

using namespace std;

// PDF 예제문제
//  int main()
//  {
//      cout << "C++의 세계로 오십시오.";
//      cout << endl;
//      cout << "후회하지 않으실 겁니다." << endl;
//      return 0;
//  }

// int main()
// {
//     int carrots;

//     carrots = 25;
//     cout << "나는 당근을 "
//          << carrots
//          << "개 갸지고 있다."
//          << endl;
//     carrots = carrots - 1;
//     cout << "아삭아삭, 이제당근은 " << carrots << "개이다." << endl;
//     return 0;
// }

// int main()
// {
//     int carrots;

//     cout << "당근을 몇 개나 가지고 있나?" << endl;
//     cin >> carrots;
//     cout << "여기 두 개가 더있다.";
//     carrots = carrots + 2;
//     cout << "이제 당근은 모두 " << carrots << "개이다." << endl;
//     return 0;
// }

// int main()
// {
//     double area;
//     cout << "마루 면적을 평방피트 단위로 입력하시오: ";
//     cin >> area;
//     double side;
//     side = sqrt(area);
//     cout << "사각형 마루라면 한변이" << side
//          << "피트에 상당합니다." << endl;
//     cout << "멋지네요!" << endl;
//     return 0;
// }

// void simon(int n);
// int main()
// {
//     simon(3);
//     cout << "정수를 하나 고르시오: ";
//     int count;
//     cin >> count;
//     simon(count);
//     cout << "끝!" << endl;
//     return 0;
// }

// void simon(int n)
// {
//     cout << "simon 왈, 발가락을 " << n << "번 두드려라." << endl;
// }

// int stonetolb(int sts);
// int main()
// {
//     int stone;
//     cout << "체중을 스톤 단위로 입력하시오.: ";
//     cin >> stone;
//     int pounds = stonetolb(stone);
//     cout << stone << " 스톤은 " << pounds << " 파운드 입니다." << endl;
//     return 0;
// }

// int stonetolb(int sts)
// {
//     return 14 * sts;제
// }

// PDF 프로그래밍 연습문제
// int main()
// {
//     cout << "이름" << endl;
//     cout << "주소" << endl;
// }

// double km(double mile);
// int main()
// {
//     double mile;
//     cout << "마일 단위로 입력해주세요.: ";
//     cin >> mile;
//     cout << mile << "마일은 " << km(mile) << "킬로미터 입니다." << endl;
// }

// double km(double mile)
// {
//     return mile * 1.60934;
// }

// void mice();
// void run();
// int main()
// {
//     mice();
//     mice();
//     run();
//     run();
// }

// void mice()
// {
//     cout << "Three blind mice" << endl;
// }

// void run()
// {
//     cout << "See how they run" << endl;
// }

// int main()
// {
//     string name;
//     cout << "이름을 입력하세요.: ";
//     cin >> name;
//     int age;
//     cout << "나이를 입력하세요.: ";
//     cin >> age;
//     cout << name << "의 나이를 월로 나타낼 경우" << age * 12 << "입니다." << endl;
//     return 0;
// }

// double f(double c);
// int main()
// {
//     double c;
//     cout << "섭씨온도를 입력하세요.: ";
//     cin >> c;
//     cout << "섭씨" << c << "도는 화씨로" << f(c) << "도 입니다." << endl;
// }

// double f(double c)
// {
//     return c * 1.8 + 32;
// }

// double cheonmun(int d);
// int main()
// {
//     double distance;
//     cout << "광년 단위로 입력하세요.: ";
//     cin >> distance;
//     cout << distance << "광년은 " << cheonmun(distance) << "천문단위 이다." << endl;
//     return 0;
// }

// double cheonmun(int d)
// {
//     return d * 63240;
// }

// void result(int h, int m);
// int main()
// {
//     int hour, minute;
//     cout << "시간을 입력하세요.: ";
//     cin >> hour;
//     cout << "분을 입력하세요.: ";
//     cin >> minute;
//     result(hour, minute);
// }

// void result(int h, int m)
// {
//     cout << "시각: " << h << ":" << m << endl;
// }

// cout.self(ios_base:fixed, ios_bas::floatfield)

// // 3-1
// #define M 100

// int main()
// {
//     int cm;
//     cout << "키를 센티미터 단위로 입력하세요.:___\b\b\b";
//     cin >> cm;
//     cout << "키는 " << cm / M << "미터 " << cm % M << "센티미터 입니다." << endl;
//     return 0;
// }

// // 3-2
// #define ft 12
// #define M 0.0254
// #define KG 0.45359237
// int main()
// {
//     double feet, inch, pound;
//     cout << "키를 피트와 인치단위로 입력하시오.: ";
//     cin >> feet >> inch;
//     cout << "체중을 파운드 단위로 입력하시오.: ";
//     cin >> pound;
//     cout << "BMI의 수치는 " << (pound * KG) / (((feet * ft + inch) * M) * ((feet * ft + inch) * M)) << " 입니다." << endl;
//     return 0;
// }

// // 3-3
// #define one_m 60
// #define one_a 60
// int main()
// {
//     double a, m, s;
//     cout << "위도를 도, 분, 초 단위로 입력하시오.: ";
//     cin >> a >> m >> s;
//     cout << a << "도, " << m << "분, " << s << "초 = " << a + (m / one_a) + (s / (one_a * one_m)) << "도" << endl;
//     return 0;
// }

// // 3-4
// #define time 60
// #define day 24

// int main()
// {
//     long sec;
//     cout << "초를 입력하세요.: ";
//     cin >> sec;
//     cout << sec << "초 = " << sec / (time * time * day) << "일, " << (sec % (time * time * day)) / (time * time) << "시간, " << ((sec % (time * time * day)) % (time * time)) / time << "분, " << (((sec % (time * time * day)) % (time * time)) % (time * time)) % time << "초" << endl;
//     return 0;
// }

// // 3-5

// int main()
// {
//     long long world, america;
//     cout << "세계 인구수를 입력하시오.: ";
//     cin >> world;
//     cout << "미국의 인구수를 입력하시오.: ";
//     cin >> america;
//     cout << "세계 인구수에서 미국이 차지하는 비중은 " << (america / (long double)world) * 100 << "%이다." << endl;
//     return 0;
// }

// // 3-6

// int main()
// {
//     double KM, L;
//     cout << "주행한 거리를 킬로미터단위로 입력하세요.: ";
//     cin >> KM;
//     cout << "소비한 기름을 리터단위로 입력하세요.: ";
//     cin >> L;
//     cout << "100km당 사용한 l수는 " << (L / KM) * 100 << "입니다." << endl;
//     return 0;
// }

// // 3-7
// #define mile 62.14
// #define gallon 3.875
// int main()
// {
//     double L;
//     cout << "100킬로미터당 리터수를 입력하세요.: ";
//     cin >> L;
//     cout << L << "liter/100km = " << int(mile / (L / gallon)) << "mpg이다." << endl;
//     return 0;
// }

// #define BUF_SIZE 20
// int main()
// {
//     char name1[BUF_SIZE];
//     char name2[BUF_SIZE];
//     cin.get(name1, BUF_SIZE).get();
//     cin >> name2;
//     cout << name1 << name2 << endl;
//     return 0;
// }

// struct info
// {
//     int num;
// };

// int main()
// {
//     info user, user2;
//     cin >> user.num;
//     user2 = user;
//     cout << user2.num << endl;
// }

// int main()
// {
//     enum spectrum
//     {
//         red = 5,
//         blue = 10
//     };
//     spectrum band;
//     int color;
//     color = red + blue;
//     cout << band << endl;
//     return 0;
// }

// int main()
// {
//     int *ps = new int;
//     int jug = 5;
//     ps = &jug;
//     delete ps;
//     cout << *ps << endl;
//     return 0;
// }

// struct info
// {
//     int year;
// };

// int main()
// {
//     info s01, s02, s03;
//     const info *ars[3] = {&s01, &s02, &s03};
//     s03.year = 2002;
//     cout << ars[2]->year << endl;
//     const info **arss = ars;
//     cout << (*arss + 2)->year << endl;
// }

// // 4-1
// struct info
// {
//     char first_name[20];
//     char last_name[10];
//     char cd;
//     int age;
// };
// int main()
// {
//     int credit;
//     info student;
//     cout << "영문 퍼스트 네임(이름) : ";
//     cin.get(student.first_name, 20).get();
//     cout << "영문 라스트 네임(성) : ";
//     cin >> student.last_name;
//     cout << "학생이 원하는 학점 : ";
//     cin >> student.cd;
//     credit = (int)student.cd;
//     cout << "나이: ";
//     cin >> student.age;
//     cout << "성명: " << student.last_name << ", " << student.first_name << endl;
//     cout << "학점: " << char(credit + 1) << endl;
//     cout << "나이: " << student.age << endl;
//     return 0;
// }

// // 4-2

// int main()
// {
//     string name, dessert;
//     cout << "이름을 입력하십시오:";
//     getline(cin, name);
//     cout << "좋아하는 디저트를 입력하십시오:";
//     getline(cin, dessert);
//     cout << "맛있는 " << dessert << "를 준비했습니다. " << name << "님\n"
//          << endl;
//     return 0;
// }

// // 4-3

// int main()
// {
//     const int NAME = 30;
//     char f_name[NAME];
//     char l_name[NAME];
//     char name[NAME];
//     cout << "퍼스트 네임(이름)을 입력하시오: ";
//     cin.get(f_name, NAME).get();
//     cout << "라스트 네임(성)을 입력하시오: ";
//     cin >> l_name;
//     strcpy(name, l_name);
//     strcat(name, ", ");
//     strcat(name, f_name);
//     cout << "하나의 문자열을 만들면: " << name << endl;
// }

// // 4-4

// int main()
// {
//     string f_name,l_name,name;
//     cout << "퍼스트 네임(이름)을 입력하시오: ";
//     getline(cin,f_name);
//     cout << "라스트 네임(성)을 입력하시오: ";
//     cin >> l_name;
//     name = l_name + ", "+f_name;
//     cout << "하나의 문자열을 만들면: " << name << endl;
//     return 0;
// }

// // 4-5

// struct CandyBar
// {
//     char title[20];
//     double kg;
//     int kcal;
// };

// int main()
// {
//     CandyBar snack{"Mocha Munch", 2.3, 350};
//     cout << snack.title << endl;
//     cout << snack.kg << endl;
//     cout << snack.kcal << endl;
// }

// // 4-6
// struct CandyBar
// {
//     char title[20];
//     double kg;
//     int kcal;
// };

// int main()
// {
//     CandyBar snack1{"snack1", 1.1, 15}, snack2{"snack2", 2.2, 20}, snack3{"snack3", 3.3, 25};
//     CandyBar snack[3] = {snack1, snack2, snack3};
//     cout << snack1.title << "," << snack1.kg << "," << snack1.kcal << endl;
//     cout << snack2.title << "," << snack2.kg << "," << snack2.kcal << endl;
//     cout << snack3.title << "," << snack3.kg << "," << snack3.kcal << endl;
// }

// // 4-7

// struct TCL
// {
//     char name[30];
//     int diameter;
//     int kg;
// };
// int main()
// {
//     TCL pizza;
//     cout << "피자 회사의 이름을 입력하세요.: ";
//     cin.get(pizza.name, 30).get();
//     cout << "피자의 지름을 입력하세요.: ";
//     cin >> pizza.diameter;
//     cout << "피자의 중량을 입력하세요.: ";
//     cin >> pizza.kg;
//     cout << "회사는 " << pizza.name << "지름은 " << pizza.diameter << "중량은 " << pizza.kg << endl;
//     return 0;
// }

// // 4-8

// struct TCL
// {
//     char name[30];
//     int diameter;
//     int kg;
// };
// int main()
// {
//     TCL *pt = new TCL;
//     cout << "피자의 지름을 입력하세요.: ";
//     cin >> pt -> diameter;
//     cout << "피자 회사의 이름을 입력하세요.: ";
//     cin.get(pt -> name, 30).get();
//     cout << "피자의 중량을 입력하세요.: ";
//     cin >> (*pt).kg;
//     cout << "회사는 " << (*pt).name << "지름은 " << (*pt).diameter << "중량은 " << (*pt).kg << endl;
//     return 0;
// }

// 4-10
int main()
{
    array<int, 3> run;
    cout << "40야드 달리기 첫번째결과: ";
    cin >> run[0];
    cout << "40야드 달리기 두번째결과: ";
    cin >> run[1];
    cout << "40야드 달리기 세번째결과: ";
    cin >> run[2];
    cout << "40야드 3회 평균" << (run[0] + run[1] + run[2]) / 3 << "입니다." << endl;
    return 0;
}