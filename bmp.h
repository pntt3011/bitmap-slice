#pragma once
#pragma pack(1)
#pragma warning(disable: 4996)

#include <stdio.h>
#include <string>
#include <stdint.h>

#define MAX_SIZE	256

struct Header {
	uint16_t Signature;
	uint32_t Size;
	uint16_t Reserved1;
	uint16_t Reserved2;
	uint32_t PixelArrayOffset;
};

struct DIB {
	uint32_t DIBSize;
	uint32_t Width;
	uint32_t Height;
	uint16_t Plane;
	uint16_t Depth;
	uint32_t Compress;
	uint32_t PixelArraySize;
	uint32_t xResolution;
	uint32_t yResolution;
	uint32_t ColorTable;
	uint32_t ColorImportant;
};

struct Util {
	int Channel;
	int Padding;
	int LineSize;
	int ByteSize;
};

struct BitMap {
	Header header;
	DIB dib;
	Util util;
};
