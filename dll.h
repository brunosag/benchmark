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
void pushDLL(DoublyLinkedList *list, int key);
void insertAfterDLL(DoublyLinkedList *list, DLLNode *prevNode, int key);
void printDLL(DoublyLinkedList *list);

void insertOrderedDataDLL(DoublyLinkedList *list, int dataSize); // Benchmark specific functions
void insertUnorderedDataDLL(DoublyLinkedList *list, int dataSize);
int findMinDLL(DoublyLinkedList *list);
int findMaxDLL(DoublyLinkedList *list);
float calculateAverageDLL(DoublyLinkedList *list);
KeyFrequency *findXMostFrequentDLL(DoublyLinkedList *list, int X, int dataSize);

#endif /* DLL_H */
