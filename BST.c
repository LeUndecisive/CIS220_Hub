#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 10

// Definition of the BST Node
typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Function to create a new BST node
BSTNode* createNode(int key) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Definition of the Binary Search Tree (BST)
typedef struct BST {
    BSTNode* root;
} BST;

// Function to create an empty BST
BST* createBST() {
    BST* tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

BSTNode* getRoot(BST* tree) {
    return tree->root;
}

// Implement the BSTSearchRecursive PseudoCode found in PA 7.9.1
BSTNode* searchRecursive(BSTNode* node, int key) {
	if (node != NULL){


        if (key == node->key){
            return node;
        }
        else if (key < node->key) {
            return searchRecursive(node->left,key);
        }
        else {
            return searchRecursive(node->right,key);
        }
	}
	return NULL;

}

// Implement the BSTSearch PseudoCode found in PA 7.9.1
BSTNode* search(BST* tree, int key) {
	return searchRecursive(tree->root,key);}

// Function to check if the tree contains a node with the given key
bool contains(BST* tree, int key) {
    return search(tree, key) != NULL;
}

// Implement the BSTInsertRecursive PseudoCode found in Fig. 7.9.2
void insertRecursive(BSTNode* parent, BSTNode* nodeToInsert) {
    if (nodeToInsert->key < parent->key) {

        if (parent->left == NULL)
            parent->left = nodeToInsert;
        else{
            insertRecursive(parent->left, nodeToInsert);
        }

    }else{
        if (parent->right == NULL)
            parent->right = nodeToInsert;
        else{
               insertRecursive(parent->right, nodeToInsert);
        }
    }
}
// Implement the BSTInsertNode PseudoCode found in Fig. 7.9.2
void insertNode(BST* tree, BSTNode* node) {
    if(tree->root == NULL){
        tree->root = node;
    }
    else{
        insertRecursive(tree->root,node);
    }
}

// Function to insert a key into the BST
bool insertKey(BST* tree, int key) {
    if (contains(tree, key)) {
        return false; // Duplicate keys not allowed
    }
	// Create a new node
    BSTNode* newNode = createNode(key);
	// Call insertNode method
    insertNode(tree, newNode);
    return true;
}

// Implement a printInReverseOrder function discussed in Section 7.7
void printInReverseOrder(BSTNode* node) {
    if (node != NULL){
        printInReverseOrder(node->right);
        printf(" %d ", node->key);
        printInReverseOrder(node->left);
    }
}

 // Function to print the binary tree in 2D using reverse inorder traversal
void print2DUtil(BSTNode* root, int space) {
    // Base case: If the node is NULL, return
    if (root == NULL) {
        return;
    }

    // Increase space for the next level
    space += COUNT;

    // First, process the right child
    print2DUtil(root->right, space);

    // Print the current node after space count
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);

    // Then, process the left child
    print2DUtil(root->left, space);
}

// Wrapper function to print the tree
void print2D(BSTNode* root) {
    // Start with 0 space
    print2DUtil(root, 0);
}

// Function to free memory allocated for BST nodes
void freeTree(BSTNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Implement the main function based on the program instructions
int main() {

//------------Variables--------------------
    int Keys[] = {35,41,13,57,3,83,88,51,38,20,11,22,27,21,48,8}; //16 items (16 - 1)
    int Amountofkeys = 16;
    int i;

//------Creating-Empty-Tree-----------
    BST* tree = createBST();

//--------Filling-Tree-------------
    for (i = 0; i < Amountofkeys - 1; ++i){
        BSTNode* NewNode = createNode(Keys[i]);
        insertNode(tree,NewNode);
    }

//--------Displaying-Tree-----------------
    printf("Binary Search Tree After Inserts:\n");
    printInReverseOrder(tree->root);

    printf("\n");
    print2D(tree->root);

//-------Searching-For-Keys------------------
    if (search(tree,27) != NULL){
        printf("Found node with key: 27\n");
    }else{
        printf("Key 27 not found\n");
    }

    printf("\n");

    if (search(tree,89) != NULL){
        printf("Found node with key: 27\n");
    }else{
        printf("Key 89 not found\n");
    }

//------Clearing-Memory-End------------------
    freeTree(tree->root);
	free(tree);

    return 0;
}
