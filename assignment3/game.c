#include <stdio.h>
#include <stdlib.h>

#define ROCK 'r'
#define PAPER 'p'
#define SCISSORS 's'
#define QUIT 'q'

void clearInputBuffer() { // clears any unwanted characters in the input buffer
    while (getchar() != '\n') {
    }
}

char getPlayerMove() {
    char playerMove;
    while (1) { // 1 = true
        printf("Enter your move (r for rock, p for paper, s for scissors): ");
        scanf(" %c", &playerMove);

        clearInputBuffer();

        if (playerMove == ROCK || playerMove == PAPER ||
            playerMove == SCISSORS) {
            return playerMove;
        }

        printf("Invalid move. ");
    }
}

char getComputerMove() {
    int randNumber = rand() % 3; // create a domain of integers [0,2]
    switch (randNumber) {
    case 0:
        return ROCK;
    case 1:
        return PAPER;
    case 2:
        return SCISSORS;
    default:
        return ROCK;
    }
}

void determineWinner(char playerMove, char computerMove) {
    if (playerMove == computerMove) {
        printf("It's a tie!\n");
        return;
    }

    if ((playerMove == ROCK && computerMove == SCISSORS) ||
        (playerMove == PAPER && computerMove == ROCK) ||
        (playerMove == SCISSORS && computerMove == PAPER)) {
        printf("You win!\n");
    } else {
        printf("Computer wins!\n");
    }
}

void playRockPaperScissorsGame() {
    printf("Welcome to Rock, Paper, Scissors! Press 'q' to quit or any other "
           "key to continue:\n");
    char playerInput;

    scanf(" %c", &playerInput);

    clearInputBuffer();

    while (playerInput != QUIT) {
        char playerMove = getPlayerMove();
        char computerMove = getComputerMove();

        printf("Computer's move: %c\n", computerMove);
        determineWinner(playerMove, computerMove);

        printf("Press 'q' to quit or any other key to continue: \n");
        scanf(" %c", &playerInput);
        clearInputBuffer();
    }
    printf("Bye Bye!\n");
}

int main() {
    playRockPaperScissorsGame();
    return 0;
}
