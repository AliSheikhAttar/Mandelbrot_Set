#include "imagedefs.h"
#include <complex.h>
#define _USE_MATH_DEFINES
#include <math.h>
unsigned char* init_image_data(
    BITMAPINFOHEADER* pInfoHeader,
    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx 
)
{
    unsigned int headerSize = 
        sizeof(BITMAPFILEHEADER) + 
        sizeof(BITMAPINFOHEADER) + 
        sizeof(COLORINDEX) * 256;

    
    memset(pInfoHeader, 0, sizeof(BITMAPINFOHEADER));
    pInfoHeader->biWidth = 1800;
    pInfoHeader->biHeight = 1200;
    pInfoHeader->bisize = 40;
    pInfoHeader->biPlanes = 1;
    pInfoHeader->biBitCount = 8;
    pInfoHeader->biSizeImage = pInfoHeader->biWidth * pInfoHeader->biHeight;


    memset(pFileHeader, 0, sizeof(BITMAPFILEHEADER));
    pFileHeader->bfType = (((unsigned short)'M')<<8) | 'B';
    pFileHeader->bfSize = headerSize + pInfoHeader->biSizeImage;
    pFileHeader->bfoffBits = headerSize;



    memset(pColorIdx, 0, sizeof(COLORINDEX)*256);
    pColorIdx[0].r = 181;

    pColorIdx[1].g = 224;

    pColorIdx[2].b = 181;

    pColorIdx[3].r = 80;
    pColorIdx[3].g = 16;
    pColorIdx[3].b = 199;

    pColorIdx[4].r = 230;
    pColorIdx[4].b = 164;

    pColorIdx[5].r = 211;
    pColorIdx[5].g = 230;

    pColorIdx[6].b = 0;



    unsigned char * pImageData = (unsigned char*) malloc(pInfoHeader->biSizeImage);
    memset(pImageData, 0, pInfoHeader->biSizeImage);
    
    return pImageData;
}

void draw_horizontal_line
            (unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader, int y, int c)
{
    for (int l = 0; l < c; l++)
    {
        for (int i = 0; i < pInfoHeader->biWidth; i++)
        {
            pImageData[(y + l) * pInfoHeader->biWidth + i] = 1;
        }
    }
}
void draw_vertical_line
            (unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader, int x, int c)
{
    for (int i = 0; i < pInfoHeader->biHeight; i++)
    {
        for (int l = 0; l < c; l++)
        {
            pImageData[i * pInfoHeader->biWidth + x + l] = 2;
        }
    }
}

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
                printf("error");
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

int save_file1(    BITMAPINFOHEADER* pInfoHeader,
    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,unsigned char* pImageData 
    ,int name)
{
    int count = 2;
    int t;
    int y = 0;
    char ct[9] = "000.bmp";
    while (count !=-1)
    {
        t = (int)(name/pow(10,count));
        ct[y] = 48+t;
        name -= t*pow(10,count);
        count -=1;
        y +=1;
    }   
    FILE *pFile = fopen(ct, "wb");
    if (NULL == pFile)
    {
        printf("error");
        return 1;
    }

    fwrite(pFileHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
    fwrite(pInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);
    fwrite(pColorIdx, sizeof(COLORINDEX) * 256, 1, pFile);
    fwrite(pImageData, pInfoHeader->biSizeImage, 1, pFile);
    fclose(pFile);

    return 0;
}

int width = 1800;
int height = 1200;

double cx = -0.74384935657398;
double cy = -0.13170134084746293;


double xx,yy,spanx,spany,r,tetha,unit;
int iter,value;
double complex c;
double len(double complex z)
{
    return pow((pow(crealf(z),2)+pow(cimagf(z),2)),0.5);
}
int mandel(double complex c,int max_iter)
{
    double complex z = 0.0 + 0.0*I;
    double size = len(z);
    int i=0;
    while (size < 16.0 && i < max_iter)
    {
        z =z*z +c;
        i+=1;
        size = len(z);
    }
    return i;
}

double abs1(double x)
{
    if (x<0)
        return -x;
    return x;
}
void draw_mandle(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx, int max_iter, double *maxx,double *maxy,double *minx,double *miny,int hold,int* Q)
{

    for(int k = 0 ; k <hold ; k++)
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        if (*Q %20 == 0)
        {
            for(int y = 0;y<pInfoHeader->biHeight;y++)
            {
                
                for(int x = 0;x<pInfoHeader->biWidth-1;x++)
                {
                    
                    xx = *minx +x*x_pixelunit;
                    yy = *miny +y*y_pixelunit;
                    
                    c = xx + yy*I;
                    
                    iter = mandel(c,max_iter);
                    
                    if (iter < max_iter)
                    {
                        pImageData[y*pInfoHeader->biWidth+x] =1;
                        
                    }
                    else
                    {

                        pImageData[y*pInfoHeader->biWidth+x] =2;
                        
                    }

                }
            }
        }
        if (*Q %20 == 0)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}
void coloring(unsigned char* pImageData,
    BITMAPINFOHEADER* pInfoHeader)
{
    for(int y = 0;y<pInfoHeader->biHeight;y++)
    {
        
        for(int x = 0;x<pInfoHeader->biWidth-1;x++)
        {
            pImageData[y*pInfoHeader->biWidth+x] = 2;
        }
    }
}

void zooming(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny,int zoom_iter, double quantity,int* Q)
{

    for(int k = 0;k<zoom_iter;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        for(int y = 0;y<pInfoHeader->biHeight;y++)
        {
            
            for(int x = 0;x<pInfoHeader->biWidth;x++)
            {
                
                xx = *minx +x*x_pixelunit;
                yy = *miny +y*y_pixelunit;
                
                c = xx + yy*I;
                
                iter = mandel(c,max_iter);
                
                if (iter < max_iter)
                {
                    pImageData[y*pInfoHeader->biWidth+x] = 2;
                    
                }
                else
                {

                    pImageData[y*pInfoHeader->biWidth+x] = 6;
                    
                }

            }
        }
        
        spanx = *maxx - *minx;
        spany = *maxy - *miny;

        *minx = *minx + spanx*((1-(1.0/quantity))/quantity);
        *maxx = *maxx - spanx*((1-(1.0/quantity))/quantity);

        *miny = *miny + spany*((1-(1.0/quantity))/quantity);
        *maxy = *maxy - spany*((1-(1.0/quantity))/quantity);


        save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}
void panning(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny, int iter_pan, double  qua_pan_x,double qua_pan_y,int* Q)
{


    for(int k = 0;k<iter_pan;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        for(int y = 0;y<pInfoHeader->biHeight;y++)
        {
            
            for(int x = 0;x<pInfoHeader->biWidth;x++)
            {
                xx = *minx +x*x_pixelunit;
                yy = *miny +y*y_pixelunit;

                c = xx + yy*I;
                
                iter = mandel(c,max_iter);
                
                if (iter < max_iter)
                {
                    pImageData[y*pInfoHeader->biWidth+x] = 2;
                    
                }
                else
                {

                    pImageData[y*pInfoHeader->biWidth+x] = 6;
                    
                }

            }
        }
        *minx +=k*(qua_pan_x)*x_pixelunit;
        *maxx +=k*(qua_pan_x)*x_pixelunit;
        *miny +=k*(qua_pan_y)*y_pixelunit;
        *maxy +=k*(qua_pan_y)*y_pixelunit;

        save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}

void rotating(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny,double degree,int rot_iter,int* Q)
{

    for(int k = 0;k<rot_iter;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy - *miny) / pInfoHeader->biHeight;

        xx = 1.0;
        yy = 1.0;
        for(int y = 0;y<pInfoHeader->biHeight;y++)
        {
            
            for(int x = 0;x<pInfoHeader->biWidth;x++)
            {

                xx = *minx +x*x_pixelunit;
                yy = *miny +y*y_pixelunit;
                r = pow(((pow(xx,2)+pow(yy,2))),0.5);
                unit = (k/(rot_iter*1.0-1))*degree;

                if (xx<0 && yy<0)
                    tetha = M_PI + atan(yy/xx);
                if (xx<0 && yy>0)
                    tetha = M_PI - abs1(atan(yy/xx));
                if (xx>0 && yy<0)
                    tetha = 2*M_PI - abs1(atan(yy/xx));
                if (xx>0 && yy>0)
                    tetha = atan(yy/xx);

                xx = r*(cos(tetha+unit));
                yy = r*(sin(tetha+unit));
                c = xx + yy*I;

                iter = mandel(c,max_iter);
                
                if (iter < max_iter)
                {
                    pImageData[y*pInfoHeader->biWidth+x] = 2;
                    
                }
                else
                {

                    pImageData[y*pInfoHeader->biWidth+x] = 6;
                    
                }

            }
        }

        save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}


void zooming1(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny,int zoom_iter, double quantity,int* Q,int limit)
{

    for(int k = 0;k<zoom_iter;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        if (*Q %limit == 0)
        {
            for(int y = 0;y<pInfoHeader->biHeight;y++)
            {
                
                for(int x = 0;x<pInfoHeader->biWidth;x++)
                {
                    
                    xx = *minx +x*x_pixelunit;
                    yy = *miny +y*y_pixelunit;
                    
                    c = xx + yy*I;
                    
                    iter = mandel(c,max_iter);
                    
                    if (iter < max_iter)
                    {
                        pImageData[y*pInfoHeader->biWidth+x] =2;
                        
                    }
                    else
                    {

                        pImageData[y*pInfoHeader->biWidth+x] =6;
                        
                    }

                }
            }
        }
        
        spanx = *maxx - *minx;
        spany = *maxy - *miny;

        *minx = *minx + spanx*((1-(1.0/quantity))/quantity);
        *maxx = *maxx - spanx*((1-(1.0/quantity))/quantity);

        *miny = *miny + spany*((1-(1.0/quantity))/quantity);
        *maxy = *maxy - spany*((1-(1.0/quantity))/quantity);

        if (*Q %limit == 0)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}
void panning1(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny, int iter_pan, double  qua_pan_x,double qua_pan_y,int* Q,int limit)
{


    for(int k = 0;k<iter_pan;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        if (*Q %limit == 0)
        {
            for(int y = 0;y<pInfoHeader->biHeight;y++)
            {
                
                for(int x = 0;x<pInfoHeader->biWidth;x++)
                {
                    xx = *minx +x*x_pixelunit;
                    yy = *miny +y*y_pixelunit;

                    c = xx + yy*I;
                    
                    iter = mandel(c,max_iter);
                    
                    if (iter < max_iter)
                    {
                        pImageData[y*pInfoHeader->biWidth+x] =2;
                        
                    }
                    else
                    {

                        pImageData[y*pInfoHeader->biWidth+x] =6;
                        
                    }

                }
            }
        }
        *minx +=k*(qua_pan_x)*x_pixelunit;
        *maxx +=k*(qua_pan_x)*x_pixelunit;
        *miny +=k*(qua_pan_y)*y_pixelunit;
        *maxy +=k*(qua_pan_y)*y_pixelunit;
        if (*Q %limit == 0)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}

void rotating1(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny,double degree,int rot_iter,int* Q,int limit)
{

    for(int k = 0;k<rot_iter;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy - *miny) / pInfoHeader->biHeight;

        xx = 1.0;
        yy = 1.0;
        if (*Q %limit == 0)
        {
            for(int y = 0;y<pInfoHeader->biHeight;y++)
            {
                
                for(int x = 0;x<pInfoHeader->biWidth;x++)
                {

                    xx = *minx +x*x_pixelunit;
                    yy = *miny +y*y_pixelunit;
                    r = pow(((pow(xx,2)+pow(yy,2))),0.5);
                    unit = (k/(rot_iter*1.0-1))*degree;

                    if (xx<0 && yy<0)
                        tetha = M_PI + atan(yy/xx);
                    if (xx<0 && yy>0)
                        tetha = M_PI - abs1(atan(yy/xx));
                    if (xx>0 && yy<0)
                        tetha = 2*M_PI - abs1(atan(yy/xx));
                    if (xx>0 && yy>0)
                        tetha = atan(yy/xx);

                    xx = r*(cos(tetha+unit));
                    yy = r*(sin(tetha+unit));
                    c = xx + yy*I;

                    iter = mandel(c,max_iter);
                    
                    if (iter < max_iter)
                    {
                        pImageData[y*pInfoHeader->biWidth+x] =2;
                        
                    }
                    else
                    {

                        pImageData[y*pInfoHeader->biWidth+x] =6;
                        
                    }

                }
            }
        }
        if (*Q %limit == 0)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}

void zooming2(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny,int zoom_iter, double quantity,int* Q,int limit)
{

    for(int k = 0;k<zoom_iter;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        if (*Q == -1)
        {
            for(int y = 0;y<pInfoHeader->biHeight;y++)
            {
                
                for(int x = 0;x<pInfoHeader->biWidth;x++)
                {
                    
                    xx = *minx +x*x_pixelunit;
                    yy = *miny +y*y_pixelunit;
                    
                    c = xx + yy*I;
                    
                    iter = mandel(c,max_iter);
                    
                    if (iter < max_iter)
                    {
                        pImageData[y*pInfoHeader->biWidth+x] =2;
                        
                    }
                    else
                    {

                        pImageData[y*pInfoHeader->biWidth+x] =6;
                        
                    }

                }
            }
        }
        
        spanx = *maxx - *minx;
        spany = *maxy - *miny;

        *minx = *minx + spanx*((1-(1.0/quantity))/quantity);
        *maxx = *maxx - spanx*((1-(1.0/quantity))/quantity);

        *miny = *miny + spany*((1-(1.0/quantity))/quantity);
        *maxy = *maxy - spany*((1-(1.0/quantity))/quantity);

        if (*Q == -1)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}
void panning2(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx,int max_iter, double *maxx,double *maxy,double *minx,double *miny, int iter_pan, double  qua_pan_x,double qua_pan_y,int* Q,int limit)
{


    for(int k = 0;k<iter_pan;k++)  
    {
        double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
        double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
        if (*Q == -1)
        {
            for(int y = 0;y<pInfoHeader->biHeight;y++)
            {
                
                for(int x = 0;x<pInfoHeader->biWidth;x++)
                {
                    xx = *minx +x*x_pixelunit;
                    yy = *miny +y*y_pixelunit;

                    
                    c = xx + yy*I;
                    
                    iter = mandel(c,max_iter);
                    
                    if (iter < max_iter)
                    {
                        pImageData[y*pInfoHeader->biWidth+x] =2;
                        
                    }
                    else
                    {

                        pImageData[y*pInfoHeader->biWidth+x] =6;
                        
                    }

                }
            }
        }
        *minx +=k*(qua_pan_x)*x_pixelunit;
        *maxx +=k*(qua_pan_x)*x_pixelunit;
        *miny +=k*(qua_pan_y)*y_pixelunit;
        *maxy +=k*(qua_pan_y)*y_pixelunit;
        if (*Q == -1)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}
void draw_mandle1(unsigned char* pImageData,
BITMAPINFOHEADER* pInfoHeader,    BITMAPFILEHEADER* pFileHeader,
    COLORINDEX* pColorIdx, int max_iter, double *maxx,double *maxy,double *minx,double *miny,int hold, int* Q,int limit)
{

    for(int k = 0 ; k <hold ; k++)
    {
        if (*Q%limit == 0)
        {
            double x_pixelunit = (*maxx - *minx) / pInfoHeader->biWidth;
            double y_pixelunit = (*maxy-*miny) / pInfoHeader->biHeight;
            if (*Q %20 == 0)
            {
                for(int y = 0;y<pInfoHeader->biHeight;y++)
                {
                    
                    for(int x = 0;x<pInfoHeader->biWidth-1;x++)
                    {
                        
                        xx = *minx +x*x_pixelunit;
                        yy = *miny +y*y_pixelunit;
                        
                        c = xx + yy*I;
                        
                        iter = mandel(c,max_iter);
                        
                        if (iter < max_iter)
                        {
                            pImageData[y*pInfoHeader->biWidth+x] =1;
                            
                        }
                        else
                        {

                            pImageData[y*pInfoHeader->biWidth+x] =2;
                            
                        }

                    }
                }
            }
        }
        if (*Q%limit  == 0)
            save_file1(pInfoHeader,pFileHeader, pColorIdx,pImageData ,*Q);
        (*Q)++;
    }
}