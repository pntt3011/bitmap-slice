#pragma once
#include "bmp.h"
char* getPartName(char* partName, int pathLength, int i, const char* direct);
unsigned char* CutPixel(BitMap& head, BitMap& subHead, unsigned char* ImgByte, int VerticalParts, int HorizontalParts);