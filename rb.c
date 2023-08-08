#include "rb.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Function to find the minimum value in a Red-Black Tree
int findMinRB(RBTree *tree)
{
    RBNode *node = tree->root;

    if (node == tree->nil)
        return -1;

    while (node->left != tree->nil)
        node = node->left;

    return node->key;
}

// Function to find the maximum value in the RB Tree
int findMaxRB(RBTree *tree)
{
    RBNode *node = tree->root;

    if (node == tree->nil)
        return 0;

    while (node->right != tree->nil)
        node = node->right;

    return node->key;
}

// Helper function to calculate the sum of all nodes in a Red-Black Tree
static int sumRBNodes(RBNode *node, RBTree *tree)
{
    if (node == tree->nil)
        return 0;

    return node->key + sumRBNodes(node->left, tree) + sumRBNodes(node->right, tree);
}

// Helper function to count the number of nodes in a Red-Black Tree
static int countRBNodes(RBNode *node, RBTree *tree)
{
    if (node == tree->nil)
        return 0;

    return 1 + countRBNodes(node->left, tree) + countRBNodes(node->right, tree);
}

double findAverageRB(RBTree *tree)
{
    long long int sum = 0;
    int numNodes = countRBNodes(tree->root, tree);

    if (numNodes == 0)
        return 0.0;

    RBNode *current = tree->root;
    RBNode *pre;

    while (current != tree->nil)
    {
        if (current->left == tree->nil)
        {
            sum += current->key;
            current = current->right;
        }
        else
        {
            pre = current->left;

            while (pre->right != tree->nil && pre->right != current)
                pre = pre->right;

            if (pre->right == tree->nil)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = tree->nil;
                sum += current->key;
                current = current->right;
            }
        }
    }

    return (double)sum / numNodes;
}

// Function to create a new Red-Black node
RBNode *createRBNode(int key, enum Color color)
{
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->key = key;
    node->color = color;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create an empty Red-Black Tree
RBTree *createRBTree()
{
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
    tree->nil = createRBNode(0, BLACK);
    tree->root = tree->nil;
    return tree;
}

// Function to free the memory occupied by the Red-Black nodes
void destroyRBNodes(RBTree *tree, RBNode *node)
{
    if (node != tree->nil)
    {
        destroyRBNodes(tree, node->left);
        destroyRBNodes(tree, node->right);
        free(node);
    }
}

// Function to destroy the Red-Black Tree
void destroyRBTree(RBTree *tree)
{
    destroyRBNodes(tree, tree->root);
    free(tree->nil);
    free(tree);
}

// Function to perform a left rotation in the Red-Black Tree
void leftRotateRB(RBTree *tree, RBNode *x)
{
    RBNode *y = x->right;
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
void rightRotateRB(RBTree *tree, RBNode *y)
{
    RBNode *x = y->left;
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
void fixInsertRB(RBTree *tree, RBNode *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode *y = z->parent->parent->right;
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
            RBNode *y = z->parent->parent->left;
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
void insertRB(RBTree *tree, int key)
{
    RBNode *z = createRBNode(key, RED);
    RBNode *y = tree->nil;
    RBNode *x = tree->root;

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
void inOrderTraversalRB(RBTree *tree, RBNode *node)
{
    if (node != tree->nil)
    {
        inOrderTraversalRB(tree, node->left);
        printf("%d ", node->key);
        inOrderTraversalRB(tree, node->right);
    }
}

// Function to print the Red-Black Tree
void printRB(RBTree *tree)
{
    inOrderTraversalRB(tree, tree->root);
    printf("\n");
}
