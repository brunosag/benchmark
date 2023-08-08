#ifndef AVL_H
#define AVL_H

#include "common.h"

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

struct AVLTree *createAVLTree();
void destroyAVLTree(struct AVLTree *tree);
void insertAVL(struct AVLTree *tree, int key);
void printAVL(struct AVLTree *tree);
int findMinAVL(struct AVLTree *tree);
int findMaxAVL(struct AVLTree *tree);
double findAverageAVL(struct AVLTree *tree);
KeyFrequency *findXMostFrequentAVL(AVLTree *tree, int X, int data_size);

#endif /* AVL_H */
