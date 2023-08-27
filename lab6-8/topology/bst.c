#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Node* insert(Node* root, int id) {
    if (root == NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->id = id;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (root->id > id) {
        root->left = insert(root->left, id);
    } else if (root->id < id) {
        root->right = insert(root->right, id);
    } else {
        return NULL;
    }
    return root;
}

Node* remove_node(Node* root, int id) {
    if (root == NULL) {
        return NULL;
    }

    if (root->id == id) {
        // leaf
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        Node* current;
        // has only left child
        if (root->right == NULL) {
            current = root->left;
            free(root);
            return current;
        }
        // has only right child
        if (root->left == NULL) {
            current = root->right;
            free(root);
            return current;
        }
        // has left and right child
        current = root->right;
        while(current->left != NULL) {
            current = current->left;
        }
        root->id = current->id;
        root->right = remove_node(root->right, current->id);
    } else if (root->id > id) {
        root->left = remove_node(root->left, id);
    } else {
        root->right = remove_node(root->right, id);
    }
    return root;
}

Node* find(Node*  root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (root->id == id) {
        return root;
    } 
    if (root->id > id) {
        return find(root->left, id);
    } 
    return find(root->right, id);
}

int exist(Node* root, int id) {
    Node* result = find(root, id);
    if (result == NULL) {
        return 0;
    }
    return 1;
}

void recursive_print(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    recursive_print(root->left, depth+1);
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("%d\n", root->id);
    recursive_print(root->right, depth+1);
}

void print_tree(Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
    } else {
        recursive_print(root, 0);
    }
}

void recursive_delete(Node* root) {
    if (root == NULL) {
        return;
    }
    recursive_delete(root->left);
    recursive_delete(root->right);
    free(root);
}

Node* destroy_tree(Node* root) {
    recursive_delete(root);
    return NULL;
}
