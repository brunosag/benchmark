#include "avl.h"
#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DATASIZE 1000000

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

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <ordered/unordered> <dataSize>\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    char *orderType = argv[1];
    int dataSize = atoi(argv[2]);

    if (dataSize <= 0 || dataSize > MAX_DATASIZE)
    {
        printf("Invalid data size. Please provide a value between 1 and %d.\n", MAX_DATASIZE);
        return 1;
    }

    // Create the data structures
    AVLTree *avlTree = createAVLTree();
    DoublyLinkedList *doublyLinkedList = createDoublyLinkedList();

    // Measure time and comparison count for AVL Tree insertion
    clock_t avlStart = clock();
    compare();
    if (strcmp(orderType, "ordered") == 0)
    {
        insertOrderedDataAVL(avlTree, dataSize);
    }
    else if (strcmp(orderType, "unordered") == 0)
    {
        insertUnorderedDataAVL(avlTree, dataSize);
    }
    else
    {
        printf("Invalid order type. Please choose 'ordered' or 'unordered'.\n");
        destroyAVLTree(avlTree);
        destroyDoublyLinkedList(doublyLinkedList);
        return 1;
    }
    clock_t avlEnd = clock();
    double avlTimeInsertion = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    unsigned long long avlCompInsertion = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Doubly-Linked List insertion
    clock_t dllStart = clock();
    compare();
    if (strcmp(orderType, "ordered") == 0)
    {
        insertOrderedDataDLL(doublyLinkedList, dataSize);
    }
    else if (strcmp(orderType, "unordered") == 0)
    {
        insertUnorderedDataDLL(doublyLinkedList, dataSize);
    }
    else
    {
        printf("Invalid order type. Please choose 'ordered' or 'unordered'.\n");
        destroyAVLTree(avlTree);
        destroyDoublyLinkedList(doublyLinkedList);
        return 1;
    }
    clock_t dllEnd = clock();
    double dllTimeInsertion = ((double)(dllEnd - dllStart)) / CLOCKS_PER_SEC;
    unsigned long long dllCompInsertion = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for AVL Tree minimum search
    avlStart = clock();
    int avlMin = findMinAVL(avlTree);
    avlEnd = clock();
    double avlTimeMin = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    unsigned long long avlCompMin = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Doubly-Linked List minimum search
    dllStart = clock();
    int dllMin = findMinDLL(doublyLinkedList);
    dllEnd = clock();
    double dllTimeMin = ((double)(dllEnd - dllStart)) / CLOCKS_PER_SEC;
    unsigned long long dllCompMin = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for AVL Tree maximum search
    avlStart = clock();
    int avlMax = findMaxAVL(avlTree);
    avlEnd = clock();
    double avlTimeMax = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    unsigned long long avlCompMax = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Doubly-Linked List maximum search
    dllStart = clock();
    int dllMax = findMaxDLL(doublyLinkedList);
    dllEnd = clock();
    double dllTimeMax = ((double)(dllEnd - dllStart)) / CLOCKS_PER_SEC;
    unsigned long long dllCompMax = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for AVL Tree average calculation
    avlStart = clock();
    double avlAverage = calculateAverageAVL(avlTree);
    avlEnd = clock();
    double avlTimeAverage = ((double)(avlEnd - avlStart)) / CLOCKS_PER_SEC;
    unsigned long long avlCompAverage = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for Doubly-Linked List average calculation
    dllStart = clock();
    double dllAverage = calculateAverageDLL(doublyLinkedList);
    dllEnd = clock();
    double dllTimeAverage = ((double)(dllEnd - dllStart)) / CLOCKS_PER_SEC;
    unsigned long long dllCompAverage = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 10 most frequent values in AVL Tree
    clock_t avlStart10 = clock();
    KeyFrequency *avlMostFrequent10 = findXMostFrequentAVL(avlTree, 10, dataSize);
    clock_t avlEnd10 = clock();
    double avlTimeFrequent10 = ((double)(avlEnd10 - avlStart10)) / CLOCKS_PER_SEC;
    unsigned long long avlCompFrequent10 = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 10 most frequent values in Doubly-Linked List
    clock_t dllStart10 = clock();
    KeyFrequency *dllMostFrequent10 = findXMostFrequentDLL(doublyLinkedList, 10, dataSize);
    clock_t dllEnd10 = clock();
    double dllTimeFrequent10 = ((double)(dllEnd10 - dllStart10)) / CLOCKS_PER_SEC;
    unsigned long long dllCompFrequent10 = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 50 most frequent values in AVL Tree
    clock_t avlStart50 = clock();
    KeyFrequency *avlMostFrequent50 = findXMostFrequentAVL(avlTree, 50, dataSize);
    clock_t avlEnd50 = clock();
    double avlTimeFrequent50 = ((double)(avlEnd50 - avlStart50)) / CLOCKS_PER_SEC;
    unsigned long long avlCompFrequent50 = comparisonCount;
    comparisonCount = 0;

    // Measure time and comparison count for finding the 50 most frequent values in Doubly-Linked List
    clock_t dllStart50 = clock();
    KeyFrequency *dllMostFrequent50 = findXMostFrequentDLL(doublyLinkedList, 50, dataSize);
    clock_t dllEnd50 = clock();
    double dllTimeFrequent50 = ((double)(dllEnd50 - dllStart50)) / CLOCKS_PER_SEC;
    unsigned long long dllCompFrequent50 = comparisonCount;
    comparisonCount = 0;

    // Calculate duplicate percentage in AVL Tree
    int avlDuplicates = countDuplicatesAVL(avlTree, dataSize);
    float avlDupPercent = ((float)avlDuplicates / (float)dataSize) * 100;

    // Calculate duplicate percentage in Doubly-Linked List
    // int dllDuplicates = countDuplicatesDLL();
    // float dllDupPercent = (dllDuplicates / dataSize) * 100;

    // Print header
    printf("\n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("| %-93s |\n", "");
    printf("| %-19sPerformance Comparison: AVL Tree vs. Doubly-Linked List%-19s |\n", "", "");
    printf("| %-93s |\n", "");
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("\nData set: %d %s elements\n\n", dataSize, orderType);

    // Ṕrint result values from the AVL Tree
    printf("AVL Tree:\n");
    printf("%-25s%d\n", "  - Minimum:", avlMin);
    printf("%-25s%d\n", "  - Maximum:", avlMax);
    printf("%-25s%.1f\n", "  - Average:", avlAverage);
    printf("%-25s", "  - 10 most frequent:");
    printMostFrequent(avlMostFrequent10, 10);
    printf("\n%-25s", "  - 50 most frequent:");
    printMostFrequent(avlMostFrequent50, 50);
    printf("\n%-25s%.2f%%\n", "  - Duplicate %:", avlDupPercent);
    printf("\n\n");

    // Print result values from the Doubly-Linked List
    printf("Doubly-Linked List:\n");
    printf("%-25s%d\n", "  - Minimum:", dllMin);
    printf("%-25s%d\n", "  - Maximum:", dllMax);
    printf("%-25s%.1f\n", "  - Average:", dllAverage);
    printf("%-25s", "  - 10 most frequent:");
    printMostFrequent(dllMostFrequent10, 10);
    printf("\n%-25s", "  - 50 most frequent:");
    printMostFrequent(dllMostFrequent50, 50);
    // printf("%-25s%.2f%%\n", "  - Duplicate %%:", dllDupPercent);
    printf("\n\n");

    // Print time benchmarks in table format
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("| %-37sExecution Time (s)%-38s |\n", "", "");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("| %-24s | %-20s | %-20s | %-20s |\n", "Operation", "AVL Tree", "Doubly-Linked List", "AVL/DLL Ratio");
    printf("|-----------------------------------------------------------------------------------------------|\n");
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Insert data", avlTimeInsertion, dllTimeInsertion,
           avlTimeInsertion / dllTimeInsertion);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find min", avlTimeMin, dllTimeMin, avlTimeMin / dllTimeMin);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find max", avlTimeMax, dllTimeMax, avlTimeMax / dllTimeMax);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Calculate average", avlTimeAverage, dllTimeAverage,
           avlTimeAverage / dllTimeAverage);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find 10 most frequent", avlTimeFrequent10, dllTimeFrequent10,
           avlTimeFrequent10 / dllTimeFrequent10);
    printf("| %-24s | %-20.6f | %-20.6f | %-20.2f |\n", "Find 50 most frequent", avlTimeFrequent50, dllTimeFrequent50,
           avlTimeFrequent50 / dllTimeFrequent50);
    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("\n");

    // Print comparison benchmarks in table format
    //    printf("+-----------------------------------------------------------------------------------------------+\n");
    //    printf("| %-36sNumber of Comparisons%-36s |\n", "", "");
    //    printf("|-----------------------------------------------------------------------------------------------|\n");
    //    printf("| %-24s | %-20s | %-20s | %-20s |\n", "Operation", "AVL Tree", "Doubly-Linked List", "AVL/DLL Ratio");
    //    printf("|-----------------------------------------------------------------------------------------------|\n");
    //    printf("| %-24s | %-20llu | %-20llu | %-20llu |\n", "Insert data", avlCompInsertion, dllCompInsertion,
    //    (avlCompInsertion / dllCompInsertion)); printf("| %-24s | %-20llu | %-20llu | %-20llu |\n", "Find min",
    //    avlCompMin, dllCompMin, (avlCompMin / dllCompMin)); printf("| %-24s | %-20llu | %-20llu | %-20llu |\n", "Find
    //    max", avlCompMax, dllCompMax, (avlCompMax / dllCompMax)); printf("| %-24s | %-20llu | %-20llu | %-20llu |\n",
    //    "Calculate average", avlCompAverage, dllCompAverage, (avlCompAverage/ dllCompAverage)); printf("| %-24s |
    //    %-20llu | %-20llu | %-20llu |\n", "Find 10 most frequent", avlCompFrequent10, dllCompFrequent10,
    //    (avlCompFrequent10 / dllCompFrequent10)); printf("| %-24s | %-20llu | %-20llu | %-20llu |\n", "Find 50 most
    //    frequent", avlCompFrequent50, dllCompFrequent50, (avlCompFrequent50 / dllCompFrequent50));
    //    printf("+-----------------------------------------------------------------------------------------------+\n");
    //    printf("\n");

    // Destroy the trees to free memory
    destroyAVLTree(avlTree);
    destroyDoublyLinkedList(doublyLinkedList);

    return 0;
}
