#include "avl.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Helper function to create a new AVL node
static struct AVLNode *createAVLNode(int key)
{
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->size = 1;
    return node;
}

// Helper function to update the height and size of a node
static void updateNode(struct AVLNode *node)
{
    int left_height = node->left ? node->left->height : 0;
    int right_height = node->right ? node->right->height : 0;

    node->height = 1 + (left_height > right_height ? left_height : right_height);
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

// Helper function to perform a right rotation
static struct AVLNode *rightRotateAVL(struct AVLNode *y)
{
    if (y == NULL || y->left == NULL)
        return y;

    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    // Perform the rotation
    x->right = y;
    y->left = T2;

    // Update heights and sizes
    updateNode(y);
    updateNode(x);

    return x;
}

// Helper function to perform a left rotation
static struct AVLNode *leftRotateAVL(struct AVLNode *x)
{
    if (x == NULL || x->right == NULL)
        return x;

    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Perform the rotation
    y->left = x;
    x->right = T2;

    // Update heights and sizes
    updateNode(x);
    updateNode(y);

    return y;
}

// Function to create an empty AVL Tree
struct AVLTree *createAVLTree()
{
    struct AVLTree *tree = (struct AVLTree *)malloc(sizeof(struct AVLTree));
    tree->root = NULL;
    return tree;
}

// Helper function to insert a key into the AVL Tree
static struct AVLNode *insertAVLNode(struct AVLNode *node, int key)
{
    if (node == NULL)
        return createAVLNode(key);

    if (key < node->key)
        node->left = insertAVLNode(node->left, key);
    else if (key > node->key)
        node->right = insertAVLNode(node->right, key);
    else // Duplicate keys are allowed in AVL tree, insert in the right subtree
        node->right = insertAVLNode(node->right, key);

    // Update height and size
    updateNode(node);

    // Calculate balance factor
    int balance = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

    // Left-Left case
    if (balance > 1 && key < node->left->key)
        return rightRotateAVL(node);

    // Right-Right case
    if (balance < -1 && key > node->right->key)
        return leftRotateAVL(node);

    // Left-Right case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotateAVL(node->left);
        return rightRotateAVL(node);
    }

    // Right-Left case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotateAVL(node->right);
        return leftRotateAVL(node);
    }

    return node;
}

// Function to insert a key into the AVL Tree (interface function)
void insertAVL(struct AVLTree *tree, int key)
{
    tree->root = insertAVLNode(tree->root, key);
}

// Function to free the memory occupied by the AVL nodes
static void destroyAVLNodes(struct AVLNode *node)
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

// Helper function to find the minimum value in an AVL Tree
static struct AVLNode *findMinAVLNode(struct AVLNode *node)
{
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
        node = node->left;

    return node;
}

// Function to find the minimum value in the AVL Tree (interface function)
int findMinAVL(struct AVLTree *tree)
{
    struct AVLNode *minNode = findMinAVLNode(tree->root);
    return minNode ? minNode->key : INT_MIN;
}

// Helper function to find the maximum value in an AVL Tree
static struct AVLNode *findMaxAVLNode(struct AVLNode *node)
{
    if (node == NULL)
        return NULL;

    while (node->right != NULL)
        node = node->right;

    return node;
}

// Function to find the maximum value in the AVL Tree (interface function)
int findMaxAVL(struct AVLTree *tree)
{
    struct AVLNode *maxNode = findMaxAVLNode(tree->root);
    return maxNode ? maxNode->key : INT_MAX;
}

// Helper function to calculate the sum of all nodes in an AVL Tree
static int sumAVLNodes(struct AVLNode *node)
{
    if (node == NULL)
        return 0;

    return node->key + sumAVLNodes(node->left) + sumAVLNodes(node->right);
}

// Helper function to count the number of nodes in an AVL Tree
static int countAVLNodes(struct AVLNode *node)
{
    if (node == NULL)
        return 0;

    return 1 + countAVLNodes(node->left) + countAVLNodes(node->right);
}

// Function to calculate the average value in an AVL Tree
double findAverageAVL(struct AVLTree *tree)
{
    long long int sum = 0;
    int numNodes = countAVLNodes(tree->root);

    if (numNodes == 0)
        return 0.0;

    struct AVLNode *current = tree->root;
    struct AVLNode *pre;

    while (current != NULL)
    {
        if (current->left == NULL)
        {
            sum += current->key;
            current = current->right;
        }
        else
        {
            pre = current->left;

            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = NULL;
                sum += current->key;
                current = current->right;
            }
        }
    }

    return (double)sum / numNodes;
}

// Function to print the AVL Tree in-order
static void inOrderTraversalAVL(struct AVLNode *node)
{
    if (node != NULL)
    {
        inOrderTraversalAVL(node->left);
        printf("%d ", node->key);
        inOrderTraversalAVL(node->right);
    }
}

// Function to print the AVL Tree (interface function)
void printAVL(struct AVLTree *tree)
{
    inOrderTraversalAVL(tree->root);
    printf("\n");
}
