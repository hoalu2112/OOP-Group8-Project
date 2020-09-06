#ifndef _BITMAP_H_
#define _BITMAP_H_
#include<iostream>
#include<cstring>
#include<fstream>
#pragma once
#include<cmath>
#include<stdio.h>
#include<stdint.h>
#include<Windows.h>
#pragma pack(1)
using namespace std;
struct BmpSignature{
	unsigned char data[2];
};
struct BmpHeader{
	BmpSignature signature;
	uint32_t filesize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t dataOffset;
};
struct BmpDip{
	uint32_t dipSize;
	uint32_t imageWidth;
	uint32_t imageHeight;
	uint16_t colorPlaneCount;
	uint16_t pixelSize;
	uint32_t compressMethod;
	uint32_t bitmapByteCount;
	uint32_t horizontalResolution;
	uint32_t verticalResolution;
	uint32_t colorCount;
	uint32_t importantColorCount;
};
struct Color{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};
struct ColorTable{
	Color *colortab;
	uint32_t length;
};
struct Pixel_Array{
	unsigned char *rawbytes;
	int raw_byte_size;
	int line_size;
	char paddingsize;
	
	Color **pixel;
	uint32_t rowCount;
	uint32_t colCount;
};
struct BMPFile{
	BmpHeader header;
	BmpDip dip; 	
	Pixel_Array pixelarray;
};
bool is_bitmap_file(FILE*f,string link);
void readBmpHeader(FILE *f,BMPFile &bmp,string link);
void printBmpHeader(BMPFile &bmp);
void initPixels(Pixel_Array& pa, int width, int height);
void readBmpDib(FILE *f,BMPFile &bmp,string link);
void PrintBmpDib(FILE *f, BMPFile &bmp);
void readBmpPixelArray(FILE *f,BMPFile &bmp,string link);
void PrintBGR_ij_position(FILE *f,BMPFile &bmp,string link);
void draw(const BMPFile &bmp);
void releaseBmpPixelArray(BMPFile &bmp);
#endif
