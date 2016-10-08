#include <stdio.h>

void copyArray(int *dataFrom, int *dataTo, int size, int start);
void merge(int *data, int low, int mid, int high);

// Provide the array of integers, and the indices, inclusive, between which to sort.
void mergeSort(int *data, int low, int high) {

    //printf("low:%d high:%d\n", low, high);

    if (high <= low) { 			// One element base case
	return;
    }

    int mid = (high - low)/2 + low;
    mergeSort(data, low, mid);
    mergeSort(data, mid + 1, high);
    merge(data, low, mid, high);
}

void merge(int *data, int low, int mid, int high) {

    //printf("merge(low: %d, mid: %d, high: %d)\n", low, mid, high);

    int i = low;
    int j = mid + 1;
    int k = 0;

    int size = high - low + 1;

    int copy[size];

    while ((i <= mid) && (j <= high)) {
	copy[k] = (data[i] <= data[j]) ? data[i++] : data[j++];  // Only the "true" branch gets evaluated and incremented
	k += 1;
    }
    while (i <= mid) {
        copy[k++] = data[i++];
    }
    while (j <= high) {
	copy[k++] = data[j++];
    }

/*
    printf("copyArray: ");
    for(i = 0; i < size; i++) {
	printf("%d ", copy[i]);
    }
    printf("\n");
*/
    copyArray(copy, data, size, low);

}

// Copy arrays
void copyArray(int *dataFrom, int *dataTo, int size, int start) {
    int i;
    for(i = 0; i < size; i++) {
	dataTo[start+i] = dataFrom[i];
    }
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        int exArr[] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        // mergeSort takes the indices between which to sort, inclusive.
        mergeSort(exArr, 0, size-1);

        for(i = 0; i < size; i++) {
            printf("%d ", exArr[i]);
        }
        printf("\n");
    }
    else if (argc == 2) {
        FILE *fin;
        int intBuf[100000];
        if((fin = fopen(argv[1], "r")) != NULL) {
            i = 0;
            while(fscanf(fin, "%d", intBuf+i) > 0) {
                i = i + 1;
            }
            mergeSort(intBuf, 0, i-1);
            for(j = 0; j < i; j++) {
                printf("%d ", intBuf[j]);
            }
        }
    }
    else {
        printf("Please provide at most one argument");
    }
}
