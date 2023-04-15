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
    int max_iter = 30;
    int hold = 6;

    int zoom_iter = 60;
    double quantity = 1.01;

    int iter_pan = 40;
    double qua_pan_x = 0.0;
    double qua_pan_y = 0.690;

    double degree = -2*M_PI;
    int rot_iter = 50;

    int iter_pan1 = 30;
    double qua_pan_x1 = -0.92;
    double qua_pan_y1 = -0.496;

    int zoom_iter1 = 40;
    double quantity1 = 1.01;

    int iter_pan2 = 60; //219 - 279
    double qua_pan_x2 = 0.419;
    double qua_pan_y2 = -0.399;

    double degree1 = 2*M_PI;
    int rot_iter1 = 50;

    int iter_pan3 = 65;    //329 - 394
    double qua_pan_x3 = 0.73;
    double qua_pan_y3 = -0.7;

    int zoom_iter2 = 50;  //394 - 444
    double quantity2 = 1.0001;

    int iter_pan4 = 100;    //444 - 544
    double qua_pan_x4 = 0.3;
    double qua_pan_y4 = 0.33;

    double degree2 = -2*M_PI;
    int rot_iter2 = 50;

    int iter_pan5 = 100;    //594 - 694
    double qua_pan_x5 = -0.093;
    double qua_pan_y5 = 0.2;

    int zoom_iter3 = 30; //694 - 724
    double quantity3 = 1.04;

    int iter_pan6 = 100;    //724 - 824
    double qua_pan_x6 = 0.0575;
    double qua_pan_y6 = 0.033;

    int iter_pan7 = 80;    //824 - 904
    double qua_pan_x7 = -0.0625;
    double qua_pan_y7 = 0.103;

    int iter_pan8 = 25;    //904 - 929
    double qua_pan_x8 = -0.77;
    double qua_pan_y8 = 0.42;

    int zoom_iter4 = 70; //929 - 999
    double quantity4 = 1.0359;



    int test = 0;
    int* Q = &test;

    // // coloring(pImageData,&InfoHeader);
    // save_file(&InfoHeader, &FileHeader, ColorIdx, pImageData, 6);
    // draw_mandle(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter, maxx,maxy,minx, miny,hold,Q);
    zooming(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter,quantity,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan, qua_pan_x,qua_pan_y,Q);
    // draw_mandle(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter, maxx,maxy,minx, miny,hold, Q);
    rotating(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny,degree,rot_iter,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan1, qua_pan_x1,qua_pan_y1,Q);
    zooming(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter1,quantity1,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan2, qua_pan_x2,qua_pan_y2,Q);
    rotating(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny,degree1,rot_iter1,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan3, qua_pan_x3,qua_pan_y3,Q);
    zooming(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter2,quantity2,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan4, qua_pan_x4,qua_pan_y4,Q);
    rotating(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny,degree2,rot_iter2,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan5, qua_pan_x5,qua_pan_y5,Q);
    zooming(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter3,quantity3,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan6, qua_pan_x6,qua_pan_y6,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan7, qua_pan_x7,qua_pan_y7,Q);
    panning(pImageData,&InfoHeader,&FileHeader,
    ColorIdx,max_iter,maxx, maxy,minx,miny,iter_pan8, qua_pan_x8,qua_pan_y8,Q);
    zooming(pImageData,&InfoHeader,&FileHeader,
        ColorIdx,max_iter,maxx, maxy,minx,miny, zoom_iter4,quantity4,Q);
    // draw_mandle(pImageData,&InfoHeader,&FileHeader,
    // ColorIdx,max_iter, maxx,maxy,minx, miny,hold, Q);
}