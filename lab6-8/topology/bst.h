#ifndef BST_H
#define BST_H

typedef struct Node {
    int id;
    struct Node* left;
    struct Node* right;
} Node;

Node* insert(Node*, int);
Node* remove_node(Node*, int);
Node* find(Node*, int);
int exist(Node*, int);
void print_tree(Node*);
Node* destroy_tree(Node*);

#endif