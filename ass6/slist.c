#include "slist.h"
#include <stdlib.h>

// inserts a node to the head pointer of a linked list with a data type char *
void insert_head(SList *list, char *data) {
    Node *new_node = malloc(sizeof(Node));

    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;

    if (list->tail == NULL) {
        list->tail = new_node;
    }
}

// removes the head node of a linked list and returns the char *data at that
// node
char *remove_head(SList *list) {
    if (list->head == NULL) {
        return NULL;
    }
    Node *curr_head = list->head;
    char *data = curr_head->data;

    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }

    free(curr_head);
    return data;
}

// appends a new node at the end of a linked list with a data type char *
void insert_tail(SList *list, char *data) {
    Node *new_node = malloc(sizeof(Node));

    new_node->data = data;
    new_node->next = NULL;

    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

// removes the tail node of a linked list and returns the char *data to the
// value at that node
char *remove_tail(SList *list) {
    if (list->tail == NULL) {
        return NULL;
    }

    char *data = list->tail->data;
    if (list->head->next == NULL) { // 1 node in list
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return data;
    }

    Node *curr = list->head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }

    free(curr->next);
    curr->next = NULL; // clean dangling pointer
    list->tail = curr;
    return data;
}
