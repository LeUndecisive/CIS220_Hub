#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Joshua S
// Chpt6 PA

// Define structure to represent the key-value pair (Item)
typedef struct Item {
    char *key;
    char *value;
    struct Item *next;
} Item;

// Define structure to represent the hash table
typedef struct HashTable {
    Item **hashTable;
    int length;
} HashTable;

// Function to create a new Item (key-value pair)
Item* createItem(char *key, char *value) {
    Item *newItem = (Item*)malloc(sizeof(Item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;
    return newItem;
}

// Function to create a new hash table with a specified number of buckets
HashTable* createHashTable(int size) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->length = size;
    table->hashTable = (Item**)malloc(sizeof(Item*) * size);

    for (int i = 0; i < size; i++) {
        table->hashTable[i] = NULL;
    }
    return table;
}

// Hash function to compute the index for a given key
int hash(char *key) {
	// Implement the function based on the PseudoCode provided in Figure 6.8.3, with 1 modification:
	// DO NOT mod(%) the stringHash by the number of buckets.
	int KeyHash = 0;
	int Length = strlen(key);
	int HashMult = 13;
	int i;

	for ( i = 0; i < Length; i++ ){
       KeyHash = (KeyHash * HashMult) + key[i];
	}

    return KeyHash;
}

// Function to insert a key-value pair into the hash table, pseudocode found in Figure 6.3.1
int hashInsert(HashTable *table, char *key, char *value) {
    int bucketIndex = hash(key) % table->length;

    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            free(currentItem->value);
            currentItem->value = strdup(value);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }

    Item *newItem = (Item *)malloc(sizeof(Item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;

    if (table->hashTable[bucketIndex] == NULL) {
        table->hashTable[bucketIndex] = newItem;
    } else {
        previousItem->next = newItem;
    }
    return 1;
}

// Function to search for the specified key and return the corresponding value, pseudocode found in Figure 6.3.1
char *hashGet(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;


    Item *item = table->hashTable[bucketIndex];

    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        item = item->next;
    }
    return NULL;
}

// Function to remove the key-value pair from the hash table, pseudocode found in Figure 6.3.1
int hashRemove(HashTable *table, char *key) {
    int bucketIndex = hash(key) % table->length;

    Item *currentItem = table->hashTable[bucketIndex];
    Item *previousItem = NULL;

    while (currentItem != NULL) {
        if (strcmp(currentItem->key, key) == 0) {
            if (previousItem == NULL) {
                table->hashTable[bucketIndex] = currentItem->next;
            } else {
                previousItem->next = currentItem->next;
            }
            free(currentItem->key);
            free(currentItem->value);
            free(currentItem);
            return 1;
        }
        previousItem = currentItem;
        currentItem = currentItem->next;
    }
    return 0;
}

// Function to print the contents of the hash table
// Update the function to display the hash for each key-value pair
void printTable(HashTable *table) {
    for (int i = 0; i < table->length; i++) {
        printf("Bucket %d: ", i);
        Item *currentItem = table->hashTable[i];
        if (currentItem == NULL) {
            printf("empty\n");
        } else {
            while (currentItem != NULL) {
                printf("[%s=%s] ", currentItem->key, currentItem->value);
                currentItem = currentItem->next;
            }
            printf("\n");
        }
    }
}

// Main function to test the hash table
// Implement the main function per the assignment instructions
int main() {
    // Create a hash table with 5 buckets
    HashTable *table = createHashTable(5);

    //---------Clear-Data-Free---------------
    for (int i = 0; i < table->length; i++) {
        Item *currentItem = table->hashTable[i];
        while (currentItem != NULL) {
            Item *temp = currentItem;
            currentItem = currentItem->next;
            free(temp->value);
            free(temp);
        }
    }

    //--------------Key-Inserts-------------
    Item *Key1 = createItem("keyA1","value1");
    hashInsert(table,Key1->key,Key1->value);

    Item *Key2 = createItem("keyB2","value2");
    hashInsert(table,Key2->key,Key2->value);

    Item *Key3 = createItem("keyC3","value3");
    hashInsert(table,Key3->key,Key3->value);

    Item *Key4 = createItem("keyD23","value23");
    hashInsert(table,Key4->key,Key4->value);

    Item *Key5 = createItem("keyE45","value45");
    hashInsert(table,Key5->key,Key5->value);

    Item *Key6 = createItem("keyF52","value52");
    hashInsert(table,Key6->key,Key6->value);

    //--------Display-Table----------
    printTable(table);
    printf("\n");

    //------Remove-n-Get-Keys-----------
    if (hashRemove(table,"keyF52") == 1){
        printf("keyF52 has been removed\n");
    }
    else{
        printf("keyF52 was not found\n");
    }


   if ( hashGet(table,"keyZ6") != NULL){
        printf("%s\n",hashGet(table,"keyZ6"));
    }
   else{
        printf("keyZ6 was not found within table\n");
    }

    //---------Key-Inserts------------
    Item *Key7 = createItem("keyG18","value7");
    hashInsert(table,Key7->key,Key7->value);

    Item *Key8 = createItem("keyH7","value7");
    hashInsert(table,Key8->key,Key8->value);

    Item *Key9 = createItem("keyI33","value33");
    hashInsert(table,Key9->key,Key9->value);

    //--------Key-Updates-----------
    hashInsert(table,Key4->key,"newvalue23");

    //--------Display-Table----------
    printf("\n");
    printTable(table);
    printf("\n");

    //-----Clear-Data-Free-------------
    free(table->hashTable);
    free(table);

    return 0;
}
