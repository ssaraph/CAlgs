#include <stdio.h>
#include <string.h> // For strcmp
#include <stdlib.h> // For exit

#include "readlines.c"

#define MAXLINES 300000 

void swap(char *data[], int index1, int index2);

// Provide array of integers, and the indices, inclusive, between which to sort.
void quickSort(char *data[], int low, int high) {

    if (high <= low) {					// One element, already sorted.
	return;
    }

    /*
    int pivotIndex = selectPivot(data, low, high);  	// Pivot selection step
    swap(data, low, pivotIndex);
    */

    // Here we just use leftmost entry as the pivot.
    char *pivot = data[low];

    int scanIndex, swapIndex;
    scanIndex = swapIndex = low + 1;

    // Skip over values that are <= pivot
    while ((scanIndex <= high) && (strcmp(data[scanIndex],pivot) <= 0)) {
	scanIndex++;
	swapIndex++;
    }

    while (scanIndex <= high) {
	if (strcmp(data[scanIndex],pivot) < 0) {
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
void swap(char *data[], int index1, int index2) {
    if (index1 == index2) {
	return;
    }
    // Note, we only rearrange the pointers, not what they actually point to.
    char *tmp;
    tmp = data[index1];
    data[index1] = data[index2];
    data[index2] = tmp;
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        char *exArr[] = {"never", "may", "losing", "kingship", "justify", "indiscriminate", "hatred", "granted", "faith", "even",
					"death", "can", "bring", "absolution"};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        // quickSort takes the indices between which to sort, inclusive.
        quickSort(exArr, 0, size-1);

        for(i = 0; i < size; i++) {
            printf("%s ", exArr[i]);
        }
        printf("\n");
    }
    else if (argc == 2) {
	FILE *fin;
	char *lines[MAXLINES];
	int nlines;

	fin = fopen(argv[1], "r");
	if (fin == NULL) {
	    fprintf(stderr, "Error: couldn't open file.\n");
	    exit(1);
	}

	nlines = readlines(fin, lines, MAXLINES);
        // quickSort takes the indices between which to sort, inclusive.
	quickSort(lines, 0, nlines-1);

	for(i = 0; i < nlines; i++) {
	    printf("%s", lines[i]);
	}
    }
    else {
	printf("Please provide at most one argument");
    }
}
