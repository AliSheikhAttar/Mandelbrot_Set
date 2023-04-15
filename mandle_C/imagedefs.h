#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfoffBits;
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int bisize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
}BITMAPINFOHEADER;

typedef struct tagCOLORTABLE
{
    unsigned char b,g,r,junk;
}COLORINDEX;
#pragma pack(pop)