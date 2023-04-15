#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <imagedefs.h>

int width = 1800;
int height = 1200;

double cx = -0.74384935657398;
double cy = -0.13170134084746293;
double minx = -0.74384935657398 - 1.5;
double maxx = -0.74384935657398 + 1.5;
double miny = -0.13170134084746293 - 1.5;
double maxy = -0.13170134084746293 + 1.5;
int save_file(    BITMAPINFOHEADER* pInfoHeader,
    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,unsigned char* pImageData 
    ,int iter)
{
        for(int j=0;j<iter;j++)
    {    
        char cc[20] = "a.bmp";
        cc[0] = 48+j;
            FILE* pFile = fopen(cc, "wb");
            if (NULL == pFile)
            {
                printf("Error man");
                return 1;
            }

        fwrite(pFileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
        fwrite(pInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
        fwrite(pColorIdx, sizeof(COLORINDEX)*256, 1, pFile);
        fwrite(pImageData, pInfoHeader->biSizeImage, 1, pFile);
        fclose(pFile);
       
    }
    return 0;
}
double xx,yy;
int iter;
int value;
double complex c;
double len(double complex z)
{
    return pow((pow(creal(z),2)+pow(cimag(z),2)),0.5);
}
int mandel(double c,int max_iter)
{
    double complex z = 0+0*I;
    int i=0;
    while (len(z) <=4 && i <max_iter)
        z =z*z +c;
        i+=1;
    return i;
}
void draw_mandle(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader, int max_iter, double maxx,double maxy,double minx,double miny)
{


    double x_pixelunit = (maxx - minx) / pInfoHeader->biWidth;
    double y_pixelunit = (maxy-miny) / pInfoHeader->biHeight;
    for(int x;x<pInfoHeader->biWidth;x++)
    {
        for(int y;y<pInfoHeader->biHeight;y++)
        {
            xx = minx +x*x_pixelunit;
            yy = miny +y*y_pixelunit;
            c = xx + yy*I;
            iter = mandel(c,max_iter);
            if (iter < max_iter)
                pImageData[x+y] = 2;
            else
                pImageData[x+y] = 1;

        }
    }
}
void main()
{
    BITMAPINFOHEADER InfoHeader;
    BITMAPFILEHEADER FileHeader;
    COLORINDEX ColorIdx[256];
    unsigned char * pImageData = init_image_data( &InfoHeader, &FileHeader, ColorIdx);
    memset(pImageData, 0, InfoHeader.biSizeImage);
        int y = 600;
        int c = 6;

        int x = 898;
        int c2=4;
    // draw_vertical_line
    //         (pImageData,
    //     &InfoHeader, 898, 4);
    // draw_horizontal_line
    //         (pImageData,
    //             &InfoHeader, 600, 6);
    double cx = -0.74384935657398;
    double cy = -0.13170134084746293;
    double minx = -0.74384935657398 - 1.5;
    double maxx = -0.74384935657398 + 1.5;
    double miny = -0.13170134084746293 - 1.5;
    double maxy = -0.13170134084746293 + 1.5;
    int max_iter = 88;
    draw_mandle(pImageData,&InfoHeader,max_iter, maxx,maxy,minx, miny);
    save_file(&InfoHeader, &FileHeader, ColorIdx, pImageData, 6);
}
