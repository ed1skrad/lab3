#include "BMP.h"
#include "Init.h"
#include <stdio.h>

//
// Created by Artem on 04.04.2023.
//
void menu(BMPInfoHeader infoHeader, BMPColor* pixels)
{
    int choice;
    printf("Enter the operation you want to perform:\n");
    printf("1. Negative\n");
    printf("2. Grayscale\n");
    printf("3. Median filter\n");
    printf("4. Gamma correction\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            for (int i = 0; i < infoHeader.width * infoHeader.height; i++) {
                negative(&pixels[i]);
            }
            break;
        case 2:
            for (int i = 0; i < infoHeader.width * infoHeader.height; i++) {
                grayscale(&pixels[i]);
            }
            break;
        case 3:
            medianFilter(pixels, infoHeader.width, infoHeader.height);
            break;
        case 4: {
            float gammaValue;
            printf("Enter gamma value:\n");
            scanf("%f", &gammaValue);

            for (int i = 0; i < infoHeader.width * infoHeader.height; i++) {
                gammaCorrection(&pixels[i], gammaValue);
            }
            break;
        }
        default:
            printf("Incorrect input!\n");
            break;
    }
}