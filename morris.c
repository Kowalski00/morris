#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#define ROW_SIZE 1024

const char *pN_desc[] = {
    "Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"
};

int lastColorKey;

typedef struct lineParameters {
    int lineNumber;
    int currentRow[ROW_SIZE];
    size_t rowLength;
    HANDLE handleConsole;
    WORD attributes;
} lineParameters;

WORD getRandomColor()
{
    int colorKey;
    do{
        colorKey =  rand() % 4;
    } while (colorKey == lastColorKey || colorKey == 0);
    lastColorKey = colorKey;
        
    switch(colorKey)
    {
        case 1:
        {
            return FOREGROUND_BLUE;
            break;
        }
        case 2:
        {
            return FOREGROUND_GREEN;
            break;
        }
        case 3:
        {
            return FOREGROUND_RED;
            break;
        }
    }
}

void printLine(struct lineParameters *pParameters, int showDescription)
{
    WORD colorOrder[pParameters->rowLength];
    unsigned int *pParamCurrentRow = (int *)pParameters->currentRow;
    printf("\n %3d |\t", pParameters->lineNumber);
    for(int i = 0; i < pParameters->rowLength; i++ )
    {
        if(i % 2 == 0) 
        {
            WORD color = getRandomColor();
            colorOrder[i] = color;
            SetConsoleTextAttribute(pParameters->handleConsole, color);
        }
        if(*pParamCurrentRow != 0) printf(" %d",*pParamCurrentRow);
        pParamCurrentRow++;
    }
    SetConsoleTextAttribute(pParameters->handleConsole, pParameters->attributes);
    if(showDescription) {
        printf("\n     |\t  --> "); 
    }
}

void clearArray(int *pArray, size_t len)
{
    for(int i = 0; i < len; i++ )
    {
        *pArray = 0;
        pArray++;
    }
}

void copyArray(int *pSrc, int *pTarget, size_t len)
{
    for(int i = 0; i < len; i++ )
    {
        *pTarget = *pSrc;
        pTarget++;
        pSrc++;
    }
}

void enrichRow(int digitQuantity, int digit, int *pArray)
{
    for(int i = 0; i < ROW_SIZE; i++ )
    {
        if(*pArray == 0) {
            *pArray = digitQuantity;
            *pArray++;
            *pArray = digit; break;
        }
        *pArray++;
    }
}

void printLineDescription(int lineNumber, int *pRow, size_t len)
{
    printf("\n     |\t  --> ");
    for(int i=0; i < len; i+=2)
    {
        if(*pRow == 0) continue;

        printf("%s ", pN_desc[*pRow++]);
        printf("%d ", *pRow++);

        if(*pRow != 0) printf("and ");
    }
}

int main()
{
    int digitGroupQuantity = 0;
    int currentRow[ROW_SIZE];
    int nextRow[ROW_SIZE];
    int line = 1;
    int showDescription = 0;
    int lineLimit;
    int firstNumber;

    HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(handleConsole, &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;

    printf("Do you want to show description below each lines? (1 or 0) \n");
    scanf("%d", &showDescription);

    printf("At what line should the sequence stop? (Insert a number or -1 to limit to 100) \n");
    scanf("%d", &lineLimit);

    printf("At which number should the sequence start? (Insert a number) \n");
    scanf("%d", &firstNumber);

    if(lineLimit == -1) lineLimit = 100;

    clearArray(currentRow, ROW_SIZE);
    clearArray(nextRow, ROW_SIZE);
    currentRow[0] = firstNumber;

    lineParameters parameters;
    parameters.lineNumber = line;
    copyArray(currentRow, parameters.currentRow, ROW_SIZE);
    parameters.rowLength = ROW_SIZE;
    parameters.handleConsole = handleConsole;
    parameters.attributes = savedAttributes;

    printLine(&parameters, showDescription);
    
    while(line < lineLimit)
    {
        int currentDigit = currentRow[0];
        int lastDigit = currentRow[0];

        for(int r = 0; r < ROW_SIZE ; r++ )
        {
            currentDigit = currentRow[r];

            if(lastDigit != currentDigit) {

                enrichRow(digitGroupQuantity, lastDigit, nextRow);

                digitGroupQuantity = 0;

                if(currentDigit == 0) break;
                
            }

            digitGroupQuantity++;

            lastDigit = currentDigit;
        }

        copyArray(nextRow, currentRow, ROW_SIZE);
        clearArray( nextRow, ROW_SIZE );

        parameters.lineNumber = line+1;
        copyArray(currentRow, parameters.currentRow, ROW_SIZE);
        parameters.rowLength = ROW_SIZE;
        parameters.handleConsole = handleConsole;
        parameters.attributes = savedAttributes;
        
        printLine(&parameters, showDescription);

        if(showDescription) printLineDescription(line+1, currentRow, ROW_SIZE);
        line++;
    }
    printf("\n");
    return 0;
}
