#include <stdio.h>
#include <string.h> // For strcmp
#include <stdlib.h> // For exit

#include "readinput.c"

#define MAXLINES 300000

// Insertion sort for strings.

void insertionSort(char *data[], int startIndex, int endIndex) {

    int i, j;
    char *string;
    for(j = startIndex+1; j <= endIndex; j++) {
	i = j - 1;
	string = data[j];
	while ((i >= startIndex) && (strcmp(string, data[i]) < 0)) {
	    data[i+1] = data[i];
	    i = i - 1;
	}
	data[i+1] = string;
    }
}

int main(int argc, char *argv[]) {

    int i, j;
    if (argc == 1) {
        char *exArr[] = {"never", "may", "losing", "kingship", "justify", "indiscriminate", "hatred", "granted", "faith", "even",
                                        "death", "can", "bring", "absolution"};
        int size = sizeof(exArr)/sizeof(exArr[0]);

        // insertionSort takes the indices between which to sort, inclusive.
        insertionSort(exArr, 0, size-1);

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
        insertionSort(lines, 0, nlines-1);

        for(i = 0; i < nlines; i++) {
            printf("%s", lines[i]);
        }
    }
    else {
        printf("Please provide at most one argument");
    }
}
