#include <stdio.h>
#include <stdlib.h>

#include "queueGeneric.h"

// Argument should be pointer to int.
void printInt(void *n) {
    printf("%d\n", *((int *) n));
}

// Argument should be pointer to double.
void printDouble(void *d) {
    printf("%lf\n", *((double *) d));
}

int main() {

    struct queue * queueInt = queueAlloc();
    struct queue * queueDouble = queueAlloc();

    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int i;
    int *n;

    for(i = 0; i < sizeof(arr)/sizeof(arr[0]) ; i++) {
        n = (int *) malloc(sizeof(int));
        *n = arr[i];
        enqueue(queueInt, n);
    }
    queuePrint(queueInt, printInt);
    for(i = 0; i < 5; i++) {
	n = dequeue(queueInt);
	printf("Dequeued: %d\n", *((int *) n));
    }
    queuePrint(queueInt, printInt);

    double arr2[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
    double *d;

    for(i = 0; i < sizeof(arr2)/sizeof(arr2[0]) ; i++) {
        d = (double *) malloc(sizeof(double));
        *d = arr2[i];
        enqueue(queueDouble, d);
    }
    queuePrint(queueDouble, printDouble);
    while (!queueIsEmpty(queueDouble)) {
	d = dequeue(queueDouble);
	printf("Dequeued: %lf\n", *((double *) d));
    }
    queuePrint(queueDouble, printDouble);
    for(i = 0; i < sizeof(arr2)/sizeof(arr2[0]) ; i++) {
        d = (double *) malloc(sizeof(double));
        *d = arr2[i];
        enqueue(queueDouble, d);
    }
    queuePrint(queueDouble, printDouble);
    return 0;
}

