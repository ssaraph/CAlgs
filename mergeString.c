#include <stdio.h>
#include <string.h> // For strcmp
#include <stdlib.h> // For exit

#include "readlines.c"

#define MAXLINES 300000

void copyArray(char *dataFrom[], char *dataTo[], int size, int start);
void merge(char *data[], int low, int mid, int high);

// Provide the array of integers, and the indices, inclusive, between which to sort.
void mergeSort(char *data[], int low, int high) {

    //printf("low:%d high:%d\n", low, high);

    if (high <= low) { 			// One element base case
	return;
    }

    int mid = (high - low)/2 + low;
    mergeSort(data, low, mid);
    mergeSort(data, mid + 1, high);
    merge(data, low, mid, high);
}

void merge(char *data[], int low, int mid, int high) {

    //printf("merge(low: %d, mid: %d, high: %d)\n", low, mid, high);

    int i = low;
    int j = mid + 1;
    int k = 0;

    int size = high - low + 1;

    char *copy[size];

    while ((i <= mid) && (j <= high)) {
	copy[k] = (strcmp(data[i], data[j]) <= 0) ? data[i++] : data[j++];  // Only the "true" branch gets evaluated and incremented
	k += 1;
    }
    while (i <= mid) {
        copy[k++] = data[i++];
    }
    while (j <= high) {
	copy[k++] = data[j++];
    }

    copyArray(copy, data, size, low);

}

// Copy arrays
void copyArray(char *dataFrom[], char *dataTo[], int size, int start) {
    int i;
    for(i = 0; i < size; i++) {
	dataTo[start+i] = dataFrom[i];
    }
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        char *exArr[] = {"never", "may", "losing", "kingship", "justify", "indiscriminate", "hatred", "granted", "faith", "even",
                                        "death", "can", "bring", "absolution"};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        // mergeSort takes the indices between which to sort, inclusive.
        mergeSort(exArr, 0, size-1);

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
        // mergeSort takes the indices between which to sort, inclusive.
        mergeSort(lines, 0, nlines-1);

        for(i = 0; i < nlines; i++) {
            printf("%s", lines[i]);
        }
    }
    else {
        printf("Please provide at most one argument");
    }
}
