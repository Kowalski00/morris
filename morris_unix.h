#if !defined(MORRIS_UNIX_H)

#define ROW_SIZE 1024

#define COLOR_DEFAULT  "\x1B[0m"
#define COLOR_RED      "\x1B[31m"
#define COLOR_GRN      "\x1B[32m"
#define COLOR_BLU      "\x1B[34m"

typedef struct lineParameters {
    int lineNumber;
    int currentRow[ROW_SIZE];
    size_t rowLength;
    int *pBitSetColor;
} lineParameters;

int lastColorKey;

int getRandomColorKey(void);

void printLine(struct lineParameters *pParameters, int showDescription);

struct lineParameters createLineParameters(int line, int *pCurrentRow);

char * getColor(int colorKey);

void copyArray(int *pSrc, int *pTarget, size_t len);

#define MORRIS_UNIX_H
#endif
