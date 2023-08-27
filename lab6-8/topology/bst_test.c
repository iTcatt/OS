#include <stdio.h>
#include "bst.h"

int main() {
    Node* root = NULL;

    // insert elements
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 8);
    root = insert(root, 0);
    print_tree(root);

    // exist
    int result = exist(root, 4);
    int err = exist(root, 10);
    printf("Expected 1 and 0, return %d and  %d\n", result, err);
    
    // remove leaf
    root = remove_node(root, 8);
    // remove node with only right child
    root = remove_node(root, 6);
    // remove node with only left child
    root = remove_node(root, 1);
    // remove node with left and right child
    root = remove_node(root, 4);
    print_tree(root);
    // try remove invalid id
    root = remove_node(root, 10);
    // nothing changed
    print_tree(root);

    // destroy
    root = destroy_tree(root);
    print_tree(root);
    return 0;
}