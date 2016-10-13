#include <stdio.h>
#include <stdlib.h> // For exit

#include "readinput.c"

#define MAXINTS 300000

// Insertion sort for integers.

void insertionSort(int data[], int startIndex, int endIndex) {

    int i, j;
    int val;
    for(j = startIndex+1; j <= endIndex; j++) {
	val = data[j];
	i = j - 1;
	while ((i >= startIndex) && (val < data[i])) {
	    data[i+1] = data[i];
	    i = i - 1;
	}
	data[i+1] = val;
    }
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        int exArr[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        // insertionSort takes the indices between which to sort, inclusive.
        insertionSort(exArr, 0, size-1);

        for(i = 0; i < size; i++) {
            printf("%d ", exArr[i]);
        }
        printf("\n");
    }
    else if (argc == 2) {
        FILE *fin;
        int intBuf[MAXINTS];
	int nints;

	fin = fopen(argv[1], "r");
	if (fin == NULL) {
	    fprintf(stderr, "Error: couldn't open file.\n");
	    exit(1);
	}

	nints = readints(fin, intBuf, MAXINTS);
        insertionSort(intBuf, 0, nints-1);

        for(i = 0; i < nints; i++) {
            printf("%d ", intBuf[i]);
        }
    }
    else {
        printf("Please provide at most one argument");
    }
}
