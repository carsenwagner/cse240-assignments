#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

#define QUIT 'q'
#define FILE_NAME "names.txt"
#define MAX_NAME_LENGTH 100
#define FORWARD 'f'
#define BACKWARD 'b'

typedef SList Deque;

typedef enum { F = 0, T = 1 } Bool;

void clear_input_buffer() {
    while (getchar() != '\n') {
    }
}

void push_back(Deque *q, char *data) { insert_tail(q, data); }

void push_front(Deque *q, char *data) { insert_head(q, data); }

char *pop_back(Deque *q) { return remove_tail(q); }

char *pop_front(Deque *q) { return remove_head(q); }

void populate_deque_from_file(Deque *q) {
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("Couldnt open file: %s\n", FILE_NAME);
        return;
    }

    while (T) {
        char *name = malloc(MAX_NAME_LENGTH);
        if (fscanf(fp, "%99s", name) == 1) {
            push_back(q, name);
        } else {
            free(name);
            break;
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    printf("To scroll through the names type\n");
    printf("f: forwards, b: backwards, q: quit\n");

    Deque q = {NULL, NULL};
    populate_deque_from_file(&q);
    char input;

    scanf(" %c", &input);
    clear_input_buffer();

    while (input != QUIT) {
        switch (input) {
        case FORWARD: {
            char *name = pop_front(&q);
            printf("%s\n", name);
            push_back(&q, name);
            break;
        }
        case BACKWARD: {
            char *name = pop_back(&q);
            printf("%s\n", name);
            push_front(&q, name);
            break;
        }
        }
        scanf(" %c", &input);
        clear_input_buffer();
    }
    printf("Bye!\n");
}
