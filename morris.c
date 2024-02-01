#include<stdio.h>

void printArray(int *array, int length) {
    printf(" # ");
    for(int i = 0; i < length; i++ ) {
        printf(" %d",array[i]);
    }
}

void clearArray(int *array, int length) {
    for(int i = 0; i < length; i++ ) {
        array[i] = 0;
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

        for(int r = 0; r < ( sizeof(currentRow) / sizeof(currentRow[0]) ); r++ ) {

            if(currentDigit == currentRow[r]) {
                
                *(groupDigit+r) = currentRow[r];

            } else {
                nextRow[r-1] = r;
                nextRow[r] = groupDigit[r-1];
                clearArray( groupDigit, ( sizeof(groupDigit) / sizeof(groupDigit[0]))  );
            }

            if(currentRow[r] != 0) {

                printf(" %d",currentRow[r]);
            }


        }
        printArray( nextRow, ( sizeof(nextRow) / sizeof(nextRow[0])) );
        printf("\n");

        currentRow[++rowSize] = 1;
    }


    return 0;
}

