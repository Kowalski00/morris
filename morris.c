#include <stdio.h>
#include <string.h>

#define ROW_SIZE 1024

const char *n_desc[] = {
    "Zero","One","Two","Three","Four","Five","Six","Seven","Eight","Nine"
};

void printArray(int *array, char *symbol) {
    printf(symbol);
    for(int i = 0; i < sizeof(array) / sizeof(array[0]); i++ ) {
        printf(" %d",array[i]);
    }
}

void printArrayAndFilterZeros(int *array, size_t len) {
    unsigned int *dst = array;
    for(int i = 0; i < len; i++ ) {
        if(*dst != 0) printf(" %d",*dst);
        dst++;
    }
}

void printLine(int lineNumber, int *array, size_t len) {

    printf("\n %3d |  ", lineNumber);
    unsigned int *dst = array;
    for(int i = 0; i < len; i++ ) {
        if(*dst != 0) printf(" %d",*dst);
        dst++;
    }
}

void clearArray(int *array, size_t len) {
    unsigned int *dst = array;
    for(int i = 0; i < len; i++ ) {
        *dst = 0;
        dst++;
    }
}

void copyArray(int *src, int *destiny, size_t len) {
    unsigned int *psrc = src;
    unsigned int *pdst = destiny;
    for(int i = 0; i < len; i++ ) {
        *pdst = *psrc;
        pdst++;
        psrc++;
    }
}

void enrichRow(int digitQuantity, int digit, int *array) {
    unsigned int *dst = array;
    for(int i = 0; i < ROW_SIZE; i++ ) {
        if(*dst == 0) {
            *dst = digitQuantity;
            *dst++;
            *dst = digit; break;
        }
        *dst++;
    }
}

void printLineDescription(int lineNumber, int *array, size_t len) {

    printf("\n     |    --> ");
    for(int i=0; i < len; i+=2) {

        if(*array == 0) continue;

        printf("%s ", n_desc[*array++]);
        printf("%d ", *array++);

        if(*array != 0) printf("and ");
    }
}

int main() {

    int digitGroupQuantity = 0;
    int currentRow[ROW_SIZE];
    int nextRow[ROW_SIZE];
    int line = 1;
    int showDescription = 0;
    int lineLimit;
    int firstNumber;

    printf("Do you want to show description below each lines? (1 or 0) \n");
    scanf("%d", &showDescription);
    
    printf("At what line should the sequence stop? (Insert a number or -1 to limit to 100) \n");
    scanf("%d", &lineLimit);

    printf("At which number should the sequence start? (Insert a number) \n");
    scanf("%d", &firstNumber);

    if(lineLimit == -1) lineLimit = 100;

    clearArray( currentRow, ROW_SIZE);
    clearArray( nextRow, ROW_SIZE );
    currentRow[0] = firstNumber;

    printLine(line, currentRow, ROW_SIZE);
    
    while(line < lineLimit) {

        int currentDigit = currentRow[0];
        int lastDigit = currentRow[0];

        for(int r = 0; r < ROW_SIZE ; r++ ) {

            currentDigit = currentRow[r];

            if(lastDigit != currentDigit) {

                enrichRow(digitGroupQuantity,lastDigit,nextRow); // NOTE: Why this function making compile/execution taking so long to execute

                digitGroupQuantity = 0;

                if(currentDigit == 0) break;
                
            }

            digitGroupQuantity++;

            lastDigit = currentDigit;

        }

        copyArray(nextRow, currentRow, ROW_SIZE);
        
        clearArray( nextRow, ROW_SIZE );

        printLine(line+1, currentRow, ROW_SIZE);
        if(showDescription) printLineDescription(line+1, currentRow, ROW_SIZE);
        line++;
    }

    printf("\n");
    return 0;
}
