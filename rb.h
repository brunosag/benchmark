#ifndef RB_H
#define RB_H

// Color enumeration for Red-Black Tree nodes
enum Color
{
    RED,
    BLACK
};

// Node structure for Red-Black Tree
typedef struct RBNode
{
    int key;
    enum Color color;
    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;
} RBNode;

// Red-Black Tree ADT
typedef struct RBTree
{
    struct RBNode *root;
    struct RBNode *nil; // Sentinel node
} RBTree;

struct RBTree *createRBTree();
void destroyRBTree(struct RBTree *tree);
void insertRB(struct RBTree *tree, int key);
void printRB(struct RBTree *tree);
int findMinRB(struct RBTree *tree);
int findMaxRB(struct RBTree *tree);
double findAverageRB(struct RBTree *tree);

#endif /* RB_H */
