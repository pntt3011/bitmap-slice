#include "inputProcessor.h"
#include "divideUtil.h"

// 1: chia doc, 2: chia ngang, 3: chia ca hai
int numArg(int argc, char** argv) {
	if (argc == 4 && (!strcmp(argv[2], "-h") || !strcmp(argv[2], "-w")) && strtol(argv[3], NULL, 10) != 0) {
		if (!strcmp(argv[2], "-h")) {
			return 1;
		}
		else {
			return 2;
		}
	}
	if (argc == 6 && !strcmp(argv[2], "-h") && !strcmp(argv[4], "-w") && strtol(argv[3], NULL, 10) != 0 && strtol(argv[5], NULL, 10) != 0) {
		return 3;
	}
	return -1;
}

void invalidInput() {
	printf("Type cutbmp.exe /? for available commands.\n");
}

void showHelp() {
	printf("Divide bitmap image into M x N subimage(s):\n");
	printf("cutbmp.exe <file name> [-h <M>] [-w <N>]\n");
	printf("With M is number of vertical parts, N is number of horizontal parts.\n");
}

void findPaddingAndSize(BitMap& header) {
	header.util.Padding = (4 - (header.dib.Width * header.util.Channel) % 4) % 4;
	header.util.LineSize = header.dib.Width * header.util.Channel + header.util.Padding;
	header.util.ByteSize = header.dib.Height * header.util.LineSize;
}

void divide(char* imgPath, int VerticalParts, int HorizontalParts) {
	FILE* img = fopen(imgPath, "rb");
	if (!img) {
		printf("Image not found.\n");
		return;
	}

	BitMap head;
	fread(&head.header, sizeof(Header), 1, img);
	fread(&head.dib, sizeof(DIB), 1, img);
	
	int ColorTableSize = head.header.PixelArrayOffset - sizeof(Header) - sizeof(DIB);
	char* ColorTable = new char[ColorTableSize];
	fread(ColorTable, sizeof(char), ColorTableSize, img);

	head.util.Channel  = head.dib.Depth / 8;
	findPaddingAndSize(head);

	unsigned char* ImgByte = new unsigned char[head.util.ByteSize];
	fseek(img, head.header.PixelArrayOffset, SEEK_SET);
	fread(ImgByte, sizeof(char), head.util.ByteSize, img);

	BitMap subHead;
	subHead = head;
	subHead.dib.Width /= VerticalParts;
	subHead.dib.Height /= HorizontalParts;
	findPaddingAndSize(subHead);
	subHead.dib.PixelArraySize = subHead.dib.Height * subHead.dib.Width * subHead.util.Channel;
	subHead.header.Size = subHead.util.ByteSize + subHead.header.PixelArrayOffset;	

	char* partName = new char[MAX_SIZE];
	strcpy(partName, imgPath);

	for (int i = 0; i < VerticalParts; i++)
		for (int j = 0; j < HorizontalParts; j++) {
			if (VerticalParts == 1 || HorizontalParts == 1) {
				getPartName(partName, strlen(imgPath), i + j ,VerticalParts == 1 ? "W" : "H");
			}
			else {
				getPartName(partName, strlen(imgPath), i, "H");
				getPartName(partName, strlen(partName), j, "W");
			}

			FILE* part = fopen(partName, "wb");
			fwrite(&subHead.header, sizeof(Header), 1, part);
			fwrite(&subHead.dib, sizeof(DIB), 1, part);
			fwrite(ColorTable, sizeof(char), ColorTableSize, part);

			unsigned char* subImgByte = CutPixel(head, subHead, ImgByte, i, HorizontalParts - j - 1);
			fwrite(subImgByte, sizeof(char), subHead.util.ByteSize, part);

			if (subImgByte) delete[] subImgByte;
			fclose(part);
		}

	fclose(img);
	if (partName) delete[] partName;
	if (ColorTable) delete[] ColorTable;
	if (ImgByte) delete[] ImgByte;
}