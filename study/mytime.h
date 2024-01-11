#ifndef MYTIME_H_
#define MYTIME_H_

class Time
{
private:
    int hours;
    int minutes;

public:
    Time();
    Time(int h, int m = 0);
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h = 0, int m = 0);
    Time operator+(const Time &t) const; // 멤버함수
    // friend Time operator+(const Time &t) const; //멤버함수와 동급인 권한을 가지고있는 맴버가 아닌 함수
    void Show() const;
};

#endif