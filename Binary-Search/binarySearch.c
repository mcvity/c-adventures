#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "Selection-Sort.h"
#define ARR_ALLOCATION_LIMIT 20
#define ARR_ALLOCATION_MIN 1
#define STR_LIMIT 120

int binarySearch(short unsigned int* values, unsigned short int searchValue, unsigned short int midOffset, unsigned short int actualLen) {
    unsigned short int middle = values[midOffset];

    if(midOffset < 0 || midOffset > actualLen) {
        return -1;
    }

    if(values[midOffset] == searchValue)
        return midOffset;
    else if ((searchValue > values[midOffset - 1] && searchValue < values[midOffset + 1]) || searchValue == 0)
        return -1;
    else if(middle == searchValue)
        return midOffset / 2;
    else if(searchValue > middle)
        return binarySearch(values, searchValue, midOffset + 1, actualLen);
    else
        return binarySearch(values, searchValue, midOffset - 1, actualLen);
}

int lengthCheck(int al) {
    if(al < ARR_ALLOCATION_MIN) {
        fprintf(stderr, "you must specify at least %d indices\n", ARR_ALLOCATION_MIN);
        return 0;
    }

    if(al > ARR_ALLOCATION_LIMIT) {
        fprintf(stderr, "Array Allocation limit exceeded (%d)\n", ARR_ALLOCATION_LIMIT);
        return 0;
    }

    return 1;
}

int isValid(char* al) {
    unsigned short int tmpDigit = 0;

    if(!isdigit(*al) || isblank(*al)) {
        fprintf(stderr, "bad character\n");
        return 0;
    }

    tmpDigit = atoi(al);

    if(tmpDigit <= 0) {
        fprintf(stderr, "indices must be larger than 0\n");
        return 0;
    }

    if(tmpDigit >= USHRT_MAX) {
        fprintf(stderr, "max limit exceeded (%d)\n", USHRT_MAX);
        return 0;
    }

    return 1;
}

void extract(char* s, unsigned short int* array, unsigned short int len) {
    char *token = strtok(s, ",");
    int counter = 0;

    for(int iterator = 0 ; token != NULL && counter < len ; iterator++ && counter++) {
        if(!isValid(token))
            exit(1);
        int intToken = atoi(token);
        array[iterator] = intToken;
        token = strtok(NULL, ",");
    }
}

int main() {
    unsigned short int* values, len = 0, search;
    char s[STR_LIMIT] = "";

    fgets(s, STR_LIMIT, stdin);
    scanf("%hd", &search);

    for (int i = 0; i < STR_LIMIT && s[i] != '\0' && s[i] != '\n' ;i++)
        s[i] == ',' && len++;

    if(!lengthCheck(len))
        return 1;

    values = (unsigned short int*)calloc(len, sizeof(int));
    extract(s, values, len);

    selectionSort(values, len + 1);

    int res = binarySearch(values, search, len / 2, len);
    printf("%d\n", res);

    free(values);
}