#include <stdio.h>
#include "map.h"

int main() {
    int size = 50;
    HashTable* map = ht_create(size);
    int hash1, hash2, hash3;
    hash1 = get_hash("lol", size);
    hash2 = get_hash("hah", size);
    hash3 = get_hash("long", size);
    printf("1 - %d\n2 - %d\n3 - %d\n", hash1, hash2, hash3);

    ht_insert(map, "lol", 5);
    ht_insert(map, "lo", 55);
    ht_insert(map, "hah", 11);
    ht_insert(map, "newnode", 1);
    ht_insert(map, "you", 50);
    ht_print(map);

    Node* find = ht_search(map, "lo");
    printf("Key %s - value %d\n", find->key, find->value);
    find = ht_search(map, "newnode");
    printf("Key %s - value %d\n", find->key, find->value);
    Node* err = ht_search(map, "nothing");
    if (err == NULL) {
        printf("This key not in map\n");
    }
    
    ht_destroy(map);
    return 0;
}