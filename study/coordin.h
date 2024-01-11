#ifndef COORDIN_H_
#define COORDIN_H_
struct carcul
{
    int sum;
    int mlt;
};
struct base
{
    int a;
    int b;
};

carcul ab_to_cal(base abpos);
void show_calcul(carcul pos);

#endif
