#include <stdio.h>
#include <stdlib.h>
#include "BMP.h"
#include "Init.h"


int main() {
    const char* filename = getFileName();

    FILE* file=fopen(filename,"rb");

    BMPHeader header;
    BMPInfoHeader infoHeader;
    BMPColor* pixels;

    if(file==NULL){
        printf("Error: File not found\n");
        return 1;
    }

    fread(&header,sizeof(header),1,file);

    if(header.type!=19778){
        printf("Error: Not a BMP file\n");
        fclose(file);
        return 1;
    }

    fread(&infoHeader,sizeof(infoHeader),1,file);

    if(infoHeader.bitsPerPixel!=24){
        printf("Error: Only supports 24 bit bmp images\n");
        fclose(file);
        return 1;
    }

    fseek(file, header.offset - sizeof(header) - sizeof(infoHeader), SEEK_CUR);

    int rowSize = (infoHeader.bitsPerPixel * infoHeader.width + 31) / 32 * 4;
    int pixelArraySize = rowSize * abs(infoHeader.height);
    pixels = malloc(pixelArraySize);

    fread(pixels, pixelArraySize, 1, file);

    fclose(file);

    menu(infoHeader, pixels);

    file = fopen("output.bmp","wb");
    writeInfo(header, infoHeader, pixels, file, pixelArraySize);

    fclose(file);
    free(pixels);
    return 0;
}
