#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list/list.h"
#include "map.h"

int get_hash(char* string, int map_size) {
    int hash = 0;
    for (int i = 0; i < strlen(string); i++) {
        hash = (hash * string[i] + string[i]) % map_size;
    }
    return hash;
}

HashTable* ht_create(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->len = 0;
    table->capacity = size;
    table->buckets = (Node**)calloc(size, sizeof(Node*));
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

void ht_insert(HashTable* table, char* key, int value) {
    int hash = get_hash(key, table->capacity);
    table->buckets[hash] = add_key(table->buckets[hash], key, value);
}

Node* ht_search(HashTable* table, char* key) {
    int hash = get_hash(key, table->capacity);
    return find_key(table->buckets[hash], key);
}

void ht_print(HashTable* table) {
    if (table == NULL) {
        printf("Map is empty\n");
        return;
    }
    for (int i = 0; i < table->capacity; i++) {
        Node* temp = table->buckets[i];
        if (temp != NULL) {
            print_list(table->buckets[i]);
        }
    }
}

void ht_delete(HashTable* table, char* key) {

}

void ht_destroy(HashTable* table) {
    if (table == NULL) {
        return;
    }
    for (int i = 0; i < table->capacity; i++) {
        Node* temp = table->buckets[i];
        if (temp != NULL) {
           temp = destroy_list(table->buckets[i]);
        }
    }
    free(table->buckets);
    free(table);
}