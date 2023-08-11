#include "avl.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DATA_SIZE 1000000

// Helper function to find the frequency of each key in the AVL Tree
static void findKeyFrequenciesAVL(AVLNode *node, int data_size, KeyFrequency *frequencies, int *arr_size)
{
    compare();
    if (node != NULL)
    {
        findKeyFrequenciesAVL(node->left, data_size, frequencies, arr_size);

        bool key_found = false;
        compare();
        for (int i = 0; (i < *arr_size) && (!key_found); i++)
        {
            compare();
            if (frequencies[i].key == node->key)
            {
                frequencies[i].frequency++;
                key_found = true;
            }
            compare();
        }
        compare();
        if (!key_found)
        {
            KeyFrequency newKey;
            newKey.frequency = 1;
            newKey.key = node->key;
            frequencies[*arr_size] = newKey;
            (*arr_size)++;
        }

        findKeyFrequenciesAVL(node->right, data_size, frequencies, arr_size);
    }
}

// Function to find the X most frequent values in the AVL Tree
KeyFrequency *findXMostFrequentAVL(AVLTree *tree, int X, int data_size)
{
    compare();
    if (tree == NULL || X <= 0)
    {
        return NULL;
    }

    KeyFrequency *frequencies = calloc(data_size, sizeof(KeyFrequency));
    KeyFrequency *result = calloc(X, sizeof(KeyFrequency));
    int arr_size = 0;

    // Find the frequency of each key in the AVL Tree
    findKeyFrequenciesAVL(tree->root, data_size, frequencies, &arr_size);

    // Find X most frequent in the frequencies array
    compare();
    for (int i = 0; i < X; i++)
    {
        int max_freq = 0;
        int max_freq_index = -1;

        compare();
        for (int j = 0; j < arr_size; j++)
        {
            compare();
            if (frequencies[j].frequency > max_freq)
            {
                max_freq = frequencies[j].frequency;
                max_freq_index = j;
            }
            compare();
        }

        compare();
        if (max_freq_index != -1)
        {
            result[i] = frequencies[max_freq_index];
            frequencies[max_freq_index].frequency = 0;
        }

        compare();
    }

    return result;
}

// Helper function to create a new AVL node
static AVLNode *createAVLNode(int key)
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
static void updateNode(AVLNode *node)
{
    compare();
    int left_height = node->left ? node->left->height : 0;
    compare();
    int right_height = node->right ? node->right->height : 0;

    compare();
    node->height = 1 + (left_height > right_height ? left_height : right_height);
    compare();
    compare();
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);
}

// Helper function to perform a right rotation
static AVLNode *rightRotateAVL(AVLNode *y)
{
    compare();
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
static AVLNode *leftRotateAVL(AVLNode *x)
{
    compare();
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
static AVLNode *insertAVLNode(AVLNode *node, int key)
{
    compare();
    if (node == NULL)
        return createAVLNode(key);

    compare();
    if (key < node->key)
        node->left = insertAVLNode(node->left, key);
    else if (key > node->key)
        node->right = insertAVLNode(node->right, key);
    else
        node->right = insertAVLNode(node->right, key);

    // Update height and size
    updateNode(node);

    // Calculate balance factor
    compare();
    compare();
    int balance = (node->left ? node->left->height : 0) - (node->right ? node->right->height : 0);

    // Left-Left case
    compare();
    compare();
    if (balance > 1 && key < node->left->key)
        return rightRotateAVL(node);

    // Right-Right case
    compare();
    compare();
    if (balance < -1 && key > node->right->key)
        return leftRotateAVL(node);

    // Left-Right case
    compare();
    compare();
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotateAVL(node->left);
        return rightRotateAVL(node);
    }

    // Right-Left case
    compare();
    compare();
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotateAVL(node->right);
        return leftRotateAVL(node);
    }

    return node;
}

// Function to free the memory occupied by the AVL nodes
static void destroyAVLNodes(AVLNode *node)
{
    compare();
    if (node != NULL)
    {
        destroyAVLNodes(node->left);
        destroyAVLNodes(node->right);
        free(node);
    }
}

// Helper function to find the minimum value in an AVL Tree
static AVLNode *findMinAVLNode(AVLNode *node)
{
    compare();
    if (node == NULL)
        return NULL;

    compare();
    while (node->left != NULL)
    {
        node = node->left;
        compare();
    }

    return node;
}

// Helper function to find the maximum value in an AVL Tree
static AVLNode *findMaxAVLNode(AVLNode *node)
{
    compare();
    if (node == NULL)
        return NULL;

    compare();
    while (node->right != NULL)
    {
        node = node->right;
        compare();
    }

    return node;
}

// Helper function to calculate the sum of all nodes in an AVL Tree
static int sumAVLNodes(AVLNode *node)
{
    if (node == NULL)
        return 0;

    return node->key + sumAVLNodes(node->left) + sumAVLNodes(node->right);
}

// Helper function to count the number of nodes in an AVL Tree
static int countAVLNodes(AVLNode *node)
{
    compare();
    if (node == NULL)
        return 0;

    return 1 + countAVLNodes(node->left) + countAVLNodes(node->right);
}

// Function to create an empty AVL Tree
AVLTree *createAVLTree()
{
    AVLTree *tree = (AVLTree *)malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
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

// Function to insert ordered data in the AVL tree (1, 2, 3, ..., size)
void insertOrderedDataAVL(AVLTree *avlTree, int size)
{
    compare();
    for (int i = 1; i <= size; i++)
    {
        insertAVL(avlTree, i);
        compare();
    }
}

// Function to insert unordered data in the AVL Tree (random values between 1 and size)
void insertUnorderedDataAVL(AVLTree *avlTree, int size)
{
    srand(time(NULL));
    compare();
    for (int i = 0; i < size; i++)
    {
        int value = rand() % size + 1;
        insertAVL(avlTree, value);
        compare();
    }
}

// Function to find the minimum value in the AVL Tree
int findMinAVL(AVLTree *tree)
{
    AVLNode *minNode = findMinAVLNode(tree->root);
    compare();
    return minNode ? minNode->key : INT_MIN;
}

// Function to find the maximum value in the AVL Tree
int findMaxAVL(AVLTree *tree)
{
    AVLNode *maxNode = findMaxAVLNode(tree->root);
    compare();
    return maxNode ? maxNode->key : INT_MAX;
}

// Function to calculate the average value in an AVL Tree
double findAverageAVL(AVLTree *tree)
{
    long long int sum = 0;
    int numNodes = countAVLNodes(tree->root);

    compare();
    if (numNodes == 0)
        return 0.0;

    AVLNode *current = tree->root;
    AVLNode *pre;

    compare();
    while (current != NULL)
    {
        compare();
        if (current->left == NULL)
        {
            sum += current->key;
            current = current->right;
        }
        else
        {
            pre = current->left;

            compare();
            while (pre->right != NULL && pre->right != current)
            {
                pre = pre->right;
                compare();
            }
            compare();
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
        compare();
    }

    return (double)sum / numNodes;
}

// Function to print the AVL Tree in-order
static void inOrderTraversalAVL(AVLNode *node)
{
    if (node != NULL)
    {
        inOrderTraversalAVL(node->left);
        printf("%d ", node->key);
        inOrderTraversalAVL(node->right);
    }
}

// Function to print the AVL Tree
void printAVL(AVLTree *tree)
{
    inOrderTraversalAVL(tree->root);
    printf("\n");
}
