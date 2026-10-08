#ifndef BST_H
#define BST_H

typedef struct Node {
    int data;
    char *question;
    char *guess;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert(Node *root, int data, char *question, char *guess);

#endif
