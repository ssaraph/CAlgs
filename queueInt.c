#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 16

struct queue {
    int *storage;
    // Index for front of the queue
    int head;
    // Index where next new element is inserted
    int tail;
    int size;
    size_t maxSize;
};

// Allocate a new queue with array size MAXSIZE.
struct queue * queueAlloc() {

    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    if (q == NULL) {
	fprintf(stderr, "Error: unable to allocate space for struct queue.\n");
	exit(1);
    }

    q->storage = (int *) malloc(sizeof(int)*MAXSIZE);
    if (q->storage == NULL) {
	fprintf(stderr, "Error: unable to allocate space for queue storage.\n");
	exit(1);
    }

    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->maxSize = MAXSIZE;
    return q;
}

// Returns 1 if queue is empty, 0 otherwise.
int queueEmpty(struct queue *q) {
    return q->size == 0 ? 1 : 0;
}

// Pushes element on the tail of queue, resizes queue if queue is full.
void enqueue(struct queue *q, int val) {

    int *tmp;
    int i;

    // The queue is full, need to resize.
    if (q->size == q->maxSize) {
	tmp = realloc(q->storage, sizeof(int) * q->maxSize * 2);
	if (tmp == NULL) {
            fprintf(stderr, "Error: queue full and unable to allocate more memory.\n");
            exit(1);
	}
	// Two cases for properly copying queue to new allocation.
        if (q->head != 0) {
	    for(i = 0; i < q->head; i++) {
		tmp[q->maxSize + i] = tmp[i];
	    }
	    q->tail = q->head + q->maxSize;
	}
	// Other case is fine by default.
	q->tail = q->head + q->maxSize;
	q->maxSize *= 2;
        q->storage = tmp;
    }

    q->storage[q->tail] = val;
    q->tail = (q->tail + 1) % q->maxSize;
    q->size += 1;
    //printf("ENQUEUE head: %d tail: %d\n", q->head, q->tail);
}

// Pop element from head of queue, resize queue if mostly empty.
int dequeue(struct queue *q) {
    int retval;
    int i;

    if (queueEmpty(q)) {
	fprintf(stderr, "Error: trying to pop empty queue.\n");
	exit(1);
    }

    retval = q->storage[q->head];
    q->head = (q->head + 1) % q->maxSize;
    q->size -= 1;

    if ((q->maxSize > MAXSIZE) && ((q->size * 4) <  q->maxSize)) {
        // Two cases for properly copying queue to new allocation.
	if (q->head < q->tail) {
	    for(i = q->head; i < q->tail; i++) {
		q->storage[i-q->head] = q->storage[i];
	    }
	}
	else {
	    for(i = 0; i < q->size; i++) {
		q->storage[q->size - 1 - i] = q->storage[(q->tail-1-i+q->maxSize) % q->maxSize];
	    }
	}
	q->head = 0;
	q->tail = q->size;
        q->storage = realloc(q->storage, sizeof(int) * q->maxSize/2);
	q->maxSize /= 2;
    }

    //printf("DEQUEUE head: %d tail: %d\n", q->head, q->tail);
    return retval;
}

void queuePrint(struct queue *q) {
    int i;
    for(i = 0; i < q->size; i++) {
	printf("%d ", q->storage[(q->head+i)%q->maxSize]);
    }
    printf("\n");
}

int main() {

    struct queue *q = queueAlloc();
    int arr[35] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    int i;
    // Uncomment tests below and print statements in enqueue and dequeue for examples.
/*
    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
	enqueue(q, arr[i]);
	queuePrint(q);
	printf("Max size of queue: %lu Number of elements in queue: %d\n\n", q->maxSize, q->size);
    }

    for(;i > 0; i--) {
        dequeue(q);
	queuePrint(q);
	printf("Max size of queue: %lu Number of elements in queue: %d\n\n", q->maxSize, q->size);
    }
    struct queue *r = queueAlloc();

    enqueue(r, 1);
    dequeue(r);
    enqueue(r, 1);
    dequeue(r);
    enqueue(r, 1);
    dequeue(r);
    for(i = 0; i < MAXSIZE; i++) {
	enqueue(r, arr[i]);
	queuePrint(r);
    }
    dequeue(r);
    enqueue(r, MAXSIZE+1);
    queuePrint(r);
    printf("Max size of queue: %lu Number of elements in queue: %d\n\n", r->maxSize, r->size);
    enqueue(r, MAXSIZE+2);
    queuePrint(r);
    printf("Max size of queue: %lu Number of elements in queue: %d\n\n", r->maxSize, r->size);
    enqueue(r, 5);
    enqueue(r, 5);
    enqueue(r, 5);
    enqueue(r, 5);
    queuePrint(r);
*/
}
