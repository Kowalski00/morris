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
    int digitGroupQuantity = 0;
    int currentRow[] = { 1, 0, 0, 0, 0, 0 };
    int lookRow[] = { 0, 0, 0, 0, 0, 0 };
    int nextRow[] = { 0, 0, 0, 0, 0, 0 }; 

    // PrintArrayAndFilterZeros
    for(int i = 0; i < sizeof(currentRow) / sizeof(currentRow[0]); i++ ) {
        if(currentRow[i] != 0) printf(" %d",currentRow[i]);
    }
    printf("\n");

    for(int row = 0; row < 4; row++) {

        int currentDigit = currentRow[0];
        int lastDigit = currentRow[0];

        for(int r = 0; r < sizeof(currentRow) / sizeof(currentRow[0]) ; r++ ) {

            currentDigit = currentRow[r];

            if(lastDigit == currentDigit) {
                
                digitGroupQuantity++;

            } else {

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

            lastDigit = currentDigit;

        }

        // Copy array
        for(int i = 0; i < sizeof(nextRow) / sizeof(nextRow[0]); i++ ) {
            currentRow[i] = nextRow[i];
        }

        // Clear array
        for(int i = 0; i < sizeof(nextRow) / sizeof(nextRow[0]); i++ ) {
            nextRow[i] = 0;
        }

        // PrintArrayAndFilterZeros
        for(int i = 0; i < sizeof(currentRow) / sizeof(currentRow[0]); i++ ) {
            if(currentRow[i] != 0) printf(" %d",currentRow[i]);
        }

        printf("\n");
    }


    return 0;
}
