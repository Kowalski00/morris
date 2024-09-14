#include <stdlib.h>
#include <stdio.h>
#include "morris_unix.h"

int getRandomColorKey()
{
    int colorKey;
    do{
        colorKey =  rand() % 4;
    } while (colorKey == lastColorKey || colorKey == 0);
    lastColorKey = colorKey;
    
    return colorKey;    
}

void printLine(struct lineParameters *pParameters, int showDescription)
{
    unsigned int *dst = (int *)pParameters->currentRow;
    char *pBitSetColor = (char *)pParameters->pBitSetColor;
    printf("\n %3d |\t", pParameters->lineNumber);
    fflush(stdout);
    char *pColor;
    int colorKey;
    for(int i = 0; i < pParameters->rowLength; i++ )
    {
        if(i % 2 == 0) 
        {
            colorKey = getRandomColorKey();
	        pColor = getColor(colorKey);
            printf("%s", pColor);
        }
        if(*dst != 0) printf(" %d",*dst);

	    fflush(stdout);
        dst++;

        if(showDescription)
        {
		    *pBitSetColor = colorKey;
		    pBitSetColor++;
        }
    }
    printf("%s", COLOR_DEFAULT);
}

struct lineParameters createLineParameters(int line, int *pCurrentRow)
{
    lineParameters parameters;
    parameters.lineNumber = line;
    copyArray(pCurrentRow, parameters.currentRow, ROW_SIZE);	 
    parameters.rowLength = ROW_SIZE;

    return parameters;
}