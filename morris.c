#include <stdio.h>
#include <string.h>

void printArray(int *array, char *symbol) {
    printf(symbol);
    for(int i = 0; i < sizeof(array) / sizeof(array[0]); i++ ) {
        printf(" %d",array[i]);
    }
}

void printArrayAndFilterZeros(int *array) {
    for(int i = 0; i < sizeof(array) / sizeof(array[0]); i++ ) {
        if(array[i] != 0) printf(" %d",array[i]);
    }
}

void clearArray(int *array) {
    for(int i = 0; i < sizeof(array) / sizeof(array[0]); i++ ) {
        array[i] = 0;
    }
}

void copyArray(int *src, int *destiny) {

    for(int i = 0; i < sizeof(src) / sizeof(src[0]); i++ ) {
        destiny[i] = src[i];
    }
}

int main() {

    int rowSize = 0;
    int currentRow[] = { 1, 0, 0, 0, 0, 0 };
    int lookRow[] = { 0, 0, 0, 0, 0, 0 };
    int groupDigit[] = { 0, 0, 0, 0, 0, 0 };
    int nextRow[] = { 0, 0, 0, 0, 0, 0 }; 

    for(int row = 0; row < 3; row++) {

        int currentDigit = currentRow[0];
        int lastDigit = currentRow[0];

        for(int r = 0; r < sizeof(currentRow) / sizeof(currentRow[0]) ; r++ ) {

            currentDigit = currentRow[r];

            if(lastDigit == currentDigit) {
                
                groupDigit[r] = currentDigit;

            } else {
                nextRow[r-1] = r;
                nextRow[r] = groupDigit[r-1];
                clearArray( groupDigit  );
                break;
            }

            lastDigit = currentDigit;

        }

        copyArray( nextRow, currentRow);
        clearArray( nextRow );
        printArrayAndFilterZeros( currentRow );

        //currentRow[++rowSize] = 1;

        printf("\n");
    }


    return 0;
}

