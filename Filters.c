#include "BMP.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
//
// Created by Artem on 04.04.2023.
//
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
            redValues[0] = pixels[(y - 1) * width + x - 1].red;
            redValues[1] = pixels[(y - 1) * width + x].red;
            redValues[2] = pixels[(y - 1) * width + x + 1].red;
            redValues[3] = pixels[y * width + x - 1].red;
            redValues[4] = pixels[y * width + x].red;
            redValues[5] = pixels[y * width + x + 1].red;
            redValues[6] = pixels[(y + 1) * width + x - 1].red;
            redValues[7] = pixels[(y + 1) * width + x].red;
            redValues[8] = pixels[(y + 1) * width + x + 1].red;

            for (int i = 0; i < sizeof(redValues) / sizeof(redValues[0]); i++) {
                for (int j = i; j < sizeof(redValues) / sizeof(redValues[0]); j++) {
                    if (redValues[j] < redValues[i]) {
                        unsigned char tempValue = redValues[i];
                        redValues[i] = redValues[j];
                        redValues[j] = tempValue;
                    }
                }
            }

            unsigned char greenValues[9] = {};
            greenValues[0] = pixels[(y - 1) * width + x - 1].green;
            greenValues[1] = pixels[(y - 1) * width + x].green;
            greenValues[2] = pixels[(y - 1) * width + x + 1].green;
            greenValues[3] = pixels[y * width + x - 1].green;
            greenValues[4] = pixels[y * width + x].green;
            greenValues[5] = pixels[y * width + x + 1].green;
            greenValues[6] = pixels[(y + 1) * width + x - 1].green;
            greenValues[7] = pixels[(y + 1) * width + x].green;
            greenValues[8] = pixels[(y + 1) * width +x + 1].green;

            for (int i = 0; i < sizeof(greenValues) / sizeof(greenValues[0]); i++) {
                for (int j = i; j < sizeof(greenValues) / sizeof(greenValues[0]); j++) {
                    if (greenValues[j] < greenValues[i]) {
                        unsigned char tempValue = greenValues[i];
                        greenValues[i] = greenValues[j];
                        greenValues[j] = tempValue;
                    }
                }
            }

            unsigned char blueValues[9] = {};
            blueValues[0] = pixels[(y - 1) * width + x - 1].blue;
            blueValues[1] = pixels[(y - 1) * width + x].blue;
            blueValues[2] = pixels[(y - 1) * width + x + 1].blue;
            blueValues[3] = pixels[y * width + x - 1].blue;
            blueValues[4] = pixels[y * width + x].blue;
            blueValues[5] = pixels[y * width + x + 1].blue;
            blueValues[6] = pixels[(y + 1) * width + x - 1].blue;
            blueValues[7] = pixels[(y + 1) * width + x].blue;
            blueValues[8] = pixels[(y + 1) * width + x + 1].blue;

            for (int i = 0; i < sizeof(blueValues) / sizeof(blueValues[0]); i++) {
                for (int j = i; j < sizeof(blueValues) / sizeof(blueValues[0]); j++) {
                    if (blueValues[j] < blueValues[i]) {
                        unsigned char tempValue = blueValues[i];
                        blueValues[i] = blueValues[j];
                        blueValues[j] = tempValue;
                    }
                }
            }

            temp[y * width + x].red   = redValues[sizeof(redValues) / sizeof(redValues[0]) / 2];
            temp[y * width + x].green = greenValues[sizeof(greenValues) / sizeof(greenValues[0]) / 2];
            temp[y * width + x].blue  = blueValues[sizeof(blueValues) / sizeof(blueValues[0]) / 2];
        }
    }

    memcpy(pixels, temp, sizeof(BMPColor) * width * height);
}
void gammaCorrection(BMPColor *color, float gammaValue) {
    color->red   = (unsigned char)(pow(color->red   / 255.0f, gammaValue) * 255.0f);
    color->green = (unsigned char)(pow(color->green / 255.0f, gammaValue) * 255.0f);
    color->blue  = (unsigned char)(pow(color->blue  / 255.0f, gammaValue) * 255.0f);
}


