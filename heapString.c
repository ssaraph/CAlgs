#include <stdio.h>
#include <stdlib.h> // For exit
#include <string.h> // For strcmp

#include "readinput.c"

#define MAXLINES 300000

// Heap sort for strings.

// Assuming heap indexing starts at 0, not 1.
int parent(int i) {
    if (i > 0) 
        return (i-1)/2;
    else
        return -1;
}
int left(int i) {
    return (i << 1) + 1;
}
int right(int i) {
    return (i << 1) + 2;
}

// Swap entries at index1 and index2.
void swap(char *data[], int index1, int index2) {
    if (index1 == index2) {
	return;
    }
    char *tmp;
    tmp = data[index1];
    data[index1] = data[index2];
    data[index2] = tmp;
}

// Given that trees rooted at left(i) and right(i) are already heaps,
// make the tree rooted at i a heap. 
void maxHeapify(char *data[], int i, int heapSize) {
    if (heapSize < 2) return;

    int largest = i;
    int leftIndex = left(i);
    int rightIndex = right(i);

    if ((leftIndex < heapSize) && (strcmp(data[leftIndex], data[i]) > 0)) {
	largest = leftIndex;
    }
    if ((rightIndex < heapSize) && (strcmp(data[rightIndex], data[largest]) > 0)) {
	largest = rightIndex;
    }
    if (largest != i) {
	swap(data, largest, i);
	maxHeapify(data, largest, heapSize);
    }
}

// Build heap from array of ints.
void buildHeap(char *data[], int heapSize) {
    if (heapSize < 2) return;

    int i;
    // All heap elements after the parent of the last node must be leaves (and therefore heaps, trivially).
    // Also, these are the only leaves. 
    for(i = parent(heapSize-1); i >=0; i--) {
	maxHeapify(data, i, heapSize);
    }
}

// Covert heap into sorted array.
void heapSort(char *data[], int heapSize) {
    if (heapSize < 2) return;
    
    int lastIndex;
    int i; 
    for (lastIndex = heapSize-1; lastIndex > 0; lastIndex--) {
	swap(data, 0, lastIndex);
	maxHeapify(data, 0, lastIndex);
    }
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        char *exArr[] = {"never", "may", "losing", "kingship", "justify", "indiscriminate", "hatred", "granted", "faith", "even",
                                        "death", "can", "bring", "absolution"};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        buildHeap(exArr, size);
	heapSort(exArr, size);

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
	buildHeap(lines, nlines);
	heapSort(lines, nlines);

        for(i = 0; i < nlines; i++) {
            printf("%s", lines[i]);
        }
    }
    else {
        printf("Please provide at most one argument");
    }
}
