#include <stdio.h>
#include "BMP.h"
//
// Created by Artem on 04.04.2023.
//
void writeInfo(BMPHeader header, BMPInfoHeader infoHeader, BMPColor* pixels, FILE* file, int pixelArraySize)
{
    fwrite(&header,sizeof(header),1,file);
    fwrite(&infoHeader,sizeof(infoHeader),1,file);
    fseek(file,header.offset-sizeof(header)-sizeof(infoHeader),SEEK_CUR);
    fwrite(pixels,pixelArraySize,1,file);
}
