#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int value;
    char* key;
    struct Node* next;
} Node;

Node* find_key(Node*, char*);
Node* add_key(Node*, char*, int);
Node* remove_key(Node*, char*);
void print_list(Node*);
Node* destroy_list(Node*);

#endif