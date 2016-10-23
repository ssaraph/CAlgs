#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 16

struct stack {
    int *storage;
    int topIndex;
    size_t maxSize;
};

// Allocate a new stack with array size MAXSIZE.
struct stack * stackAlloc() {

    struct stack *s = (struct stack *) malloc(sizeof(struct stack));
    if (s == NULL) {
	fprintf(stderr, "Error: unable to allocate space for struct stack.\n");
	exit(1);
    }

    s->storage = (int *) malloc(sizeof(int)*MAXSIZE);
    if (s->storage == NULL) {
	fprintf(stderr, "Error: unable to allocate space for stack storage.\n");
	exit(1);
    }

    s->topIndex = -1;
    s->maxSize = MAXSIZE;
    return s;
}

// Returns 1 if stack is empty, 0 otherwise.
int stackEmpty(struct stack *s) {
    return s->topIndex == -1 ? 1 : 0;
}

// Puts value on end of stack, and resizes stack if stack is full.
void stackPush(struct stack *s, int value) {

    int *tmp;
    // Need to reallocate space because stack is full.
    if ((s->topIndex+1) >= s->maxSize) {
	tmp = realloc(s->storage, sizeof(int) * s->maxSize * 2);
	if (tmp == NULL) {
	    fprintf(stderr, "Error: stack full and unable to allocate more memory.\n");
	    exit(1);
	}
	s->storage = tmp;
	s->maxSize *= 2;
    }

    s->topIndex += 1;
    s->storage[s->topIndex] = value;
}

// Pops values from stack, and resizes stack to if stack is mostly empty.
int stackPop(struct stack *s) {

    int retval, maxSize;

    if (stackEmpty(s)) {
	fprintf(stderr, "Error: attempting to pop empty stack.\n");
	exit(1);
    }	

    s->topIndex -= 1;
    retval = s->storage[s->topIndex+1];
    maxSize = s->maxSize;

    if ((maxSize > MAXSIZE) && ( (s->topIndex+1) * 4 < maxSize )) {
	s->storage = realloc(s->storage, sizeof(int) * (maxSize/2));
	s->maxSize /= 2;
    }

    return retval;
}

void stackPrint(struct stack *s) {

    int i;
    for(i = 0; i <= s->topIndex; i++) {
        printf("%d ", s->storage[i]);
    }
    printf("\n");
}

int main() {

    struct stack *s = stackAlloc();
    int arr[35] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    int i;

    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
	stackPush(s, arr[i]);
	stackPrint(s);
	printf("Max size of stack: %lu Number of elements in stack: %d\n\n", s->maxSize, s->topIndex+1);
    }

    for(;i > 0; i--) {
	stackPop(s);
	stackPrint(s);
	printf("Max size of stack: %lu Number of elements in stack: %d\n\n", s->maxSize, s->topIndex+1);
    }

}
