#include <cmath>
#include <cstdlib>
#include <ctime>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#define QUIT 'q'
const std::string LEADERBOARD_FILE = "leaderboard.txt";

class Player {
public:
  Player() : name(""), num_guess(0) {}
  Player(std::string name, int num_guess)
      : name(std::move(name)), num_guess(num_guess) {}

  void prompt_name() {
    std::cout << "Please enter your name to start:";
    std::cin >> name;
  }

  void set_guess(int num) { num_guess = num; }
  int get_guesses() const { return num_guess; }
  const std::string &get_name() const { return name; }

private:
  std::string name;
  int num_guess;
};

class LeaderBoard {
public:
  LeaderBoard() : count(0) {}

  void read_leaders(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
      return;
    }

    count = 0;
    std::string name;
    int guesses;
    while (count < NUM_LEADERS && file >> name >> guesses) {
      leaders[count] = Player(name, guesses);
      count++;
    }
    file.close();
  }

  void save_leaders(const std::string &file_path) const {
    std::ofstream file(file_path);
    if (!file.is_open()) {
      return;
    }

    for (int i = 0; i < count; i++) {
      file << leaders[i].get_name() << " " << leaders[i].get_guesses() << "\n";
    }
    file.close();
  }

  void insert_player(Player player) {
    int i = 0;
    while (i < count && leaders[i].get_guesses() <= player.get_guesses()) {
      i++;
    }

    if (i < NUM_LEADERS) {
      int start = (count < NUM_LEADERS) ? count : NUM_LEADERS - 1;
      for (int j = start; j > i; j--) {
        leaders[j] = leaders[j - 1];
      }
      leaders[i] = player;

      if (count < NUM_LEADERS) {
        count++;
      }
    }
  }

  void print_leaders() const {
    std::cout << "Here are the current leaders:\n";
    for (int i = 0; i < count; i++) {
      std::cout << leaders[i].get_name() << " made " << leaders[i].get_guesses()
                << " guesses\n";
    }
  }

private:
  static const int NUM_LEADERS = 5;
  Player leaders[NUM_LEADERS];
  int count;
};

int get_guess() {
  int guess;
  std::cout << "Guess a value between 10 and 100: ";
  std::cin >> guess;
  return guess;
}

void play_guess_game(LeaderBoard &leaderboard) {
  int number_to_guess = std::rand() % 91 + 10;
  double square_root = std::sqrt(number_to_guess);
  Player player;

  player.prompt_name();

  std::cout << std::fixed << std::setprecision(8);
  std::cout << square_root << " is the square root of what number?";

  bool done = false;
  int num_of_guesses = 0;

  while (!done) {
    int guess = get_guess();
    num_of_guesses++;

    if (guess < number_to_guess) {
      std::cout << "Too low, guess again: ";
    } else if (guess > number_to_guess) {
      std::cout << "Too high, guess again: ";
    } else {
      done = true;
    }
  }

  std::cout << "You got it, baby!\n";
  std::cout << "You made " << num_of_guesses << " guesses.\n";

  player.set_guess(num_of_guesses);
  leaderboard.insert_player(player);
  leaderboard.print_leaders();
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  LeaderBoard leaderboard;
  leaderboard.read_leaders(LEADERBOARD_FILE);

  std::cout << "Welcome! Press 'q' to quit or any other key to continue:\n";

  char input;
  bool game_over = false;

  while (!game_over) {
    std::cin >> input;

    if (input == QUIT) {
      game_over = true;
      std::cout << "Bye Bye!\n";
      leaderboard.save_leaders(LEADERBOARD_FILE);
    } else {
      play_guess_game(leaderboard);
      std::cout << "Press 'q' to quit or any other key to continue\n";
    }
  }
  return 0;
}
