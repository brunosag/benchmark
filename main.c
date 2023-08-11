#include "avl.h"
#include "rb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DATA_SIZE 1000000

// Global variable to count comparisons
unsigned long long comparisonCount = 0;

// Function that increments comparisonCount (insert just before comparison)
void compare()
{
    comparisonCount++;
}

// Helper function to print the X most repeated values in the tree
void printMostFrequent(KeyFrequency *result, int X)
{
    if (result == NULL)
    {
        printf("Invalid input or X is zero.\n");
        return;
    }

    for (int i = 0; (i < X && result[i].key != 0); i++)
    {
        if ((i != 0) && (i % 10 == 0))
        {
            printf("\n%-25s", "");
        }
        printf("%d(%d) ", result[i].key, result[i].frequency);
    }
}

// Function to insert ordered data in the Red-Black tree (1, 2, 3, ..., size)
void insertOrderedDataRB(RBTree *rbTree, int size)
{
    for (int i = 1; i <= size; i++)
    {
        insertRB(rbTree, i);
    }
}

// Function to insert unordered data in the RB Tree (random values between 1 and size)
void insertUnorderedDataRB(RBTree *rbTree, int size)
{
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

    // Measure time and comparison count for AVL Tree insertion
    clock_t avlStart = clock();
    compare();
    if (strcmp(order_type, "ordered") == 0)
    {
        insertOrderedDataAVL(avlTree, data_size);
    }
    else if (strcmp(order_type, "unordered") == 0)
    {
        insertUnorderedDataAVL(avlTree, data_size);
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
    int avlCompInsertion = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Red-Black Tree insertion
    clock_t rbStart = clock();
    if (strcmp(order_type, "ordered") == 0)
    {
        insertOrderedDataRB(rbTree, data_size);
    }
    else if (strcmp(order_type, "unordered") == 0)
    {
        insertUnorderedDataRB(rbTree, data_size);
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
    int rbCompInsertion = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for AVL Tree minimum search
    avlStart = clock();
    int avlMin = findMinAVL(avlTree);
    avlEnd = clock();
    double avlTimeMin = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    int avlCompMin = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Red-Black Tree minimum search
    rbStart = clock();
    int rbMin = findMinRB(rbTree);
    rbEnd = clock();
    double rbTimeMin = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;
    int rbCompMin = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for AVL Tree maximum search
    avlStart = clock();
    int avlMax = findMaxAVL(avlTree);
    avlEnd = clock();
    double avlTimeMax = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    int avlCompMax = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Red-Black Tree maximum search
    rbStart = clock();
    int rbMax = findMaxRB(rbTree);
    rbEnd = clock();
    double rbTimeMax = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;
    int rbCompMax = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for AVL Tree average calculation
    avlStart = clock();
    double avlAverage = findAverageAVL(avlTree);
    avlEnd = clock();
    double avlTimeAverage = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    int avlCompAverage = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Red-Black Tree average calculation
    rbStart = clock();
    double rbAverage = findAverageRB(rbTree);
    rbEnd = clock();
    double rbTimeAverage = ((double)(rbEnd - rbStart)) / CLOCKS_PER_SEC;
    int rbCompAverage = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 10 most frequent values in AVL Tree
    clock_t avlStart10 = clock();
    KeyFrequency *avlMostFrequent10 = findXMostFrequentAVL(avlTree, 10, data_size);
    clock_t avlEnd10 = clock();
    double avlTimeFrequent10 = ((double)(avlEnd10 - avlStart10)) / CLOCKS_PER_SEC;
    int avlCompFrequent10 = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 50 most frequent values in AVL Tree
    clock_t avlStart50 = clock();
    KeyFrequency *avlMostFrequent50 = findXMostFrequentAVL(avlTree, 50, data_size);
    clock_t avlEnd50 = clock();
    double avlTimeFrequent50 = ((double)(avlEnd50 - avlStart50)) / CLOCKS_PER_SEC;
    int avlCompFrequent50 = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 10 most frequent values in Red-Black Tree
    clock_t rbStart10 = clock();
    KeyFrequency *rbMostFrequent10 = findXMostFrequentRB(rbTree, 10, data_size);
    clock_t rbEnd10 = clock();
    double rbTimeFrequent10 = ((double)(rbEnd10 - rbStart10)) / CLOCKS_PER_SEC;
    int rbCompFrequent10 = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 50 most frequent values in Red-Black Tree
    clock_t rbStart50 = clock();
    KeyFrequency *rbMostFrequent50 = findXMostFrequentRB(rbTree, 50, data_size);
    clock_t rbEnd50 = clock();
    double rbTimeFrequent50 = ((double)(rbEnd50 - rbStart50)) / CLOCKS_PER_SEC;
    int rbCompFrequent50 = comparisonCount;
    comparisonCount = 0;

    // Print header
    printf("\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("| %-93s |\n", "");
    printf("| %-21sPerformance Comparison: AVL Tree vs. Red-Black Tree%-21s |\n", "", "");
    printf("| %-93s |\n", "");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("\nData set: %d %s elements\n\n", data_size, order_type);

    // Ṕrint result values from the AVL Tree
    printf("AVL Tree:\n");
    printf("%-25s%d\n", "  - Minimum:", avlMin);
    printf("%-25s%d\n", "  - Maximum:", avlMax);
    printf("%-25s%.1f\n", "  - Average:", avlAverage);
    printf("%-25s", "  - 10 most frequent:");
    printMostFrequent(avlMostFrequent10, 10);
    printf("\n%-25s", "  - 50 most frequent:");
    printMostFrequent(avlMostFrequent50, 50);
    printf("\n\n");

    // Print result values from the Red-Black Tree
    printf("Red-Black Tree:\n");
    printf("%-25s%d\n", "  - Minimum:", rbMin);
    printf("%-25s%d\n", "  - Maximum:", rbMax);
    printf("%-25s%.1f\n", "  - Average:", rbAverage);
    printf("%-25s", "  - 10 most frequent:");
    printMostFrequent(rbMostFrequent10, 10);
    printf("\n%-25s", "  - 50 most frequent:");
    printMostFrequent(rbMostFrequent50, 50);
    printf("\n\n");

    // Print time benchmarks in table format
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("| %-37sExecution Time (s)%-38s |\n", "", "");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("| %-24s | %-20s | %-20s | %-20s |\n", "Operation", "AVL Tree", "Red-Black Tree", "AVL/RB Ratio");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Insert data", avlTimeInsertion, rbTimeInsertion,
           avlTimeInsertion / rbTimeInsertion);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find min", avlTimeMin, rbTimeMin, avlTimeMin / rbTimeMin);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find max", avlTimeMax, rbTimeMax, avlTimeMax / rbTimeMax);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Calculate average", avlTimeAverage, rbTimeAverage,
           avlTimeAverage / rbTimeAverage);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find 10 most frequent", avlTimeFrequent10, rbTimeFrequent10,
           avlTimeFrequent10 / rbTimeFrequent10);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find 50 most frequent", avlTimeFrequent50, rbTimeFrequent50,
           avlTimeFrequent50 / rbTimeFrequent50);
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("\n");

    // Print comparison benchmarks in table format
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("| %-36sNumber of Comparisons%-36s |\n", "", "");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("| %-24s | %-20s | %-20s | %-20s |\n", "Operation", "AVL Tree", "Red-Black Tree", "AVL/RB Ratio");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("| %-24s | %-20i | %-20i | %-20i |\n", "Insert data", avlCompInsertion, 0, 0);
    printf("| %-24s | %-20i | %-20i | %-20i |\n", "Find min", avlCompMin, 0, 0);
    printf("| %-24s | %-20i | %-20i | %-20i |\n", "Find max", avlCompMax, 0, 0);
    printf("| %-24s | %-20i | %-20i | %-20i |\n", "Calculate average", avlCompAverage, 0, 0);
    printf("| %-24s | %-20i | %-20i | %-20i |\n", "Find 10 most frequent", avlCompFrequent10, 0, 0);
    printf("| %-24s | %-20i | %-20i | %-20i |\n", "Find 50 most frequent", avlCompFrequent50, 0, 0);
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("\n");

    // Destroy the trees to free memory
    destroyAVLTree(avlTree);
    destroyRBTree(rbTree);

    return 0;
}
