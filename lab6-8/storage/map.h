#ifndef MAP_H
#define MAP_H

#include "list/list.h"

typedef struct HashTable {
    int len;
    int capacity;
    Node** buckets;
} HashTable;

int get_hash(char*, int);
HashTable* ht_create(int);
void ht_insert(HashTable*, char*, int);
Node* ht_search(HashTable*, char*);
void ht_print(HashTable*);
void ht_delete(HashTable*, char*);
void ht_destroy(HashTable*);

#endif