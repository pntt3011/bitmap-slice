#include "divideUtil.h"

char* getPartName(char* partName, int pathLength, int i, const char* direct) {
	char* temp = partName + (pathLength - 4);
	char buffer[10];
	strncpy(temp, _itoa(i + 1, buffer, 10), MAX_SIZE);
	strncpy(temp + strlen(buffer), direct, 1);
	strncpy(temp + strlen(buffer) + 1, ".bmp", 4);
	*(temp + strlen(buffer) + 5) = '\0';
	return partName;
}

unsigned char* CutPixel(BitMap& head, BitMap& subHead, unsigned char* ImgByte, int VerticalParts, int HorizontalParts) {
	unsigned char* EachLine = new unsigned char[subHead.util.ByteSize];
	unsigned char* temp = EachLine;

	for (int i = 0; i < subHead.dib.Height; i++) {

		for (int j = 0; j < subHead.dib.Width; j++) 
			for (int k = 0; k < subHead.util.Channel; k++) {
				*(temp++) = ImgByte[head.util.LineSize * (i + HorizontalParts * subHead.dib.Height) + subHead.util.Channel * (VerticalParts * subHead.dib.Width + j) + k];
		}

		for (int j = 0; j < subHead.util.Padding; j++) {
			*(temp++) = 0;
		}
	}
	return EachLine;
}

