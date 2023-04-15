#include<stdio.h>
#include<stdlib.h>
#include <complex.h>
#define _USE_MATH_DEFINES
#include <math.h>
double abs1(double x)
{
    if (x<0)
        return -x;
    return x;
}


double xx,yy,spanx,spany,r,tetha,unit,test;
double len(double complex z)
{
    return pow(pow(cimagf(z),2)+pow(crealf(z),2),0.5);
}
int mandel(double complex c,int max_iter)
{
    double complex z = 0.0 + 0.0*I;
    double size = len(z);
    int i=0;
    while (size < 4.0 && i < max_iter)
    {
        z =z*z +c;
        i+=1;
        size = len(z);
    }
    return i;
}
double xx,yy;
double complex c;
int iter;
void nothing(int max_iter, double maxx,double maxy,double minx,double miny)
{
    printf("done1\n");
    double x_pixelunit = (maxx - minx) / 1800;
    double y_pixelunit = (maxy-miny) / 900;
    for(int x;x<1800;x++)
    {
        printf("done2\n");
        for(int y;y<900;y++)
        {
            printf("done3\n");
            xx = minx +x*x_pixelunit;
            yy = miny +y*y_pixelunit;
            printf("done4\n");
            c = xx + yy*I;
            printf("done5\n");
            iter = mandel(c,max_iter);
            printf("done6\n");

        }
    }
}
void rotating(int max_iter, double maxx,double maxy,double minx,double miny,int max_deg)
{

    for(int k = 0;k<max_deg;k++)  
    {
        double x_pixelunit = (maxx - minx) / 1800;
        double y_pixelunit = (maxy-miny) /900;
        // printf("1\n");
        xx = 1.0;
        yy = 1.0;
        for(int y = 0;y<900;y++)
        {
            
            for(int x = 0;x<1799;x++)
            {
                // printf("2\n");
                xx = minx +x*x_pixelunit;
                yy = miny +y*y_pixelunit;
                r = pow(((pow(xx,2)+pow(yy,2))),0.5);
                unit = (k/9)* M_PI;
                // printf("3\n");
                if (xx<0 && yy<0)
                    tetha = M_PI + atan(yy/xx);
                if (xx<0 && yy>0)
                    tetha = M_PI - abs1(atan(yy/xx));
                if (xx>0 && yy<0)
                    tetha = 2*M_PI - abs1(atan(yy/xx));
                else
                    tetha = atan(yy/xx);
                // printf("4\n");
                xx = r*(cos(tetha));
                yy = r*(sin(tetha));
                c = xx + yy*I;
                // printf("5\n");
                iter = mandel(c,max_iter);
                
                if (iter < max_iter)
                {
                    test =1.0;
                    
                }
                else
                {
                    // printf("god is somewhere near\n");
                    test =2.0;
                    
                }

            }
        }
    }
}
int main()
{
    printf("%.5f", pow(-0.000021,2));
    double cx = -0.74384935657398;
    double cy = -0.13170134084746293;
    double minx = -0.74384935657398 - 1.5;
    double maxx = -0.74384935657398 + 1.5;
    double miny = -0.13170134084746293 - 1.5;
    double maxy = -0.13170134084746293 + 1.5;
    int max_iter = 88;
    int max_deg = 10;
    nothing(max_iter,maxx,maxy,minx,miny);
    rotating( max_iter,  maxx, maxy, minx, miny, max_deg);

}