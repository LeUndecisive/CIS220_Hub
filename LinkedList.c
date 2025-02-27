#include <stdio.h>
#include <stdlib.h>

// Joshua S
// Chpt4 PA

// Define a node structure for the singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a structure for the list itself
typedef struct List {
    Node* head;
    Node* tail;
} List;

// Function to allocate memory for a new node and initialize it with data
Node* allocateNewNode(int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty list
void initList(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Function to append a node to the list, pseudocode found in PA 4.2.6
void ListAppendNode(List* list, Node* newNode) {
	// If list is empty, new head and tail node
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
	// list not empty, new tail node
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Function to append an item to the list, pseudocode found in PA 4.2.6
void ListAppend(List* list, int item) {
	// Create node to add
    Node* newNode = allocateNewNode(item);
    ListAppendNode(list, newNode);
}

// Function to prepend a node to the list, pseudocode found in PA 4.2.9
void ListPrependNode(List* list, Node* newNode) {
	// If list is empty, new head and tail node
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
		// list not empty, new head node
        newNode->next = list->head;
        list->head = newNode;
    }
}

// Function to prepend an item to the list, pseudocode found in PA 4.2.9
void ListPrepend(List* list, int item) {
	// Create node to add
    Node* newNode = allocateNewNode(item);
    ListPrependNode(list, newNode);
}

// Function searches for a node with a specific data value, pseudocode found in PA 4.3.1
Node* ListSearch(List *list, int key) {
    Node *curNode = list->head;
    while (curNode != NULL) {
        if (curNode->data == key) {
            return curNode;
        }
        curNode = curNode->next;
    }
    return NULL;
}

// Function to insert a node after a specific node in the list, pseudocode found in PA 4.3.4
void ListInsertNodeAfter(List* list, Node* currentNode, Node* newNode) {
    // If list is empy, new head and tail node
	if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
	// Inserting after list's tail node, new tail node
    } else if (currentNode == list->tail) {
        list->tail->next = newNode;
        list->tail = newNode;
	// Inserting in middle of list
    } else {
        newNode->next = currentNode->next;
        currentNode->next = newNode;
    }
}

// Function to insert a new item after a specific item, pseudocode found in Figure 4.3.1
int ListInsertAfter(List *list, int currentItem, int newItem) {
	// Search for the node to insert after
    Node *currentNode = ListSearch(list, currentItem);
    if (currentNode != NULL) {
        Node *newNode = allocateNewNode(newItem);
		// Call ListInsertNodeAfter method
        ListInsertNodeAfter(list, currentNode, newNode);
		// Success
        return 1;
    }
	// Failure
    return 0;
}

// Function to remove a node after a specific node in the list, pseudocode found in PA 4.4.1
void ListRemoveNodeAfter(List* list, Node* curNode) {
    Node* sucNode;
	// Special case, remove head
    if (curNode == NULL) {  // Special case, remove head
        sucNode = list->head->next;
        list->head = sucNode;
		// Removed last item
        if (sucNode == NULL) {
            list->tail = NULL;
        }
	// Node exists after curNode
    } else if (curNode->next != NULL) {
        sucNode = curNode->next->next;
        curNode->next = sucNode;
		// Removed tail, set tail to curNode
        if (sucNode == NULL) {
            list->tail = curNode;
        }
    }
}

// Function to remove a node with a specific data value, pseudocode found in Figure 4.4.1
int ListRemove(List *list, int itemToRemove) {
    Node *previous = NULL;
    Node *current = list->head;
    while (current != NULL) {
        if (current->data == itemToRemove) {
			// Call ListRemoveNodeAfter method
            ListRemoveNodeAfter(list, previous);
            // Success
			return 1;
        }
        previous = current;
        current = current->next;
    }
    // Not found
    return 0;
}

// Function to traverse and print the list, pseudocode found in PA 4.8.1
void ListTraverse(List* list) {
	// Start at head
    Node* curNode = list->head;
    while (curNode != NULL) {
		// Prints the node's data
        printf("%d -> ", curNode->data);
        // Traverse to next node in the list
        curNode = curNode->next;
    }
    printf("NULL\n");
}

// Function to find the insertion position for a data value, pseudocode found in figure 4.9.1
Node* ListFindInsertionPosition(List* list, int dataValue) {
	// curNodeA keeps track of the node before the insertion position
    Node* curNodeA = NULL;
	// curNodeB starts at the head and traverses the list list
    Node* curNodeB = list->head;
	// Traverse the list until we find the correct insertion position
	// Stop when curNodeB is null (end of list) or dataValue is small than or equal to curNode
    while (curNodeB != NULL && dataValue > curNodeB->data) {
		// Move curNodeA to curNodeB (keeping track of previous node)
        curNodeA = curNodeB;
		// Move curNodeB to the next node
        curNodeB = curNodeB->next;
    }
	// Return curNodeA, which is the node after which the new value should be inserted
	// If curNodeA is null, it means the new value should be inserted at the head
    return curNodeA;
}

// Function to perform insertion sort on the list, pseudocode found in PA 4.9.1
void ListInsertionSortSinglyLinked(List* list) {
	// Initalize beforeCurrent to the head of the list
    Node* beforeCurrent = list->head;
	// Start curNode from the second node (if head is not null)
    Node* curNode = list->head ? list->head->next : NULL;
	// Traverse through the linked list
    while (curNode != NULL) {
		// Store the next node before manipulating curNode
        Node* next = curNode->next;
		// Find the correct position for curNode in the sorted portion of the list
        Node* position = ListFindInsertionPosition(list, curNode->data);
		// If curNode is already in the correct position, move beforeCurrent foward
        if (position == beforeCurrent) {
            beforeCurrent = curNode;
        } else {
			// Removes the curNode from its current position
            ListRemoveNodeAfter(list, beforeCurrent);
			// If position is null, curNode should be inserted at the beginning
            if (position == NULL) {
                ListPrependNode(list, curNode);
            } else {
				// Insert curNode after the found position
                ListInsertNodeAfter(list, position, curNode);
            }
        }
		// Move to the next node in the original list
        curNode = next;
    }
}

// Function to gather the sum of data within a list, returning a int variable
int sumDataValues(List* list){
        //We need to grab the 1st node of the list
        Node* currnode = list->head;
        // A var is needed to return and add all node data
        int DataSum = 0;
        while(currnode != NULL){
            DataSum += currnode->data;
            currnode = currnode->next;
        }
        return DataSum;
}
// main function
int main() {

    // Create our List and initilize it
    List listdata;
    initList(&listdata);

    // Showcase our list and its current sum
    ListTraverse(&listdata);
    printf("%d\n",sumDataValues(&listdata));

    // Append 2/ Prepend 1 data values
    ListAppend(&listdata,10);
    ListAppend(&listdata,20);
    ListPrepend(&listdata,30);
    ListTraverse(&listdata);

    // Insert 4 nodes after other nodes
    ListInsertAfter(&listdata,30,40);
    ListInsertAfter(&listdata,20,50);
    ListInsertAfter(&listdata,10,60);
    ListInsertAfter(&listdata,40,70);
    ListTraverse(&listdata);

    // Remove node
    ListRemove(&listdata,30);
    ListTraverse(&listdata);
    ListRemoveNodeAfter(&listdata,ListSearch(&listdata,70));
    ListTraverse(&listdata);

    // Search for nodes 50 and 15
   if (ListSearch(&listdata,50) != NULL){
     printf("Data value 50 was found\n");
   }else{
     printf("Data value 50 was not found\n");
   };

    if (ListSearch(&listdata,15) != NULL){
     printf("Data value 15 was found\n");
   }else{
     printf("Data value 15 was not found\n");
   };

    // Sort the list of nodes and print out the sum of data
    ListInsertionSortSinglyLinked(&listdata);
    ListTraverse(&listdata);
    printf("Sum of data within the list: %d",sumDataValues(&listdata));
    return 0;
}
