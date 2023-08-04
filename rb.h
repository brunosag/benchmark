#ifndef RB_H
#define RB_H

// Color enumeration for Red-Black Tree nodes
enum Color
{
    RED,
    BLACK
};

// Node structure for Red-Black Tree
struct RBNode
{
    int key;
    enum Color color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
};

// Red-Black Tree ADT
struct RBTree
{
    struct RBNode *root;
    struct RBNode *nil; // Sentinel node
};

// Function prototypes
struct RBTree *createRBTree();
void destroyRBTree(struct RBTree *tree);
void insertRB(struct RBTree *tree, int key);
void deleteRB(struct RBTree *tree, int key);
void printRB(struct RBTree *tree);

#endif /* RB_H */
