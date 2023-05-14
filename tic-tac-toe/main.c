#include <stdio.h>

char board_values[10] = {'1','2','3','4','5','6','7','8','9'};

void draw_board();
void draw_connect_line();
void draw_line(char a, char b, char c);
void draw_empty_line();

void clear_screen() {
  printf("\033[H\033[J");
}

int main() {
  int current_player = 1;
  int input;
  int i = 0;

  clear_screen();
  printf("Player 1: (x) - Player 2: (o)");
 
  do {
    draw_board();
    printf("Player %d turn. Enter a number: ", current_player);
    scanf("%d", &input);
    
    if (current_player == 1) {
      board_values[input - 1] = 'x';
    }

    if (current_player == 2) {
      board_values[input - 1] = 'o';
    }

    current_player = (current_player % 2) ? 2 : 1;
    i = i + 1;
  } while (i < 9);

  return 1;
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
