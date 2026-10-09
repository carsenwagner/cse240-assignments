#include <stdlib.h>

#include "bst.h"


Node *create_node(int data, const char *question, const char *guess) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("Allocation Failed");
        exit(EXIT_FAILURE);
    }
    
    new_node->data = data;
    new_node->question = question;
    new_node->guess = guess;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node; 
}

Node *insert(Node *root, int data, const char *question, const char *guess) {
    if (root == NULL) {
        root = create_node(data, question, guess);
        return root; 
    }
    if (data < root->data) {
        root->left = insert(root->left, data, question, guess);
    } else {
        root->right = insert(root->right, data, question, guess);
    }
    return root;
}

void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
