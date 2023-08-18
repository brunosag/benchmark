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
void pushFrontDLL(DoublyLinkedList *list, int data);
void pushBackDLL(DoublyLinkedList *list, int data);
void insertAfterDLL(DoublyLinkedList *list, DLLNode *prevNode, int data);
void deleteNodeDLL(DoublyLinkedList *list, DLLNode *node);
void printListDLL(DoublyLinkedList *list);

void insertOrderedDataDLL(DoublyLinkedList *list, int data_size); // Benchmark specific functions
void insertUnorderedDataDLL(DoublyLinkedList *list, int data_size);
int findMinDLL(DoublyLinkedList *list);
int findMaxDLL(DoublyLinkedList *list);
float calculateAverageDLL(DoublyLinkedList *list);
KeyFrequency *findXMostFrequentDLL(DoublyLinkedList *list, int X, int data_size);

#endif /* DLL_H */
