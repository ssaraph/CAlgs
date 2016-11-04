#include <stdio.h>
#include <stdlib.h>

#include "queueGeneric.h" 	// For binaryTreePrint function.
#include <math.h>		// For binaryTreePrint function.

/*
Example of an implementation of a binary search tree. In this example, the key is an integer.
Supports dynamic set operations:
Min
Max
Successor
Predecessor
Search
Insert
Delete

The binary search tree has the following structure: Each node has at most two children. Let
n be an arbirary node. Then n.left.key <= n.key, and n.right.key >= n.key, if they exist.
*/

struct tnode {
    int key;
    struct tnode *left;
    struct tnode *right;
    struct tnode *parent;
};

struct tnode * talloc(int key, struct tnode *parent) {
    struct tnode *p = (struct tnode *) malloc (sizeof(struct tnode));
    if (p == NULL) {
	fprintf(stderr, "Error: couldn't allocate space for new tnode.\n");
	exit(1);
    }
    p->key = key;
    p->left = NULL;
    p->right = NULL;
    p->parent = parent;

    return p;
}

// Returns pointer to tnode with min key.
struct tnode * treeMin(struct tnode *tp) {
    struct tnode *p = tp;
    while (p->left != NULL) {
	p = p->left;
    }
    return p;
}

// Returns pointer to tnode with max key.
struct tnode * treeMax(struct tnode *tp) {
    struct tnode *p = tp;
    while (p->right != NULL) {
	p = p->right;
    }
    return p;
}

// Returns pointer to successor of root.
struct tnode * treeSuccessor(struct tnode *tp) {
    // If root has a right child, the successor of root is the
    // minimum of the tree rooted at the right child. 
    if (tp->right != NULL) {
	return treeMin(tp->right);
    }
    // Else, if root has a successor, it is the lowest ancestor of root
    // whose left child is also an ancestor of root. (Practically, keep
    // going up the tree, and stop after the first time we go right).
    // (Nodes are considered ancestors of themselves).
    struct tnode *p = tp->parent;
    while ((p != NULL) && (tp == p->right)) {
	tp = p;
	p = p->parent;
    }
    return p;
}

// Returns pointer to predecessor of root.
struct tnode * treePredecessor(struct tnode *tp) {
    if(tp->left != NULL) {
	return treeMax(tp->left);
    }

    struct tnode *p = tp->parent;
    while ((p != NULL) && (tp == p->left)) {
	tp = p;
	p = p->parent;
    }
    return p;
}

// Returns pointer to a tnode with matching key, or NULL.
struct tnode * treeSearch(struct tnode *root, int key) {

    if ((root == NULL) || (root->key == key)) {
	return root;
    }

    // Recursive method
    /* 
    if (key < root->key) {
	return treeSearch(root->left, key);
    }
    else {
	return treeSearch(root->right, key);
    }
    */
    
    // Iterative method
    while ((root->key != key) && (root != NULL)) {
    	if (key < root->key) {
	    root = root->left;
	}
	else {
	    root = root->right;
	}
    }
    return root;
}

// Assumes that the input tnode has already been initialized.
// Returns pointer to the root of the tree.
struct tnode * treeInsert(struct tnode *root, struct tnode *newNode) {
    struct tnode *p = root;
    struct tnode *parent = NULL;


    // Empty tree
    if (p == NULL) {
        newNode->parent = NULL;
	return newNode;
    }

    while (p != NULL) {
        parent = p;
	if (newNode->key <= p->key) {
	    p = p->left;
	}
	else {
	    p = p->right;
	}
	//printf("p NULL? %d\n", p==NULL);
	//printf("newNode NULL? %d\n", newNode==NULL);
    }

    newNode->parent = parent;
    if (newNode->key <= parent->key) {
	parent->left = newNode;
    }
    else {
	parent->right = newNode;
    }
    return root;
}

// Create new node with key and insert it into tree pointed at root
struct tnode * treeInsertKey(struct tnode *root, int key) {
    struct tnode *tp = talloc(key, NULL);
    return treeInsert(root, tp);
}

// Makes the parent of t1 point to t2 as a child instead of t1, and changes
// the parent of t2 to be the original parent of t1.
// Returns the new root of the tree (which most often did not change).
struct tnode * transplant(struct tnode *root, struct tnode *t1, struct tnode *t2) {

    // Transplant location is NULL. This makes no sense.
    if (t1 == NULL) {
	fprintf(stderr, "Error: Transplant location is NULL.\n");
	exit(1);
    }

    struct tnode *newRoot = root;
    // Root is the transplant location, so we have a new root.
    if (root == t1) {
	newRoot = t2;
    }
    else if (t1 == t1->parent->right) {
	t1->parent->right = t2;
    }
    else {
	t1->parent->left = t2;
    } 
    if (t2 != NULL) {
	t2->parent = t1->parent;
    }
    return newRoot;
}

// Assumes pointer to tnode to be deleted is passed in.
// Returns pointer to the root of the tree.
struct tnode * treeDelete(struct tnode *root, struct tnode *toDelete) {

    struct tnode * newRoot = root;

    if (toDelete == NULL) {
	fprintf(stderr, "Error: trying to delete NULL node.\n");
	exit(1);
    }

    // toDelete has no children, or only a right child.
    if (toDelete->left == NULL) {
	newRoot = transplant(root, toDelete, toDelete->right);
	// Note: freeing NULL does nothing.
	free(toDelete);
    }
    // toDelete has only a left child.
    else if (toDelete->right == NULL) {
	newRoot = transplant(root, toDelete, toDelete->left);
	free(toDelete);
    }
    // toDelete has two children.
    else {
        // Equivalent to treeSuccessor(toDelete) in this case.
        struct tnode * successor = treeMin(toDelete->right);
	if(successor->parent != toDelete) {
	    newRoot = transplant(root, successor, successor->right);
	    successor->right = toDelete->right;
	    toDelete->right->parent = successor;
	}
	newRoot = transplant(root, toDelete, successor);
	toDelete->left->parent = successor;
	successor->left = toDelete->left;
	free(toDelete);
    }
    return newRoot;

}

struct tnode * treeDeleteKey(struct tnode *root, int toDeleteKey) {
    
    struct tnode *toDelete = treeSearch(root, toDeleteKey);
    if (toDelete == NULL) {
	return root;
    }
    else {
	return treeDelete(root, toDelete);
    }
}

void inOrderPrint(struct tnode *tp) {

    if (tp == NULL) {
    	return;
    }
    inOrderPrint(tp->left);
    printf("%d ", tp->key);
    inOrderPrint(tp->right);
    return;
}


/****** Functions for printing the binary tree. ******/
struct printNode {
    struct tnode *tp;
    int depth;
};

// Return maximum width of a key in the tree (in number of characters when printed).
int maxKeyWidth(struct tnode *tp) {
    if (tp == NULL) {
	return 0;
    }
    int width = 1;
    if (tp->key != 0) {
    	width = log10(tp->key) + 1;
    }
    int lval = maxKeyWidth(tp->left);
    int rval = maxKeyWidth(tp->right);
    rval = (lval > rval) ? lval : rval;
    return (width > rval) ? width : rval;
}

// If tree is empty, returns -1. If tree has one node, returns 0.
int treeHeight(struct tnode *tp) {
    if (tp == NULL) {
	return -1;
    }
    else {
        int lval = treeHeight(tp->left);
	int rval = treeHeight(tp->right);
	return (lval > rval) ? (lval + 1) : (rval + 1);
    }
}

struct printNode * printNodeAlloc(struct tnode *tp, int depth) {
    struct printNode *p = (struct printNode *) malloc(sizeof(*p));
    if (p == NULL) {
	fprintf(stderr, "Error: couldn't allocate space for new printNode.\n");
	exit(1);
    }
    p->tp = tp;
    p->depth = depth;
    return p;
}

void printSpaces(int n, int c) {
    int i;
    for(i = 0; i < n; i++) {
        fputc(c, stdout);
    }
}

void binaryTreePrint(struct tnode *tp) {
    if (tp == NULL) {
	printf("Empty tree.\n");
	return;
    }
    int currentDepth = 0;
    int height = treeHeight(tp);
    int keyWidth = maxKeyWidth(tp);
    // Two digits should be sufficient for keyWidth, i.e. "%##d".
    char formatString[5];
    if (keyWidth > 99) {
	sprintf(formatString, "%%99d");
    }
    else {
	sprintf(formatString, "%%%dd", keyWidth);
    }


    struct queue *nodeQueue = queueAlloc(); 
    enqueue(nodeQueue, printNodeAlloc(tp, 0));

    struct printNode *currentNode;
    int i;
    // Loop condition (currentDepth <= height) allows us to add NULL nodes (i.e. currentNode->tp == NULL) 
    // to the queue in order to keep alignment for non-complete trees correct. Ordinarily, I would use 
    // condition !queueIsEmpty(nodeQueue) instead, but this won't work because I am adding NULL nodes to 
    // the queue so the queue will never be empty.

    printf("Tree Height: %d\n", height);
    while (currentDepth <= height) {
        currentNode = (struct printNode *) dequeue(nodeQueue);
	if (currentNode->depth != currentDepth) {
	    currentDepth += 1;
	    printf("\n");
	}
	/*
	Want:
	(Width of all keys on level) + (Width of additional space) = (2^height)*keyWidth
	Solve for Width of additional space from there.
	*/
	// General spaces for each level
	printSpaces(pow(2, height-currentDepth), ' ');
	// Additional spaces for missing keys
	printSpaces(((pow(2, height) - pow(2, currentDepth))*keyWidth)/(pow(2, currentDepth+1)), ' ');
	if (currentNode->tp != NULL) {
	    printf(formatString, currentNode->tp->key);
	}
	else {
	    printSpaces(keyWidth, ' ');
	}
	// Additional spaces for missing keys
	printSpaces(((pow(2, height) - pow(2, currentDepth))*keyWidth)/(pow(2, currentDepth+1)), ' ');
	// General spaces for each level
	printSpaces(pow(2, height-currentDepth), ' ');
	if (currentNode->tp != NULL) {
	    enqueue(nodeQueue, printNodeAlloc(currentNode->tp->left, currentDepth+1));
	    enqueue(nodeQueue, printNodeAlloc(currentNode->tp->right, currentDepth+1));
	}
	// Adding NULL nodes to queue for alignment purposes.
	else {
	    enqueue(nodeQueue, printNodeAlloc(NULL, currentDepth+1));
	    enqueue(nodeQueue, printNodeAlloc(NULL, currentDepth+1));
	}
    }
    while (!queueIsEmpty(nodeQueue)) {
	free(dequeue(nodeQueue));
    }
    free(nodeQueue);
    printf("\n");
}

int main() {

    /*
	NOTE: Right now these test cases are not very enlightening because it is not easy
	to see what is happening to the tree. I need to write a pretty print function for the
	binary tree so it is easy to see what is happening.
    */

    struct tnode *root = NULL;

    binaryTreePrint(root);
    root = treeInsertKey(root, 50);
    binaryTreePrint(root);
    root = treeInsertKey(root, 30);
    binaryTreePrint(root);
    root = treeInsertKey(root, 80);
    binaryTreePrint(root);
    root = treeInsertKey(root, 10);
    binaryTreePrint(root);
    root = treeInsertKey(root, 40);
    binaryTreePrint(root);
    root = treeInsertKey(root, 60);
    binaryTreePrint(root);
    root = treeInsertKey(root, 90);
    binaryTreePrint(root);
    root = treeInsertKey(root, 70);
    binaryTreePrint(root);

    printf("\n");

    // Test deletion of leaf
    struct tnode *tmp = treeSearch(root, 70);
    root = treeDelete(root, tmp);

    binaryTreePrint(root);
    printf("\n");

    root = treeInsertKey(root, 70);
    root = treeInsertKey(root, 75);
    root = treeInsertKey(root, 72);

    binaryTreePrint(root);
    printf("\n");

    // Test deletion of node with one child
    tmp = treeSearch(root, 70);
    root = treeDelete(root, tmp);

    binaryTreePrint(root);
    printf("\n");

    root = treeInsertKey(root, 45);

    binaryTreePrint(root);
    printf("\n");

    // Test deletion of node with two children, right child is successor.
    tmp = treeSearch(root, 30);
    root = treeDelete(root, tmp);

    binaryTreePrint(root);
    printf("\n");

    printf("root key %d\n", root->key);

    // Test deletion of node with two children, right child is not successor.
    // (Also test deletion of the root of the tree).
    root = treeDelete(root, root);

    binaryTreePrint(root);
    printf("\n");
    return 0;
}
