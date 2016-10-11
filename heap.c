#include <stdio.h>
#include <stdlib.h> // For exit

#include "readinput.c"

#define MAXINTS 300000

// Heap sort for integers.

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
void swap(int data[], int index1, int index2) {
    if (index1 == index2) {
	return;
    }
    int tmp;
    tmp = data[index1];
    data[index1] = data[index2];
    data[index2] = tmp;
}

// Given that trees rooted at left(i) and right(i) are already heaps,
// make the tree rooted at i a heap. 
void maxHeapify(int data[], int i, int heapSize) {
    if (heapSize < 2) return;

    int largest = i;
    int leftIndex = left(i);
    int rightIndex = right(i);

    if ((leftIndex < heapSize) && (data[leftIndex] > data[i])) {
	largest = leftIndex;
    }
    if ((rightIndex < heapSize) && (data[rightIndex] > data[largest])) {
	largest = rightIndex;
    }
    if (largest != i) {
	swap(data, largest, i);
	maxHeapify(data, largest, heapSize);
    }
}

// Build heap from array of ints.
void buildHeap(int data[], int heapSize) {
    if (heapSize < 2) return;

    int i;
    // All heap elements after the parent of the last node must be leaves (and therefore heaps, trivially).
    // Also, these are the only leaves. 
    for(i = parent(heapSize-1); i >=0; i--) {
	maxHeapify(data, i, heapSize);
    }
}

// Covert heap into sorted array.
void heapSort(int data[], int heapSize) {
    if (heapSize < 2) return;
    
    int lastIndex;
    int i; 
    for (lastIndex = heapSize-1; lastIndex > 0; lastIndex--) {
	swap(data, 0, lastIndex);
	maxHeapify(data, 0, lastIndex);
        /*for(i = 0; i < heapSize; i++) {
	    printf("%d ", data[i]);
	}*/
	printf("\n");
    }
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        int exArr[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        buildHeap(exArr, size);
	heapSort(exArr, size);

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
	buildHeap(intBuf, nints);
	heapSort(intBuf, nints);

        for(i = 0; i < nints; i++) {
            printf("%d ", intBuf[i]);
        }
    }
    else {
        printf("Please provide at most one argument");
    }
}
