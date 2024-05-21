#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#define ROW_SIZE 1024

const char *n_desc[] = {
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

void printLine(struct lineParameters *parameters, int showDescription)
{
    unsigned int *dst = (int *)parameters->currentRow;
    printf("\n %3d |\t", parameters->lineNumber);
    for(int i = 0; i < parameters->rowLength; i++ )
    {
        if(i % 2 == 0) 
        {
            WORD color = getRandomColor();
            SetConsoleTextAttribute(parameters->handleConsole, color);
        }
        if(*dst != 0) printf(" %d",*dst);
        dst++;
    }
    SetConsoleTextAttribute(parameters->handleConsole, parameters->attributes);
}

void clearArray(int *array, size_t len)
{
    unsigned int *dst = array;
    for(int i = 0; i < len; i++ )
    {
        *dst = 0;
        dst++;
    }
}

void copyArray(int *src, int *destiny, size_t len)
{
    unsigned int *psrc = src;
    unsigned int *pdst = destiny;
    for(int i = 0; i < len; i++ )
    {
        *pdst = *psrc;
        pdst++;
        psrc++;
    }
}

void enrichRow(int digitQuantity, int digit, int *array)
{
    unsigned int *dst = array;
    for(int i = 0; i < ROW_SIZE; i++ )
    {
        if(*dst == 0) {
            *dst = digitQuantity;
            *dst++;
            *dst = digit; break;
        }
        *dst++;
    }
}

void printLineDescription(int lineNumber, int *array, size_t len)
{
    printf("\n     |\t  --> ");
    for(int i=0; i < len; i+=2)
    {
        if(*array == 0) continue;

        printf("%s ", n_desc[*array++]);
        printf("%d ", *array++);

        if(*array != 0) printf("and ");
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

                enrichRow(digitGroupQuantity,lastDigit,nextRow);

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
