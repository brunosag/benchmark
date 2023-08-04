#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

// Utility function to get the height of a node
int height(struct AVLNode *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// Utility function to get the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to create a new AVL node
struct AVLNode *createAVLNode(int key)
{
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to create an empty AVL Tree
struct AVLTree *createAVLTree()
{
    struct AVLTree *tree = (struct AVLTree *)malloc(sizeof(struct AVLTree));
    tree->root = NULL;
    return tree;
}

// Function to free the memory occupied by the AVL nodes
void destroyAVLNodes(struct AVLNode *node)
{
    if (node != NULL)
    {
        destroyAVLNodes(node->left);
        destroyAVLNodes(node->right);
        free(node);
    }
}

// Function to destroy the AVL Tree
void destroyAVLTree(struct AVLTree *tree)
{
    destroyAVLNodes(tree->root);
    free(tree);
}

// Function to perform a right rotation
struct AVLNode *rightRotate(struct AVLNode *y)
{
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
struct AVLNode *leftRotate(struct AVLNode *x)
{
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Function to get the balance factor of a node
int getBalance(struct AVLNode *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a key into the AVL Tree
struct AVLNode *insertAVLNode(struct AVLNode *node, int key)
{
    if (node == NULL)
        return createAVLNode(key);

    if (key < node->key)
        node->left = insertAVLNode(node->left, key);
    else if (key > node->key)
        node->right = insertAVLNode(node->right, key);
    else // Duplicate keys are not allowed in AVL tree
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left-Left case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right-Right case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left-Right case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to insert a key into the AVL Tree (interface function)
void insertAVL(struct AVLTree *tree, int key)
{
    tree->root = insertAVLNode(tree->root, key);
}

// Function to print the AVL Tree in-order
void inOrderTraversal(struct AVLNode *node)
{
    if (node != NULL)
    {
        inOrderTraversal(node->left);
        printf("%d ", node->key);
        inOrderTraversal(node->right);
    }
}

// Function to print the AVL Tree (interface function)
void printAVL(struct AVLTree *tree)
{
    inOrderTraversal(tree->root);
    printf("\n");
}
