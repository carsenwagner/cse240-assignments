#include <stdio.h>

#include "bst.h"

#define QUIT 'q'
#define YES 'y'
#define NO 'n'

Node *create_game_tree() {
    Node *root = NULL;
    root = insert(root, 100, "Does it grow underground?", "");
    insert(root, 50, "Is it long in shape?", "");
    insert(root, 25, "Is it orange in color?", "");
    insert(root, 15, "", "It's a carrot!");
    insert(root, 35, "", "It's a parsnip!");
    insert(root, 75, "Is it red in color?", "");
    insert(root, 65, "", "It's a radish!");
    insert(root, 85, "", "It's a potato!");
    insert(root, 150, "Does it grow on a tree?", "");
    insert(root, 125, "Is it red in color?", "");
    insert(root, 115, "", "It's an apple!");
    insert(root, 135, "", "It's a peach!");
    insert(root, 175, "Is it red in color?", "");
    insert(root, 165, "", "It's a tomato!");
    insert(root, 185, "", "It's a pea!");
    
    return root;
}

void clear_input_buffer() {
    while (getchar() != '\n') {}
}

void play_game(Node *game_tree) {
    Node *current = game_tree;

    char player_answer; 

    while (current != NULL) { 
        if (*(current->question) == 0) {
            printf("%s\n", current->guess);
          
            printf("y/n: ");

            scanf(" %c", &player_answer);
            clear_input_buffer();
            
            if (player_answer == YES) {
                printf("I win!\n");
            } else if (player_answer == NO) {
                printf("You win!\n");
            }
            return;
        }

        printf("%s\n", current->question);
        printf("y/n: ");
        scanf(" %c", &player_answer);
        clear_input_buffer();

        if (player_answer == YES) {
            current = current->left;
        } else if (player_answer == NO) {
            current = current->right;
        } else {
            printf("Please enter y/n:\n");
        }
    } 
}

int main() { 
    Node *game_tree = create_game_tree(); 
    
    printf("Welcome press 'q' to quit or any other key to continue:\n");
    fflush(stdout);

    char input;

    scanf(" %c", &input);
    clear_input_buffer();

    while (input != QUIT) {
        printf("You think of a fruit or vegetable and I will try to guess it!\n");

        play_game(game_tree);

        printf("Press 'q' to quit or any other key to continue:\n");
        scanf(" %c", &input);
        clear_input_buffer();
    }
    printf("Bye Bye!\n");


    free_tree(game_tree);
    return 0;
}
