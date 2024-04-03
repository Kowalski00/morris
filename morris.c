#include <stdio.h>
#include <string.h>

#define ROW_SIZE 30
#define LINES_QTTY 11

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

    printf("\n        --> ");
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
    
    clearArray( currentRow, ROW_SIZE);
    clearArray( nextRow, ROW_SIZE );
    currentRow[0] = 1;

    printLine(line, currentRow, ROW_SIZE);
    
    while(line < LINES_QTTY) {

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
        printLineDescription(line+1, currentRow, ROW_SIZE);
        line++;
    }

    printf("\n");
    return 0;
}
