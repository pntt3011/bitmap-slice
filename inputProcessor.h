#pragma once
#include "bmp.h"
int numArg(int argc, char** argv);
void invalidInput();
void showHelp();
void divide(char* imgPath, int VerticalParts, int HorizontalParts);