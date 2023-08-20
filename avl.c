#include "avl.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DATASIZE 1000000

// Function to create an empty AVL Tree
AVLTree *createAVLTree()
{
    AVLTree *tree = malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

// Helper function to find the frequency of each key in the AVL Tree
void findKeyFrequenciesAVL(AVLNode *node, int dataSize, KeyFrequency *frequencies, int *arrSize)
{
    if (node != NULL)
    {
        findKeyFrequenciesAVL(node->left, dataSize, frequencies, arrSize);

        bool keyFound = false;
        for (int i = 0; (i < *arrSize) && (!keyFound); i++)
        {
            if (frequencies[i].key == node->key)
            {
                frequencies[i].frequency++;
                keyFound = true;
            }
        }
        if (!keyFound)
        {
            KeyFrequency newKey = {node->key, 1};
            frequencies[*arrSize] = newKey;
            (*arrSize)++;
        }

        findKeyFrequenciesAVL(node->right, dataSize, frequencies, arrSize);
    }
}

// Function to find the X most frequent values in the AVL Tree
KeyFrequency *findXMostFrequentAVL(AVLTree *tree, int X, int dataSize)
{
    if (tree == NULL || X <= 0)
    {
        return NULL;
    }

    KeyFrequency *frequencies = calloc(dataSize, sizeof(KeyFrequency));
    KeyFrequency *result = calloc(X, sizeof(KeyFrequency));
    int arr_size = 0;

    // Find the frequency of each key in the AVL Tree
    findKeyFrequenciesAVL(tree->root, dataSize, frequencies, &arr_size);

    // Find X most frequent in the frequencies array
    for (int i = 0; i < X; i++)
    {
        int max_freq = 0;
        int max_freq_index = -1;

        for (int j = 0; j < arr_size; j++)
        {
            if (frequencies[j].frequency > max_freq)
            {
                max_freq = frequencies[j].frequency;
                max_freq_index = j;
            }
        }

        if (max_freq_index != -1)
        {
            result[i] = frequencies[max_freq_index];
            frequencies[max_freq_index].frequency = 0;
        }
    }

    return result;
}

// Helper function to create a new AVL node
AVLNode *createAVLNode(int key)
{
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->size = 1;
    return node;
}

// Helper function to update the height and size of a node
void updateNode(AVLNode *node)
{
    int left_height = node->left ? node->left->height : 0;
    int right_height = node->right ? node->right->height : 0;

    node->height = 1 + (left_height > right_height ? left_height : right_height);
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

// Helper function to perform a right rotation
AVLNode *rightRotateAVL(AVLNode *y)
{
    if (y == NULL || y->left == NULL)
        return y;

    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform the rotation
    x->right = y;
    y->left = T2;

    // Update heights and sizes
    updateNode(y);
    updateNode(x);

    return x;
}

// Helper function to perform a left rotation
AVLNode *leftRotateAVL(AVLNode *x)
{
    if (x == NULL || x->right == NULL)
        return x;

    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform the rotation
    y->left = x;
    x->right = T2;

    // Update heights and sizes
    updateNode(x);
    updateNode(y);

    return y;
}

// Helper function to insert a key into the AVL Tree
AVLNode *insertAVLNode(AVLNode *node, int key)
{
    if (node == NULL)
        return createAVLNode(key);

    if (key < node->key)
        node->left = insertAVLNode(node->left, key);
    else if (key > node->key)
        node->right = insertAVLNode(node->right, key);
    else
        node->right = insertAVLNode(node->right, key);

    // Update height and size
    updateNode(node);

    // Calculate balance factor
    int balance = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

    // Left-Left case
    if (balance > 1 && key < node->left->key)
    {
        return rightRotateAVL(node);
    }

    // Right-Right case
    if (balance < -1 && key > node->right->key)
    {
        return leftRotateAVL(node);
    }

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

// Function to free the memory occupied by the AVL nodes
void destroyAVLNodes(AVLNode *node)
{
    if (node != NULL)
    {
        destroyAVLNodes(node->left);
        destroyAVLNodes(node->right);
        free(node);
    }
}

// Function to insert a key into the AVL Tree
void insertAVL(AVLTree *tree, int key)
{
    tree->root = insertAVLNode(tree->root, key);
}

// Function to destroy the AVL Tree
void destroyAVLTree(AVLTree *tree)
{
    destroyAVLNodes(tree->root);
    free(tree);
}

// Function to insert data from the dataset into the AVL Tree
void insertDataAVL(AVLTree *tree, int *dataset, int dataSize)
{
    for (int i = 0; i < dataSize; i++)
    {
        insertAVL(tree, dataset[i]);
    }
}

// Function to find the minimum value in the AVL Tree
int findMinAVL(AVLTree *tree)
{
    AVLNode *current = tree->root;

    if (current == NULL)
    {
        printf("Tree is empty.\n");
        return -1;
    }

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current->key;
}

// Function to find the maximum value in the AVL Tree
int findMaxAVL(AVLTree *tree)
{
    AVLNode *current = tree->root;

    if (current == NULL)
    {
        printf("Tree is empty.\n");
        return -1;
    }

    while (current->right != NULL)
    {
        current = current->right;
    }

    return current->key;
}

double calculateAverageAVLNode(AVLNode *node, long long int *sum, int *numNodes)
{
    if (node == NULL)
        return 0.0;

    calculateAverageAVLNode(node->left, sum, numNodes);
    *sum += node->key;
    (*numNodes)++;
    calculateAverageAVLNode(node->right, sum, numNodes);

    return (double)(*sum) / (*numNodes);
}

double calculateAverageAVL(AVLTree *tree)
{
    long long int sum = 0;
    int numNodes = 0;

    return calculateAverageAVLNode(tree->root, &sum, &numNodes);
}

void printAVLNode(AVLNode *node)
{
    if (node != NULL)
    {
        printAVLNode(node->left);
        printf("%d ", node->key);
        printAVLNode(node->right);
    }
}

// Function to print the AVL Tree
void printAVL(AVLTree *tree)
{
    printAVLNode(tree->root);
    printf("\n");
}
