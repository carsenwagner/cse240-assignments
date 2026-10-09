#ifndef BST_H
#define BST_H

typedef struct Node {
    int data;
    const char *question;
    const char *guess;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int data, const char* question, const char *guess);
Node *insert(Node *root, int data, const char *question, const char *guess);
void free_tree(Node *root);

#endif
