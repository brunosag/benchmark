#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new Red-Black node
struct RBNode *createRBNode(int key, enum Color color)
{
    struct RBNode *node = (struct RBNode *)malloc(sizeof(struct RBNode));
    node->key = key;
    node->color = color;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create an empty Red-Black Tree
struct RBTree *createRBTree()
{
    struct RBTree *tree = (struct RBTree *)malloc(sizeof(struct RBTree));
    tree->nil = createRBNode(0, BLACK);
    tree->root = tree->nil;
    return tree;
}

// Function to free the memory occupied by the Red-Black nodes
void destroyRBNodes(struct RBTree *tree, struct RBNode *node)
{
    if (node != tree->nil)
    {
        destroyRBNodes(tree, node->left);
        destroyRBNodes(tree, node->right);
        free(node);
    }
}

// Function to destroy the Red-Black Tree
void destroyRBTree(struct RBTree *tree)
{
    destroyRBNodes(tree, tree->root);
    free(tree->nil);
    free(tree);
}

// Function to perform a left rotation in the Red-Black Tree
void leftRotateRB(struct RBTree *tree, struct RBNode *x)
{
    struct RBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == tree->nil)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform a right rotation in the Red-Black Tree
void rightRotateRB(struct RBTree *tree, struct RBNode *y)
{
    struct RBNode *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == tree->nil)
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree properties after insertion
void fixInsertRB(struct RBTree *tree, struct RBNode *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct RBNode *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotateRB(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotateRB(tree, z->parent->parent);
            }
        }
        else
        {
            struct RBNode *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotateRB(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotateRB(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Function to insert a key into the Red-Black Tree
void insertRB(struct RBTree *tree, int key)
{
    struct RBNode *z = createRBNode(key, RED);
    struct RBNode *y = tree->nil;
    struct RBNode *x = tree->root;

    while (x != tree->nil)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == tree->nil)
        tree->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    z->left = tree->nil;
    z->right = tree->nil;

    fixInsertRB(tree, z);
}

// Function to print the Red-Black Tree in-order
void inOrderTraversalRB(struct RBTree *tree, struct RBNode *node)
{
    if (node != tree->nil)
    {
        inOrderTraversalRB(tree, node->left);
        printf("%d ", node->key);
        inOrderTraversalRB(tree, node->right);
    }
}

// Function to print the Red-Black Tree (interface function)
void printRB(struct RBTree *tree)
{
    inOrderTraversalRB(tree, tree->root);
    printf("\n");
}
