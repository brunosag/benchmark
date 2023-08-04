#ifndef AVL_H
#define AVL_H

// Node structure for AVL Tree
struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
    int size;
};

// AVL Tree ADT
struct AVLTree
{
    struct AVLNode *root;
};

// Function prototypes
struct AVLTree *createAVLTree();
void destroyAVLTree(struct AVLTree *tree);
void insertAVL(struct AVLTree *tree, int key);
void deleteAVL(struct AVLTree *tree, int key);
void printAVL(struct AVLTree *tree);
int findMinAVL(struct AVLTree *tree);
int findMaxAVL(struct AVLTree *tree);
double findAverageAVL(struct AVLTree *tree);
static int countAVLNodes(struct AVLNode *node);

#endif /* AVL_H */
