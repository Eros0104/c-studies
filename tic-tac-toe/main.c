#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define DRAW 0
#define PLAYER_WIN 1
#define GAME_IS_NOT_OVER -1

char board_values[3][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
};

struct board_coordinate {
  int i;
  int j;
};

void draw_board();
void draw_connect_line();
void draw_line(char a, char b, char c);
void draw_empty_line();
void clear_screen();
void red();
void yellow();
void green();
void reset_color();
int check_game_over(int current_player, int turn);
bool is_diagonal_complete();
bool is_vertical_complete();
bool is_horizontal_complete();
struct board_coordinate get_board_coordinate(char value);

int main() {
  int current_player = 1;
  char input;
  int turn = 1;
  int game_over = GAME_IS_NOT_OVER;

  printf("Player 1: (x) - Player 2: (o)");
 
  clear_screen();
  draw_board();

  do {
    printf("Player %d turn. Enter a number: ", current_player);
    // space inserted before "%c" to consume newline from previous run 
    scanf(" %c", &input);

    struct board_coordinate coordinates = get_board_coordinate(input);  
    
    printf("%d", coordinates.i);
    if (coordinates.i != -1 && isdigit(board_values[coordinates.i][coordinates.j])) {
      
      board_values[coordinates.i][coordinates.j] = current_player == 1 ? 'x' : 'o';
      
      game_over = check_game_over(current_player, turn); 
    
      turn = turn + 1;

      current_player = (current_player % 2) ? 2 : 1;

      clear_screen();
    } else {
      clear_screen();
      red();
      printf("Invalid move!");
      reset_color();
    }

    draw_board();

  } while (game_over == GAME_IS_NOT_OVER);
  
  if (game_over == DRAW) {
    yellow();
    printf("Draw!");
  } else {
    green();
    printf("Player %d won!", current_player);
  }

  return 0;
}

struct board_coordinate get_board_coordinate (char value) {
  int i, j;
  struct board_coordinate result = { -1, -1 };

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (board_values[i][j] == value) {
        result.i = i;
	result.j = j;
      }
    }
  }

  return result;
}

bool is_even(int board_index) {
  return (board_index % 2) == 0;
}

bool is_diagonal_complete() {
  // implement logic
  return false;
}

bool is_vertical_complete() {
  // implement logic
  return false;
}

bool is_horizontal_complete() {
  // implement logic
  return false;
}

int check_game_over(int current_player, int turn) {
  if (turn == 9) {
    return DRAW;
  }

  
  if (is_horizontal_complete() || is_vertical_complete() || is_diagonal_complete()) {
    return PLAYER_WIN;
  }

  return GAME_IS_NOT_OVER;
}

void clear_screen() {
  printf("\033[H\033[J");
}

void draw_line(char a, char b, char c) {
  printf(" %c | %c | %c \n", a, b, c);
}

void draw_empty_line() {
  draw_line(' ', ' ', ' ');
}

void draw_connect_line() {
  printf("---+---+---\n");
}

void draw_board() {
  printf("\n");
    
  for(int i = 0; i < 3; i++) {
    draw_empty_line();
    draw_line(board_values[i][0], board_values[i][1], board_values[i][2]);
    draw_empty_line();
    if (i < 2)
     draw_connect_line();
  }
}

void reset_color() {
  printf("\033[0m");
}

void red() {
  printf("\033[1;31m");
}

void green() {
  printf("\033[0;32m");
}

void yellow() {
  printf("\033[1;33m");
}
