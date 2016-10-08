#include <stdio.h>
#include <stdlib.h> // For exit

#include "readinput.c"

#define MAXINTS 300000

// Quick sort for integers.

void swap(int *data, int index1, int index2);

// Provide array of integers, and the indices, inclusive, between which to sort.
void quickSort(int *data, int low, int high) {

    if (high <= low) {					// One element, already sorted.
	return;
    }

    /*
    int pivotIndex = selectPivot(data, low, high);  	// Pivot selection step
    swap(data, low, pivotIndex);
    */

    // Here we just use leftmost entry as the pivot.
    int pivot = data[low];

    int scanIndex, swapIndex;
    scanIndex = swapIndex = low + 1;

    // Skip over values that are <= pivot
    while ((scanIndex <= high) && (data[scanIndex] <= pivot)) {
	scanIndex++;
	swapIndex++;
    }

    while (scanIndex <= high) {
	if (data[scanIndex] < pivot) {
	    swap(data, swapIndex, scanIndex);
	    swapIndex++;
	}
	scanIndex++;
    }

    // Finally, swap the pivot into the proper place.
    swap(data, low, swapIndex - 1);

    // The pivot is now in the correct place.
    quickSort(data, low, swapIndex-2);
    quickSort(data, swapIndex, high);
}
// Swap data between two indices in array.
void swap(int *data, int index1, int index2) {
    if (index1 == index2) {
	return;
    }
    int tmp;
    tmp = data[index1];
    data[index1] = data[index2];
    data[index2] = tmp;
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        int exArr[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        // quickSort takes the indices between which to sort, inclusive.
        quickSort(exArr, 0, size-1);

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
        quickSort(intBuf, 0, nints-1);

        for(i = 0; i < nints; i++) {
            printf("%d ", intBuf[i]);
        }
    }
    else {
	printf("Please provide at most one argument");
    }
}
