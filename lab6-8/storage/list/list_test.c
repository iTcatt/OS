#include <stdio.h>
#include "list.h"

int main() {
    Node* map = NULL;

    // add elements
    map = add_key(map, "hah", 3);
    map = add_key(map, "lol", 1);
    map = add_key(map, "ugl", 8);
    print_list(map);
    
    // update value
    map = add_key(map, "lol", 19);
    print_list(map);

    // find
    Node* result = find_key(map, "lol");
    printf("Expected 19, returned %d", result->value);
    Node* err = find_key(map, "non");
    if (err == NULL) {
        printf("This key hasn't in list");
    }

    // remove key
    map = remove_key(map, "lol");
    map = remove_key(map, "ugl");
    print_list(map);

    // nothing
    map = remove_key(map, "non");
    print_list(map);
    
    // remove head
    map = remove_key(map, "hah");

    // try remove null
    map = remove_key(map, "null");
    if (map == NULL) {
        printf("Error: list is empty\n");
    }

    // empty
    print_list(map);

    // destroy
    map = add_key(map, "hah", 3);
    map = add_key(map, "lol", 1);
    map = add_key(map, "ugl", 8);
    map = destroy_list(map);
    print_list(map);
    return 0;
}