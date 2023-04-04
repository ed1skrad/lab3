#include "BMP.h"
#include <stdio.h>
//
// Created by Artem on 04.04.2023.
//

#ifndef UNTITLED20_INIT_H
#define UNTITLED20_INIT_H
void negative(BMPColor *color);
void grayscale(BMPColor *color);
void medianFilter(BMPColor *pixels, int width, int height);
void gammaCorrection(BMPColor *color, float gammaValue);
void menu(BMPHeader header, BMPInfoHeader infoHeader, BMPColor* pixels);
void writeInfo(BMPHeader header, BMPInfoHeader infoHeader, BMPColor* pixels, FILE* file, int pixelArraySize);
char* getFileName();
#endif //UNTITLED20_INIT_H
