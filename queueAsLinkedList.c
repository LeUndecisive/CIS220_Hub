#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Joshua S
// Chpt5 PA

// Define a Node structure for each element in the queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a Queue structure to represent the queue implemented as a linked list
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create and initialize an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Enqueue operation: adds an item to the end of the queue, pseudocode found in PA 5.5.1
void enqueue(Queue* queue, int item) {
    // Allocate new node and assign data (newNode->next is set to NULL)
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
	// Set the node's member values
    newNode->data = item;
    newNode->next = NULL;

    if (queue->front == NULL) {
        // If the queue is empty, set front to the new node
        queue->front = newNode;
    } else {
        // Otherwise, link the new node at the end of the queue
        queue->rear->next = newNode;
    }
    // Update the rear pointer to the new node
    queue->rear = newNode;
}

// Dequeue operation: removes and returns the item from the front of the queue, pseudocode found in PA 5.5.1
int dequeue(Queue* queue) {
	// If queue is empty return -1 (assuming only positive integers will be added)
    if (queue->front == NULL) {
        return -1;
    }
    // Save the data from the front node and move the front pointer
    Node* temp = queue->front;
    int dequeuedItem = temp->data;
    queue->front = temp->next;
    // If the queue becomes empty, update the rear pointer to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
	// free memory for the dequeued node
    free(temp);
    return dequeuedItem;
}

// Function to check if the queue is empty
bool isEmpty(Queue* queue) {
    // Implement function
     if (queue->front == NULL) {
        return false;
    }else{
        return true;
    }
}

// Function to peek at the front item without removing it
int peek(Queue* queue) {
    // Implement function
    if (queue->front == NULL) {
        return 0;
    }else{
        return queue->front->data;
    }
}

// Function to get the length of the queue
int getLength(Queue* queue) {
    // Implement function
    int Length = 0;
    Node* CurNode = queue->front;
    while (CurNode != NULL){
        Length = Length + 1;
        CurNode = CurNode->next;
    }
    return Length;
}

// Function to traverse and display the queue
void displayQueue(Queue* queue) {
    // Implement function
    Node* CurNode = queue->front;
    while (CurNode != NULL){
        printf("%d",CurNode->data);
        CurNode = CurNode->next;
        printf(" -> ");
    }
    printf("NULL\n");
}

int main() {

    int DeqResults;
    Queue* queue = createQueue();


    // Dsplaying an empty queue 1-4
    displayQueue(queue);

    if (isEmpty(queue)){
        printf("Queue contains items\n");
    }else{
        printf("Queue contains no items\n");
    }

    if (peek(queue) != 0){
        printf("Top Item: %d\n",peek(queue));
    }else{
        printf("Queue contains no items\n");
    }

    printf("Queue length: %d\n",getLength(queue));

    //  Enqueue 2 items and display 5-7
    enqueue(queue,1);
    enqueue(queue,2);
    printf("Top Item: %d\n",peek(queue));

    // Enqueue 3rd item and dequeue 8-20
    enqueue(queue,3);
    printf("Queue length: %d\n",getLength(queue));
    printf("dequeued: %d\n",dequeue(queue));

    if (peek(queue) != 0){
        printf("Top Item: %d\n",peek(queue));
    }else{
        printf("Queue contains no items\n");
    }


    enqueue(queue,4);
    displayQueue(queue);

    enqueue(queue,5);
    printf("dequeued: %d\n",dequeue(queue));

    enqueue(queue,6);
    printf("Queue length: %d\n",getLength(queue));
    displayQueue(queue);
    printf("dequeued: %d\n",dequeue(queue));


    if (isEmpty(queue)){
        printf("Queue contains items\n");
    }else{
        printf("Queue contains no items\n");
    }

    // Dequeing all items 21-26
    printf("%d dequeued\n",dequeue(queue));
    printf("%d dequeued\n",dequeue(queue));
    printf("Queue length: %d\n",getLength(queue));
    printf("dequeued: %d\n",dequeue(queue));

    DeqResults = dequeue(queue);
    if (DeqResults != -1){
        printf("dequeued: %d\n",DeqResults);
    }else{
        printf("No Items were dequeued\n");
    }


    if (isEmpty(queue)){
        printf("Queue contains items\n");
    }else{
        printf("Queue contains no items\n");
    }
 // Free the queue structure (all nodes should have been dequeued by now)
    free(queue);

    return 0;
}
