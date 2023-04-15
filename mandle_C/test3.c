#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex.h>

double abs1(double x)
{
    if (x<0)
        return -x;
    return x;
}
void xcx(int name)
{
    char p = '9';
    int t= 0;
    int y = 1;
    int count = 3;
    char ct[9];
    char* cp = ".bmp";
    for(int kk = 0 ; kk < 8 ; kk++)
        ct[kk] = 0;  
    while (count !=-1)
    {
        t = (int)(name/pow(10,count));
        ct[y] = (char)t;
        name -= t*pow(10,count);
        count -=1;
        y +=1;
    }   
    for(int p = 4;p<8;p++)
    {
        ct[p] = cp[p-4];
        ct[p+1] = 0;
    }
}
int main()
{
    int x = 10;
    if (x<0)
        x+=2;
    if (x>0 && x<5)
        x+=3;
    if (x>5 && x<11)
        x+=4;
    else
        x+=5;
    double ui = 2.35321;
    ui -=1;
    xcx(6);

    // int s;
    // scanf("%d", &s);
    // printf("%d",s);
    printf("%f\n\n",acos(pow(3,0.5)/2)*180/M_PI);
    printf("%f\n",abs1(-2.16532));
    printf("%f",ui);
}