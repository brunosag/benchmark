#include "dll.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

DoublyLinkedList *createDoublyLinkedList()
{
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void destroyDoublyLinkedList(DoublyLinkedList *list)
{
    DLLNode *current = list->head;
    while (current != NULL)
    {
        DLLNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void pushFrontDLL(DoublyLinkedList *list, int key)
{
    DLLNode *newNode = (DLLNode *)malloc(sizeof(DLLNode));
    newNode->key = key;
    newNode->prev = NULL;
    newNode->next = list->head;

    if (list->head != NULL)
    {
        list->head->prev = newNode;
    }
    else
    {
        list->tail = newNode;
    }

    list->head = newNode;
}

void pushBackDLL(DoublyLinkedList *list, int key)
{
    DLLNode *newNode = (DLLNode *)malloc(sizeof(DLLNode));
    newNode->key = key;
    newNode->prev = list->tail;
    newNode->next = NULL;

    if (list->tail != NULL)
    {
        list->tail->next = newNode;
    }
    else
    {
        list->head = newNode;
    }

    list->tail = newNode;
}

void insertAfterDLL(DoublyLinkedList *list, DLLNode *prevNode, int key)
{
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL.");
        return;
    }

    DLLNode *newNode = (DLLNode *)malloc(sizeof(DLLNode));
    newNode->key = key;
    newNode->prev = prevNode;
    newNode->next = prevNode->next;

    if (prevNode->next != NULL)
    {
        prevNode->next->prev = newNode;
    }
    else
    {
        list->tail = newNode;
    }

    prevNode->next = newNode;

    prevNode->next = newNode;
}

void deleteNodeDLL(DoublyLinkedList *list, DLLNode *node)
{
    if (node == NULL)
    {
        printf("DLLNode to be deleted cannot be NULL.");
        return;
    }

    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->head = node->next;
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->tail = node->prev;
    }

    free(node);
}

void printListDLL(DoublyLinkedList *list)
{
    DLLNode *current = list->head;
    while (current != NULL)
    {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

// Function to insert ordered data in the Doubly-Linked List (1, 2, 3, ..., size)
void insertOrderedDataDLL(DoublyLinkedList *list, int size)
{
    for (int i = 1; i <= size; i++)
    {
        DLLNode *current = list->head;
        while (current != NULL && current->key < i)
        {
            current = current->next;
        }

        if (current == NULL)
        {
            pushBackDLL(list, i);
        }
        else
        {
            insertAfterDLL(list, current->prev, i);
        }
    }
}

// Function to insert unordered data in the Doubly-Linked List (random values between 1 and size)
void insertUnorderedDataDLL(DoublyLinkedList *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        int randomValue = rand() % size + 1;
        pushBackDLL(list, randomValue);
    }
}

// Function to find the minimum value in the Doubly-Linked List
int findMinDLL(DoublyLinkedList *list)
{
    compare();
    if (list->head == NULL)
    {
        printf("List is empty.\n");
        return -1;
    }

    int min = list->head->key;
    DLLNode *current = list->head->next;
    while (current != NULL)
    {
        if (current->key < min)
        {
            min = current->key;
        }
        current = current->next;
    }

    return min;
}

// Function to find the maximum value in the Doubly-Linked List
int findMaxDLL(DoublyLinkedList *list)
{
    if (list->head == NULL)
    {
        printf("List is empty.\n");
        return -1;
    }

    int max = list->head->key;
    DLLNode *current = list->head->next;
    while (current != NULL)
    {
        if (current->key > max)
        {
            max = current->key;
        }
        current = current->next;
    }

    return max;
}

// Function to calculate the average value in a Doubly-Linked List
float calculateAverageDLL(DoublyLinkedList *list)
{
    if (list->head == NULL)
    {
        printf("List is empty.\n");
        return -1;
    }

    int sum = 0;
    int count = 0;
    DLLNode *current = list->head;
    while (current != NULL)
    {
        sum += current->key;
        count++;
        current = current->next;
    }

    return (float)sum / count;
}

// Function to find the X most frequent values in the Doubly-Linked List
KeyFrequency *findXMostFrequentDLL(DoublyLinkedList *list, int X, int data_size)
{
    if (list->head == NULL || X <= 0)
    {
        return NULL;
    }

    KeyFrequency *frequencies = calloc(data_size, sizeof(KeyFrequency));
    KeyFrequency *result = calloc(X, sizeof(KeyFrequency));
    int frequencies_size = 0;

    // Find frequency of each value in list
    DLLNode *current = list->head;
    while (current != NULL)
    {
        bool keyExists = false;
        for (int i = 0; (i < frequencies_size) && (!keyExists); i++)
        {
            if (current->key == frequencies[i].key)
            {
                keyExists = true;
                frequencies[i].frequency++;
            }
        }
        if (!keyExists)
        {
            KeyFrequency newKey = {current->key, 1};
            frequencies[frequencies_size] = newKey;
            frequencies_size++;
        }
        current = current->next;
    }

    // Find X highest frequencies in array
    for (int i = 0; i < X; i++)
    {
        KeyFrequency most_frequent = {0, 0};
        int most_frequent_index = -1;
        for (int j = 0; j < frequencies_size; j++)
        {
            if (frequencies[j].frequency > most_frequent.frequency)
            {
                most_frequent = frequencies[j];
                most_frequent_index = j;
            }
        }
        result[i] = most_frequent;
        frequencies[most_frequent_index].frequency = -1; // Prevent key from being counted again
    }

    return result;
}
