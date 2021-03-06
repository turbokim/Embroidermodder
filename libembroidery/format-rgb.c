#include "format-rgb.h"
#include <stdio.h>
#include <stdlib.h>
#include "helpers-binary.h"

int readRgb(EmbPattern* pattern, const char* fileName)
{
    int i, numberOfColors;

    FILE* file = 0;

    file = fopen(fileName, "rb");
    if(!file)
    {
        return 0;
    }
    fseek(file, 0x00, SEEK_END);
    numberOfColors = ftell(file) / 4;

    embThreadList_free(pattern->threadList);

    fseek(file, 0x00, SEEK_SET);
    for(i = 0; i < numberOfColors; i++)
    {
        EmbThread t;
        t.color.r = binaryReadByte(file);
        t.color.g = binaryReadByte(file);
        t.color.b = binaryReadByte(file);
        binaryReadByte(file);
        embPattern_addThread(pattern, t);
    }
    fclose(file);
    return 1;
}

int writeRgb(EmbPattern* pattern, const char* fileName)
{
    EmbThreadList* colors = pattern->threadList;
    FILE* file = 0;

    file = fopen(fileName, "wb");
    if(!file)
    {
        return 0;
    }

    while(colors)
    {
        EmbColor c = colors->thread.color;
        binaryWriteByte(file, c.r);
        binaryWriteByte(file, c.g);
        binaryWriteByte(file, c.b);
        binaryWriteByte(file, 0);
        colors = colors->next;
    }
    fclose(file);
    return 1;
}

/* kate: bom off; indent-mode cstyle; indent-width 4; replace-trailing-space-save on; */
