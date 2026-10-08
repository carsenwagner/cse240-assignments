#ifndef SLIST_H
#define SLIST_H

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} SList;

void insert_head(SList *list, char *data);
char *remove_head(SList *list);
void insert_tail(SList *list, char *data);
char *remove_tail(SList *list);

#endif
