#include "avl.h"
#include "rb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DATA_SIZE 1000000

// Function to print the resulting array containing the X most repeated values
void printMostFrequent(KeyFrequency *result, int X)
{
    if (result == NULL)
    {
        printf("Invalid input or X is zero.\n");
        return;
    }

    printf("%d most frequent values in AVL tree: \n- ", X);
    for (int i = 0; (i < X && result[i].key != 0); i++)
    {
        printf("%d(%d) ", result[i].key, result[i].frequency);
    }
    printf("\n\n");
}

void insert_ordered_data_avl(AVLTree *avlTree, int size)
{
    // Insert ordered data (1, 2, 3, ..., size)
    for (int i = 1; i <= size; i++)
    {
        insertAVL(avlTree, i);
    }
}

void insert_ordered_data_rb(RBTree *rbTree, int size)
{
    // Insert ordered data (1, 2, 3, ..., size)
    for (int i = 1; i <= size; i++)
    {
        insertRB(rbTree, i);
    }
}

void insert_unordered_data_avl(AVLTree *avlTree, int size)
{
    // Insert unordered data (random values between 1 and size)
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        int value = rand() % size + 1;
        insertAVL(avlTree, value);
    }
}

void insert_unordered_data_rb(RBTree *rbTree, int size)
{
    // Insert unordered data (random values between 1 and size)
    for (int i = 0; i < size; i++)
    {
        int value = rand() % size + 1;
        insertRB(rbTree, value);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <ordered/unordered> <data_size>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    char *order_type = argv[1];
    int data_size = atoi(argv[2]);

    if (data_size <= 0 || data_size > MAX_DATA_SIZE)
    {
        printf("Invalid data size. Please provide a value between 1 and %d.\n", MAX_DATA_SIZE);
        return 1;
    }

    // Create the data structures
    AVLTree *avlTree = createAVLTree();
    RBTree *rbTree = createRBTree();

    // Measure time for AVL Tree insertion
    clock_t avlStart = clock();
    if (strcmp(order_type, "ordered") == 0)
    {
        insert_ordered_data_avl(avlTree, data_size);
    }
    else if (strcmp(order_type, "unordered") == 0)
    {
        insert_unordered_data_avl(avlTree, data_size);
    }
    else
    {
        printf("Invalid order type. Please choose 'ordered' or 'unordered'.\n");
        destroyAVLTree(avlTree);
        destroyRBTree(rbTree);
        return 1;
    }
    clock_t avlEnd = clock();
    double avlTimeInsertion = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;

    // Measure time for Red-Black Tree insertion
    clock_t rbStart = clock();
    if (strcmp(order_type, "ordered") == 0)
    {
        insert_ordered_data_rb(rbTree, data_size);
    }
    else if (strcmp(order_type, "unordered") == 0)
    {
        insert_unordered_data_rb(rbTree, data_size);
    }
    else
    {
        printf("Invalid order type. Please choose 'ordered' or 'unordered'.\n");
        destroyAVLTree(avlTree);
        destroyRBTree(rbTree);
        return 1;
    }
    clock_t rbEnd = clock();
    double rbTimeInsertion = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;

    // Measure time for AVL Tree minimum search
    avlStart = clock();
    int avlMin = findMinAVL(avlTree);
    avlEnd = clock();
    double avlTimeMin = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;

    // Measure time for Red-Black Tree minimum search
    rbStart = clock();
    int rbMin = findMinRB(rbTree);
    rbEnd = clock();
    double rbTimeMin = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;

    // Measure time for AVL Tree maximum search
    avlStart = clock();
    int avlMax = findMaxAVL(avlTree);
    avlEnd = clock();
    double avlTimeMax = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;

    // Measure time for Red-Black Tree maximum search
    rbStart = clock();
    int rbMax = findMaxRB(rbTree);
    rbEnd = clock();
    double rbTimeMax = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;

    // Measure time for AVL Tree average calculation
    avlStart = clock();
    double avlAverage = findAverageAVL(avlTree);
    avlEnd = clock();
    double avlTimeAverage = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;

    // Measure time for Red-Black Tree average calculation
    rbStart = clock();
    double rbAverage = findAverageRB(rbTree);
    rbEnd = clock();
    double rbTimeAverage = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;

    // Measure time for finding the 10 most frequent values in AVL Tree
    clock_t avlStart10 = clock();
    KeyFrequency *avlMostFrequent10 = findXMostFrequentAVL(avlTree, 10, data_size);
    clock_t avlEnd10 = clock();
    double avlTimeFrequent10 = ((double)(avlEnd10 - avlStart10)) / CLOCKS_PER_SEC;

    // Measure time for finding the 50 most frequent values in AVL Tree
    clock_t avlStart50 = clock();
    KeyFrequency *avlMostFrequent50 = findXMostFrequentAVL(avlTree, 50, data_size);
    clock_t avlEnd50 = clock();
    double avlTimeFrequent50 = ((double)(avlEnd50 - avlStart50)) / CLOCKS_PER_SEC;

    // // Measure time for finding the 10 most frequent values in Red-Black Tree
    // clock_t rbStart10 = clock();
    // findXMostFrequentRB(rbTree, 10);
    // clock_t rbEnd10 = clock();
    // double rbTimeFrequent10 = ((double)(rbEnd10 - rbStart10)) / CLOCKS_PER_SEC;

    // // Measure time for finding the 50 most frequent values in Red-Black Tree
    // clock_t rbStart50 = clock();
    // findXMostFrequentRB(rbTree, 50);
    // clock_t rbEnd50 = clock();
    // double rbTimeFrequent50 = ((double)(rbEnd50 - rbStart50)) / CLOCKS_PER_SEC;

    // Display the most frequent values
    printMostFrequent(avlMostFrequent10, 10);
    printMostFrequent(avlMostFrequent50, 50);

    // Display the results in table format
    printf("%-20s | %-20s | %-20s | %-20s\n", "Operation", "AVL Tree (s)", "Red-Black Tree (s)", "AVL/RB Ratio");
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-20s | %-20.6f | %-20.6f | %-20.2f\n", "Insert data", avlTimeInsertion, rbTimeInsertion,
           avlTimeInsertion / rbTimeInsertion);
    printf("%-20s | %-20.6f | %-20.6f | %-20.2f\n", "Find min", avlTimeMin, rbTimeMin, avlTimeMin / rbTimeMin);
    printf("%-20s | %-20.6f | %-20.6f | %-20.2f\n", "Find max", avlTimeMax, rbTimeMax, avlTimeMax / rbTimeMax);
    printf("%-20s | %-20.6f | %-20.6f | %-20.2f\n", "Calculate average", avlTimeAverage, rbTimeAverage,
           avlTimeAverage / rbTimeAverage);
    // printf("%-20s | %-20.6f | %-20.6f | %-20.2f\n", "Find 10 most frequent", avlTimeFrequent10, rbTimeFrequent10,
    //        avlTimeFrequent10 / rbTimeFrequent10);
    // printf("%-20s | %-20.6f | %-20.6f | %-20.2f\n", "Find 50 most frequent", avlTimeFrequent50, rbTimeFrequent50,
    //        avlTimeFrequent50 / rbTimeFrequent50);

    // Destroy the trees to free memory
    destroyAVLTree(avlTree);
    destroyRBTree(rbTree);

    return 0;
}
