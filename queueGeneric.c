#include <stdio.h>
#include <stdlib.h>

#include "queueGeneric.h"

struct queue * queueAlloc() {
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    if (q == NULL) {
        fprintf(stderr, "Error: unable to allocate space for struct queue.\n");
        exit(1);
    }
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// Assumes void *data has already been allocated and initialized.
struct queueNode * queueNodeAlloc(void *data) {
    struct queueNode *p = (struct queueNode *) malloc(sizeof(struct queueNode));
    if (p == NULL) {
        fprintf(stderr, "Error: unable to allocate space for struct queueNode.\n");
        exit(1);
    }
    p->data = data;
    p->next = NULL;
    return p;
}

int queueIsEmpty(struct queue *q) {
    if(q == NULL) {
	fprintf(stderr, "Error: attempting to examine NULL queue.\n");
	exit(1);
    }
    if (q->head == NULL) {
	return 1;
    }
    return 0;
}

// Inserts element at the tail of the queue.
void enqueue(struct queue *q, void *data) {
    if (q == NULL) {
	fprintf(stderr, "Error: attempting to enqueue to NULL queue.\n");
	exit(1);
    }
    // Queue is empty.
    if (q->head == NULL) {
	q->head = queueNodeAlloc(data);
	q->tail = q->head;
    }
    // Queue has at least one element.
    else {
	q->tail->next = queueNodeAlloc(data);
	q->tail = q->tail->next;
    }
}

// Removes element from the head of the queue.
void * dequeue(struct queue *q) {
    if (q == NULL) {
	fprintf(stderr, "Error: attempting to dequeue from NULL queue.\n");
	exit(1);
    }
    // Queue is empty.
    if (queueIsEmpty(q)) {
	fprintf(stderr, "Error: attempting to dequeue from empty queue.\n");
	exit(1);
    }

    struct queueNode *oldHead = q->head;
    void *retval = q->head->data;

    // Queue has exactly one element.
    if (q->head == q->tail) {
	q->head = NULL;
	q->tail = NULL;
    }
    // Queue has more than one element.
    else {
    	q->head = q->head->next;
    }
    free(oldHead);
    return retval;
}

// The second argument is a pointer to a function that prints the data type in the queue.
void queuePrint(struct queue * q, void (*pf) (void *)) {

    if (q == NULL) {
	return;
    }
    struct queueNode *itr = q->head;
    while (itr != NULL) {
	pf(itr->data);
	itr = itr->next;
    }
}

