#include "divideUtil.h"
char* getPartName(char* partName, int pathLength, int i, const char* direct) {
	char* temp = partName + (pathLength - 4);
	char buffer[10];
	strcpy(temp, _itoa(i + 1, buffer, 10));
	strcpy(temp + strlen(buffer), direct);
	strcpy(temp + strlen(buffer) + 1, ".bmp");
	*(temp + strlen(buffer) + 5) = '\0';
	return partName;
}

unsigned char* CutPixel(BitMap& head, BitMap& subHead, unsigned char* ImgByte, int VerticalParts, int HorizontalParts) {

	unsigned char* subImgByte = new unsigned char[subHead.util.ByteSize];
	unsigned char* temp = subImgByte;

	for (int i = 0; i < subHead.dib.Height; i++) {

		for (int j = 0; j < subHead.dib.Width; j++) 
			for (int k = 0; k < subHead.util.Channel; k++) {
				*(temp++) = ImgByte[head.util.LineSize * (i + HorizontalParts * subHead.dib.Height) + subHead.util.Channel * (VerticalParts * subHead.dib.Width + j) + k];
		}

		for (int j = 0; j < subHead.util.Padding; j++) {
			*(temp++) = 0;
		}
	}
	return subImgByte;
}

