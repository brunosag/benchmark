#ifndef AVL_H
#define AVL_H

// Node structure for AVL Tree
struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
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

#endif /* AVL_H */
