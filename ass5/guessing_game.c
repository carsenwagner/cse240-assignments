#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QUIT 'q'
#define LB_CAPACITY 5
#define FILE_NAME "lb_file.txt"

typedef enum { F = 0, T = 1 } Bool;

typedef struct {
    char name[32];
    int score;
} Player;

// clear any unwanted characters from the input buffer
void clear_input_buffer() {
    while (getchar() != '\n') {
    }
}

// method to get the guess input from the user
int get_guess() {
    int guess;

    printf("Guess a value between 10 and 100: ");
    int num_values = scanf("%d", &guess);
    clear_input_buffer();

    while (num_values != 1 || guess < 10 || guess > 100) {
        printf("Make sure your guess is between 10 and 100: ");
        num_values = scanf("%d", &guess);
        clear_input_buffer();
    }
    return guess;
}

// gets the players name from the user
void get_player_name(char *name) {
    printf("Please enter your name to start: ");
    scanf("%31s", name);
    clear_input_buffer();
}

int read_lb_file(Player *lb, int max_entries) {
    FILE *file = fopen(FILE_NAME, "r");
    int count = 0;

    if (file == NULL) {
        return 0;
    }

    while (count < max_entries &&
           fscanf(file, "%31s %d", lb[count].name, &lb[count].score) == 2) {
        count++;
    }
    fclose(file);
    return count;
}

Bool write_lb_file(const Player *lb, int count) {
    FILE *file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        return F;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", lb[i].name, lb[i].score);
    }

    fclose(file);
    return T;
}

int compare_players(const void *a, const void *b) {
    const Player *p1 = (const Player *)a;
    const Player *p2 = (const Player *)b;

    if (p1->score < p2->score)
        return -1;
    if (p1->score > p2->score)
        return 1;
    return 0;
}

void sort_lb(Player *lb, int size) {
    qsort(lb, size, sizeof(Player), compare_players);
}

void print_lb_list(const Player *lb, int size) {
    printf("Here are the current leaders:\n");
    for (int i = 0; i < size; i++) {
        printf("%s made %d guesses\n", lb[i].name, lb[i].score);
    }
}

// main game running logic method
int play_guessing_game(Player *leaderboard, int lb_count) {
    int number_to_guess = rand() % 91 + 10;
    double square_root = sqrt(number_to_guess);
    char name[32];

    get_player_name(name);

    printf("%.8f is the square root of what number?", square_root);

    Bool done = F;
    int num_of_guesses = 0;

    while (!done) {
        int guess = get_guess();
        num_of_guesses++;

        if (guess < number_to_guess) {
            printf("Too low, guess again: ");
        } else if (guess > number_to_guess) {
            printf("Too high, guess again: ");
        } else {
            done = T;
        }
    }

    printf("You got it, baby!\n");
    printf("You made %d guesses.\n", num_of_guesses);

    strncpy(leaderboard[lb_count].name, name,
            sizeof(leaderboard[lb_count].name) - 1);
    leaderboard[lb_count].name[sizeof(leaderboard[lb_count].name) - 1] = '\0';
    leaderboard[lb_count].score = num_of_guesses;

    lb_count++;

    sort_lb(leaderboard, lb_count);

    if (lb_count > LB_CAPACITY) {
        lb_count = LB_CAPACITY;
    }

    print_lb_list(leaderboard, lb_count);
    return lb_count;
}

// entry point
int main() {
    Player leaderboard[LB_CAPACITY + 1];
    srand((unsigned int)time(NULL));
    printf("Welcome! Press 'q' to quit or any other key to continue:\n");

    int count = read_lb_file(leaderboard, LB_CAPACITY);
    char input, game_over = F;

    while (!game_over) {

        scanf(" %c", &input);
        clear_input_buffer();

        if (input == QUIT) {
            game_over = 1;
            printf("Bye Bye!\n");
        } else {
            count = play_guessing_game(leaderboard, count);
            printf("Press 'q' to quit or any other key to continue\n");
        }
    }

    write_lb_file(leaderboard, count);

    return 0;
}
