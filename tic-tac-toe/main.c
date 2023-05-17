#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define DRAW 0
#define PLAYER_WIN 1
#define GAME_IS_NOT_OVER -1

char board_values[10] = {'1','2','3','4','5','6','7','8','9'};

void draw_board();
void draw_connect_line();
void draw_line(char a, char b, char c);
void draw_empty_line();
void clear_screen();
int check_game_over(int board_index, int current_player, int turn);
bool is_diagonal_complete();
bool is_vertical_complete();
bool is_horizontal_complete();


int main() {
  int current_player = 1;
  int input;
  int turn = 1;
  int game_over = GAME_IS_NOT_OVER;

  printf("Player 1: (x) - Player 2: (o)");
 
  clear_screen();
  draw_board();

  do {
    printf("Player %d turn. Enter a number: ", current_player);
    scanf("%d", &input);
    int board_index = input - 1;  

    if (isdigit(board_values[board_index]) && board_index <= 9) {
      
      board_values[board_index] = current_player == 1 ? 'x' : 'o';
      
      game_over = check_game_over(board_index, current_player, turn); 
    
      turn = turn + 1;

      current_player = (current_player % 2) ? 2 : 1;

      clear_screen();
      draw_board();
    } else {
      clear_screen();
      printf("Invalid move!");
    }

  } while (game_over == GAME_IS_NOT_OVER);
  
  if (game_over == DRAW) {
    printf("Draw!");
  } else {
    printf("Player %d won!", current_player);
  }

  return 0;
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

int check_game_over(int board_index, int current_player, int turn) {
  if (turn == 9) {
    return DRAW;
  }

  // checks if diagonal is complete
  // check vertical
  // check horizontal

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
  draw_empty_line();
  draw_line(board_values[0], board_values[1], board_values[2]);
  draw_empty_line();
  draw_connect_line();
  draw_empty_line();
  draw_line(board_values[3], board_values[4], board_values[5]);
  draw_empty_line();
  draw_connect_line();
  draw_empty_line();
  draw_line(board_values[6], board_values[7], board_values[8]);
  draw_empty_line();
}
