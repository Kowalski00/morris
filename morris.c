#include <stdio.h>
#include <string.h>

#define SIZE 30
#define ROW_SIZE 11

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

int main() {

    int digitGroupQuantity = 0;
    int currentRow[SIZE];
    int nextRow[SIZE];
    
    clearArray( currentRow, sizeof(currentRow) / sizeof(currentRow[0]) );
    clearArray( nextRow, sizeof(nextRow) / sizeof(nextRow[0]) );
    currentRow[0] = 1;

    printf("\n %3d |  ", 1);
    printArrayAndFilterZeros(currentRow, sizeof(currentRow) / sizeof(currentRow[0]));

    for(int row = 0; row < ROW_SIZE; row++) {

        int currentDigit = currentRow[0];
        int lastDigit = currentRow[0];

        for(int r = 0; r < sizeof(currentRow) / sizeof(currentRow[0]) ; r++ ) {

            currentDigit = currentRow[r];

            if(lastDigit != currentDigit) {

                for(int i = 0; i < sizeof(nextRow) / sizeof(nextRow[0]); i++ ) {
                    if(nextRow[i] == 0) {
                        nextRow[i] = digitGroupQuantity;
                        break;
                    }
                }

                for(int i = 0; i < sizeof(nextRow) / sizeof(nextRow[0]); i++ ) {
                    if(nextRow[i] == 0) {
                        nextRow[i] = lastDigit;
                        break;
                    }
                }
                
                
                digitGroupQuantity = 0;
                if(currentDigit == 0) break;
                else digitGroupQuantity = 1;
                lastDigit = currentDigit;
                continue;
            }

            digitGroupQuantity++;

            lastDigit = currentDigit;

        }

        copyArray(nextRow, currentRow, SIZE);
        
        clearArray( nextRow, sizeof(nextRow) / sizeof(nextRow[0]) );

        printf("\n %3d |  ", row+1);
        printArrayAndFilterZeros(currentRow, sizeof(currentRow) / sizeof(currentRow[0]));
    }


    printf("\n");
    return 0;
}
