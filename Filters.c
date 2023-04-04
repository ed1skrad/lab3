#include "BMP.h"
#include <stdlib.h>
#include <string.h>
//
// Created by Artem on 04.04.2023.
//
double my_pow(double base, double exponent) {
    double result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

void negative(BMPColor *color) {
    color->red = 255 - color->red;
    color->green = 255 - color->green;
    color->blue = 255 - color->blue;
}

void grayscale(BMPColor *color) {
    float gray = (float)(color->red + color->green + color->blue) / 3.0f;

    color->red = (unsigned char)gray;
    color->green = (unsigned char)gray;
    color->blue = (unsigned char)gray;
}

void gammaCorrection(BMPColor *color, float gammaValue) {
    color->red   = (unsigned char)(my_pow(color->red   / 255.0f, gammaValue) * 255.0f);
    color->green = (unsigned char)(my_pow(color->green / 255.0f, gammaValue) * 255.0f);
    color->blue  = (unsigned char)(my_pow(color->blue  / 255.0f, gammaValue) * 255.0f);
}

void sortArray(unsigned char *values, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (values[j] < values[i]) {
                unsigned char tempValue = values[i];
                values[i] = values[j];
                values[j] = tempValue;
            }
        }
    }
}

void getPixelValues(BMPColor *pixels, int width, int height, int x, int y, unsigned char *redValues, unsigned char *greenValues, unsigned char *blueValues) {
    redValues[0] = pixels[(y - 1) * width + x - 1].red;
    redValues[1] = pixels[(y - 1) * width + x].red;
    redValues[2] = pixels[(y - 1) * width + x + 1].red;
    redValues[3] = pixels[y * width + x - 1].red;
    redValues[4] = pixels[y * width + x].red;
    redValues[5] = pixels[y * width + x + 1].red;
    redValues[6] = pixels[(y + 1) * width + x - 1].red;
    redValues[7] = pixels[(y + 1) * width + x].red;
    redValues[8] = pixels[(y + 1) * width + x + 1].red;

    greenValues[0] = pixels[(y - 1) * width + x - 1].green;
    greenValues[1] = pixels[(y - 1) * width + x].green;
    greenValues[2] = pixels[(y - 1) * width + x + 1].green;
    greenValues[3] = pixels[y * width + x - 1].green;
    greenValues[4] = pixels[y * width + x].green;
    greenValues[5] = pixels[y * width + x + 1].green;
    greenValues[6] = pixels[(y + 1) * width + x - 1].green;
    greenValues[7] = pixels[(y + 1) * width + x].green;
    greenValues[8] = pixels[(y + 1) * width + x + 1].green;

    blueValues[0] = pixels[(y - 1) * width + x - 1].blue;
    blueValues[1] = pixels[(y - 1) * width + x].blue;
    blueValues[2] = pixels[(y - 1) * width + x + 1].blue;
    blueValues[3] = pixels[y * width + x - 1].blue;
    blueValues[4] = pixels[y * width + x].blue;
    blueValues[5] = pixels[y * width + x + 1].blue;
    blueValues[6] = pixels[(y + 1) * width + x - 1].blue;
    blueValues[7] = pixels[(y + 1) * width + x].blue;
    blueValues[8] = pixels[(y + 1) * width + x + 1].blue;
}

void medianFilter(BMPColor *pixels, int width, int height) {
    BMPColor *temp = malloc(sizeof(BMPColor) * width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            BMPColor *pixel = &pixels[y * width + x];

            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                temp[y * width + x] = *pixel;
                continue;
            }

            unsigned char redValues[9] = {};
            unsigned char greenValues[9] = {};
            unsigned char blueValues[9] = {};

            getPixelValues(pixels, width, height, x, y, redValues, greenValues, blueValues);

            sortArray(redValues, sizeof(redValues) / sizeof(redValues[0]));
            sortArray(greenValues, sizeof(greenValues) / sizeof(greenValues[0]));
            sortArray(blueValues, sizeof(blueValues) / sizeof(blueValues[0]));

            temp[y * width + x].red   = redValues[sizeof(redValues) / sizeof(redValues[0]) / 2];
            temp[y * width + x].green = greenValues[sizeof(greenValues) / sizeof(greenValues[0]) / 2];
            temp[y * width + x].blue  = blueValues[sizeof(blueValues) / sizeof(blueValues[0]) / 2];
        }
    }

    memcpy(pixels, temp, sizeof(BMPColor) * width * height);
    free(temp);
}


