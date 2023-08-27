#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

Node* find_key(Node* head, char* find_key) {
    Node* current = head;
    while (current != NULL) {
        if (!strcmp(current->key, find_key)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node* add_key(Node* head, char* key, int value) {
    Node* current = head;
    while (current != NULL) {
        if (!strcmp(current->key, key)) {
            current->value = value;
            return head;
        }
        current = current->next;
    }
    Node* new_head = (Node*)malloc(sizeof(Node));
    new_head->key = (char*)malloc(strlen(key) + 1);
    strcpy(new_head->key, key);
    new_head->value = value;
    new_head->next = head;
    return new_head;
}

Node* remove_key(Node* head, char* key) {
    if (head == NULL) {
        return NULL;
    }
    if (!strcmp(head->key, key)) {
        Node* new_head = head->next;
        free(head->key);
        free(head);
        return new_head;
    }

    Node* parent = NULL;
    Node* current = head;
    while(current != NULL) {
        if (!strcmp(current->key, key)) {
            parent->next = current->next;
            free(current->key);
            free(current);
            return head;
        }
        parent = current;
        current = current->next;
    } 
    return head;
}

void print_list(Node* head) {
    if (head == NULL) {
        printf("Map is empty\n");
        return;
    }
    Node* current = head;
    while (current != NULL) {
        printf("\t%s: %d\n", current->key, current->value);
        current = current->next;
    }
}

Node* destroy_list(Node* head) {
    Node* current = head;
    while(current != NULL) {
        Node* next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    return NULL;
}
