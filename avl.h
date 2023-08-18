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

void insertOrderedDataAVL(AVLTree *avlTree, int data_size); // Benchmark specific functions
void insertUnorderedDataAVL(AVLTree *avlTree, int data_size);
int findMinAVL(struct AVLTree *tree);
int findMaxAVL(struct AVLTree *tree);
double calculateAverageAVL(struct AVLTree *tree);
KeyFrequency *findXMostFrequentAVL(AVLTree *tree, int X, int data_size);

#endif /* AVL_H */
