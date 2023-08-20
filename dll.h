#ifndef DLL_H
#define DLL_H

#include "main.h"

// Node structure for Doubly-Linked-List
typedef struct DLLNode
{
    int key;
    struct DLLNode *prev;
    struct DLLNode *next;
} DLLNode;

// Doubly-Linked List ADT
typedef struct DoublyLinkedList
{
    DLLNode *head;
    DLLNode *tail;
} DoublyLinkedList;

DoublyLinkedList *createDoublyLinkedList(); // Main ADT functions
void destroyDoublyLinkedList(DoublyLinkedList *list);
void insertDLL(DoublyLinkedList *list, int key);
void printDLL(DoublyLinkedList *list);

void insertDataDLL(DoublyLinkedList *list, int *dataset, int dataSize); // Benchmark specific functions
int findMinDLL(DoublyLinkedList *list);
int findMaxDLL(DoublyLinkedList *list);
float calculateAverageDLL(DoublyLinkedList *list);
KeyFrequency *findXMostFrequentDLL(DoublyLinkedList *list, int X, int dataSize);

#endif /* DLL_H */
