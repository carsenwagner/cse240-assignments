#include <stdio.h>
#include <string.h>

#define NUM_ROWS 5
#define NUM_COLS 5
#define QUIT 'q'
#define delim ","
#define NUM_OF_GENERATIONS 7

typedef enum { F = 0, T = 1 } Bool;

// clears any leftover input in the buffer
void clear_input_buffer() {
    while (getchar() != '\n') {
    }
}

// parses a str or char array into an integer
int parse_str_to_int(const char *val) { // const means i promise not to change
                                        // the contents at this memory address
    int result = 0;

    while (*val != '\0') { // check for null terminator
        result =
            (result * 10) + (*val - '0'); // current char - '0' where '0' is 48
        val++;                            // increment pointer by 1
    }
    return result;
}

// gets the initial state from the user and returns the number of alive cells
int get_initial_state(int init_state[]) {
    char input_str[100];
    char *token;
    int count = 0;

    printf("Enter the offsets for the live cells:\n");
    scanf("%s", input_str);
    token = strtok(input_str, delim);

    while (token != NULL) {
        init_state[count] = parse_str_to_int(token);
        count++;

        token = strtok(NULL, delim);
    }
    return count;
}

// sets the initial state of the board based off the user input
void set_initial_state(char board[][NUM_COLS], const int init_state[],
                       int num_alive) {
    for (int i = 0; i < num_alive; i++) {
        int offset = init_state[i];
        int row = offset / NUM_ROWS;
        int column = offset % NUM_COLS;
        board[row][column] = T;
    }
}

// counts the amount of live cells around the current place on the board
int count_live_neighbors(const char board[][NUM_COLS], int row, int column) {
    int delta_row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int delta_column[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;

    for (int i = 0; i < 8; i++) {
        int neighbor_row = row + delta_row[i];
        int neighbor_column = column + delta_column[i];

        if (neighbor_row < 0 || neighbor_row >= NUM_ROWS ||
            neighbor_column < 0 || neighbor_column >= NUM_COLS) {
            continue;
        }
        count += board[neighbor_row][neighbor_column];
    }
    return count;
}

// generates the next generation and applies it to the board
void next_generation(char current_board[][NUM_COLS]) {
    char new_board[NUM_ROWS][NUM_COLS];

    memcpy(new_board, current_board, sizeof(new_board));

    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            int live_neighbors = count_live_neighbors(new_board, r, c);
            char val = new_board[r][c];

            if (val == T && (live_neighbors < 2 || live_neighbors > 3)) {
                current_board[r][c] = F;
            }

            if (val == F && live_neighbors == 3) {
                current_board[r][c] = T;
            }
        }
    }
}

// prints the board
void print_board(const char board[][NUM_COLS]) {
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            char val = board[r][c];

            if (val == T) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// method to play the game of life
void play_game_life() {
    char input;

    printf("Welcome! Press 'q' to quit or any other key to continue:\n");
    scanf(" %c", &input);
    clear_input_buffer();

    while (input != QUIT) {
        char board[NUM_ROWS][NUM_COLS] = {F};
        int init_state[NUM_ROWS * NUM_COLS];

        int num_alive = get_initial_state(init_state);
        set_initial_state(board, init_state, num_alive);

        for (int i = 0; i < NUM_OF_GENERATIONS; i++) {
            printf("generation = %d:\n", i);
            print_board(board);
            next_generation(board);
        }

        printf("Good life!\n");
        printf("Press 'q' to quit or any other key to continue:\n");
        scanf(" %c", &input);
        clear_input_buffer();
    }
    printf("Bye Bye!\n");
}

// entry point
int main() {
    play_game_life();
    return 0;
}
