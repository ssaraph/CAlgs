#ifndef QUEUE_GENERIC_H
#define QUEUE_GENERIC_H

#include <stdio.h>
#include <stdlib.h>

struct queueNode {
    void *data;
    struct queueNode *next;
};

struct queue {
    struct queueNode *head;
    struct queueNode *tail;
};

struct queue * queueAlloc();

// Assumes void *data has already been allocated and initialized.
struct queueNode * queueNodeAlloc(void *data);

int queueIsEmpty(struct queue *q);
// Inserts element at the tail of the queue.
void enqueue(struct queue *q, void *data);
// Removes element from the head of the queue.
void * dequeue(struct queue *q);
// The second argument is a pointer to a function that prints the data type in the queue.
void queuePrint(struct queue * q, void (*pf) (void *));

#endif
