#include <stdio.h>
#include <string.h>


int getArrayLength(int *array) {
    return ( sizeof(&array) / sizeof(&array[0])); // Something wrong here
}

void printArray(int *array, char *symbol) {
    printf(symbol);
    for(int i = 0; i < getArrayLength(array); i++ ) {
        printf(" %d",array[i]);
    }
}

void printArrayAndFilterZeros(int *array) {
    for(int i = 0; i < getArrayLength(array); i++ ) {
        if(array[i] != 0) printf(" %d",array[i]);
    }
}

void clearArray(int *array) {
    for(int i = 0; i < getArrayLength(array); i++ ) {
        array[i] = 0;
    }
}

void copyArray(int *src, int *destiny) {

    for(int i = 0; i < getArrayLength(src); i++ ) {
        destiny[i] = src[i];
    }
}

int main() {

    int rowSize = 0;
    int currentRow[6] = { 1, 0, 0, 0, 0, 0 };
    int lookRow[6] = { 0, 0, 0, 0, 0, 0 };
    int groupDigit[6] = { 0, 0, 0, 0, 0, 0 };
    int nextRow[6] = { 0, 0, 0, 0, 0, 0 }; 

    for(int row = 0; row < 3; row++) {

        int currentDigit = currentRow[0];
        int lastDigit = currentRow[0];

        for(int r = 0; r < getArrayLength(currentRow) ; r++ ) {

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

