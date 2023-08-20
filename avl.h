#ifndef AVL_H
#define AVL_H

#include "main.h"

// Node structure for AVL Tree
typedef struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
    int size;
} AVLNode;

// AVL Tree ADT
typedef struct AVLTree
{
    struct AVLNode *root;
} AVLTree;

struct AVLTree *createAVLTree(); // Main ADT functions
void destroyAVLTree(struct AVLTree *tree);
void insertAVL(struct AVLTree *tree, int key);
void printAVL(struct AVLTree *tree);

void insertDataAVL(AVLTree *tree, int *dataset, int dataSize); // Benchmark specific functions
int findMinAVL(struct AVLTree *tree);
int findMaxAVL(struct AVLTree *tree);
double calculateAverageAVL(struct AVLTree *tree);
KeyFrequency *findXMostFrequentAVL(AVLTree *tree, int X, int dataSize);

#endif /* AVL_H */
