#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include"lib.h"
#define _USE_MATH_DEFINES
#include <math.h>

int main()
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

    double cx = -0.74384935657398;
    double cy = -0.13170134084746293;
    double minx1 = -0.74384935657398 - 1.5;
    double maxx1 = -0.74384935657398 + 1.5;
    double miny1 = -0.13170134084746293 - 1.5;
    double maxy1 = -0.13170134084746293 + 1.5;
    double* minx = &minx1;
    double* maxx = &maxx1;
    double* miny = &miny1;
    double* maxy = &maxy1;
    int max_iter = 93;

    int zoom_iter = 90;  //0-89
    double quantity = 1.029;

    int iter_pan = 210;//89-299
    double qua_pan_x = 0.0;
    double qua_pan_y = 0.102;

    int iter_pan1 = 180;//299-479
    double qua_pan_x1 = -0.0309;
    double qua_pan_y1 = 0.096;

    int iter_pan2 = 90;//479-569
    double qua_pan_x2 = -0.2619;
    double qua_pan_y2 = -0.201;

    int zoom_iter1 = 60;  //569-629
    double quantity1 = 1.02;

    //HOLD 629-679
    int iter_pan3 = 111;//629-740
    double qua_pan_x3 = -0.2028;
    double qua_pan_y3 = 0.2361;

    double degree = -2*M_PI; //740-840
    int rot_iter = 100;

    int iter_pan4 = 90; //840-930
    double qua_pan_x4 = 0.2139;
    double qua_pan_y4 = 0.133;

    int zoom_iter2 = 69;  //930-999
    double quantity2 = 1.032;



    int hold = 40;
    int limit = 40;
    int test = 0;
    int* Q = &test;

    // // coloring(pImageData,&InfoHeader);
    // save_file(&InfoHeader, &FileHeader, ColorIdx, pImageData, 6);

    zooming2(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter,quantity,Q,limit);
    panning2(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan, qua_pan_x,qua_pan_y,Q,limit);
    panning2(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan1, qua_pan_x1,qua_pan_y1,Q,limit);
    panning2(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan2, qua_pan_x2,qua_pan_y2,Q,limit);
    zooming2(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter1,quantity1,Q,100);
    draw_mandle1(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter, maxx,maxy,minx, miny,hold,Q,limit);
    panning2(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan3, qua_pan_x3,qua_pan_y3,Q,limit);
    // rotating1(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny,degree,rot_iter,Q,1);
    panning1(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan4, qua_pan_x4,qua_pan_y4,Q,10);
    // zooming1(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter2,quantity2,Q,3);
    // panning1(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan2, qua_pan_x2,qua_pan_y2,Q,limit);
    // zooming1(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter1,quantity1,Q,limit);
    // panning1(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan3, qua_pan_x3,qua_pan_y3,Q,limit);
    // draw_mandle(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter, maxx,maxy,minx, miny,hold, Q);
    // rotating(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny,degree,rot_iter,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan1, qua_pan_x1,qua_pan_y1,Q);
    // zooming(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter1,quantity1,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan2, qua_pan_x2,qua_pan_y2,Q);
    // rotating(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny,degree1,rot_iter1,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan3, qua_pan_x3,qua_pan_y3,Q);
    // zooming(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter2,quantity2,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan4, qua_pan_x4,qua_pan_y4,Q);
    // rotating(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny,degree2,rot_iter2,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan5, qua_pan_x5,qua_pan_y5,Q);
    // zooming(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter3,quantity3,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan6, qua_pan_x6,qua_pan_y6,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan7, qua_pan_x7,qua_pan_y7,Q);
    // panning(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan8, qua_pan_x8,qua_pan_y8,Q);
    // zooming(pImageData,&InfoHeader,&FileHeader,
    //     ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter4,quantity4,Q);
    // draw_mandle(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter, maxx,maxy,minx, miny,hold, Q);
}