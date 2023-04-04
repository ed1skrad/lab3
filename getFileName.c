#include <stdio.h>
#include <stdlib.h>
//
// Created by Artem on 04.04.2023.
//
char* getFileName()
{
    char* filename = (char*)calloc(1, sizeof(char));
    printf("Enter filename:\n");
    scanf("%54s", filename);
    return filename;
}