#pragma once
#ifndef BMP_H
#define BMP_H

typedef unsigned char LBYTE;	//
typedef unsigned short LWORD;	//
typedef unsigned int LDWORD;
typedef long LLONG;				//

//

#pragma pack(2)
typedef struct
{
	LWORD bfType;
	LDWORD bfSize;
	LWORD bfReserved1;
	LWORD bfReserved2;
	LDWORD bfOffBits;
}LBITMAPFILEHEADER;
// #pragma pack(pop)

typedef struct
{
	LDWORD biSize;
	LLONG biWidth;
	LLONG biHeight;
	LWORD biPlanes;
	LWORD biBitCount;
	LDWORD biCompression;
	LDWORD biSizeImage;
	LLONG biXPelsPerMeter;
	LLONG biYPelsPerMeter;
	LDWORD biClrUsed;
	LDWORD biClrImportant;
}LBITMAPINFOHEADER;

typedef struct
{
	LBYTE rgbBlue;
	LBYTE rgbGreen;
	LBYTE rgbRed;
	LBYTE rgbReserved;
}LRGBQUAD;

typedef struct
{
	unsigned char* buf;
	int width_x;
	int height_y;
	int deepth;
	LRGBQUAD* palette;
}LBmpbase;

//bool saveBmp(char*, unsigned char*, int, int, int, RGBQUAD*);
//Bmpbase readbmp(char*);
bool saveBmp(char*, unsigned char*, int, int, int, LRGBQUAD*);

bool SaveBmp1(char * fileName, unsigned char *imgBuffer, int imWidth, int imHeight);

bool wDataToBitBmp(unsigned char*, int imWidth, int imHeight, char *imName);
// Bmpbasel readbmp(char*);
// Bmpbase imrotate(unsigned char*, int, int, int, RGBQUAD*, double);

#endif

//BMP文件头（14字节）
typedef struct                       /**** BMP file header structure ****/
{
	unsigned short bfType;
	unsigned int   bfSize;           /* Size of file */
	unsigned short bfReserved1;      /* Reserved */
	unsigned short bfReserved2;      /* ... */
	unsigned int   bfOffBits;        /* Offset to bitmap data */
} MyBITMAPFILEHEADER;

//位图信息头（40字节）
typedef struct                       /**** BMP file info structure ****/
{
	unsigned int   biSize;           /* Size of info header */
	int            biWidth;          /* Width of image */
	int            biHeight;         /* Height of image */
	unsigned short biPlanes;         /* Number of color planes */
	unsigned short biBitCount;       /* Number of bits per pixel */
	unsigned int   biCompression;    /* Type of compression to use */
	unsigned int   biSizeImage;      /* Size of image data */
	int            biXPelsPerMeter;  /* X pixels per meter */
	int            biYPelsPerMeter;  /* Y pixels per meter */
	unsigned int   biClrUsed;        /* Number of colors used */
	unsigned int   biClrImportant;   /* Number of important colors */
} MyBITMAPINFOHEADER;
