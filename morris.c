#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef linux
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#define ROW_SIZE 1024

#ifdef linux
#define COLOR_DEFAULT  "\x1B[0m"
#define COLOR_RED      "\x1B[31m"
#define COLOR_GRN      "\x1B[32m"
#define COLOR_BLU      "\x1B[34m"
#endif

const char *pN_desc[] = {
    "Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"
};

int lastColorKey;

#ifdef linux
typedef struct lineParameters {
    int lineNumber;
    int currentRow[ROW_SIZE];
    size_t rowLength;
} lineParameters;
#endif

#ifdef _WIN32
typedef struct lineParameters {
    int lineNumber;
    int currentRow[ROW_SIZE];
    size_t rowLength;
    HANDLE handleConsole;
    WORD attributes;
    WORD *pBitSetColor;
} lineParameters;

#ifdef _WIN32
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
#endif

#ifdef linux
char getRandomColor()
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
            return COLOR_BLU;
            break;
        }
        case 2:
        {
            return COLOR_GRN;
            break;
        }
        case 3:
        {
            return COLOR_RED;
            break;
        }
    }
}
#endif

void printLine(struct lineParameters *pParameters, int showDescription)
{
    unsigned int *pParamCurrentRow = (int *)pParameters->currentRow;
    WORD *pBitSetColor = (WORD *)pParameters->pBitSetColor;
    printf("\n %3d |\t", pParameters->lineNumber);
    fflush(stdout);
    for(int i = 0; i < pParameters->rowLength; i++ )
    {
        WORD color;
        if(i % 2 == 0) 
        {
            color = getRandomColor();
            SetConsoleTextAttribute(pParameters->handleConsole, color);
        }
        if(*pParamCurrentRow != 0) printf(" %d",*pParamCurrentRow);
        pParamCurrentRow++;
	    fflush(stdout);

        if(showDescription)
        {
            *pBitSetColor = color;
            pBitSetColor++;
        }
    }
    SetConsoleTextAttribute(pParameters->handleConsole, pParameters->attributes);
}
#endif

#ifdef linux
void printLine(struct lineParameters *pParameters, int showDescription)
{
    unsigned int *dst = (int *)pParameters->currentRow;
    printf("\n %3d |\t", pParameters->lineNumber);
    fflush(stdout);
    for(int i = 0; i < pParameters->rowLength; i++ )
    {
        char color;
        if(i % 2 == 0) 
        {
            color = getRandomColor();
            printf("%s", color);
        }
        if(*dst != 0) printf(" %d",*dst);
        printf("%s", COLOR_DEFAULT);
	    fflush(stdout);
        dst++;
    }
}
#endif


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
            *pArray = digit;
            break;
        }
        *pArray++;
    }
}

void printLineDescription(int lineNumber, int *pRow, size_t len, struct lineParameters *pParameters)
{
#ifdef _WIN32
    WORD *pBitSetColor = (WORD *)pParameters->pBitSetColor;
#endif
    printf("\n     |\t  --> ");
    fflush(stdout);
    for(int i=0; i < len; i+=2)
    {
        if(*pRow == 0) continue;
            
#ifdef _WIN32
        WORD color = *pBitSetColor;
        SetConsoleTextAttribute(pParameters->handleConsole, color);
        pBitSetColor++;
        pBitSetColor++;
#endif
        printf("%s ", pN_desc[*pRow++]);
        printf("%d ", *pRow++);
	    fflush(stdout);

#ifdef _WIN32
        SetConsoleTextAttribute(pParameters->handleConsole, pParameters->attributes);
#endif

        if(*pRow != 0) printf("and ");
	    fflush(stdout);
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

#ifdef _WIN32
    HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(handleConsole, &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;
#endif

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

#ifdef linux
    lineParameters parameters;
    parameters.lineNumber = line;
    copyArray(currentRow, parameters.currentRow, ROW_SIZE);	 
    parameters.rowLength = ROW_SIZE;
#endif
#ifdef _WIN32
    lineParameters parameters;
    parameters.lineNumber = line;
    copyArray(currentRow, parameters.currentRow, ROW_SIZE);
    parameters.rowLength = ROW_SIZE;
    parameters.handleConsole = handleConsole;
    parameters.attributes = savedAttributes;
#endif

    if(showDescription) 
    {
#ifdef _WIN32
       parameters.pBitSetColor = (WORD *) malloc(ROW_SIZE*sizeof(WORD)); 
#endif
    }

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

#ifdef _WIN32
        parameters.lineNumber = line+1;
        copyArray(currentRow, parameters.currentRow, ROW_SIZE);
        parameters.rowLength = ROW_SIZE;
        parameters.handleConsole = handleConsole;
        parameters.attributes = savedAttributes;
        
        printLine(&parameters, showDescription);
#endif
#ifdef linux
        parameters.lineNumber = line+1;
        copyArray(currentRow, parameters.currentRow, ROW_SIZE);
        parameters.rowLength = ROW_SIZE;
        
        printLine(&parameters, showDescription);
#endif


        if(showDescription) printLineDescription(line+1, currentRow, ROW_SIZE, &parameters);
        line++;
	//sleep(0.5);
    }
    printf("\n");
    return 0;
}
