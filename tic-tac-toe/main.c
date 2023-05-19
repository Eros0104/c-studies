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
int check_game_over(
int current_player, int turn, struct board_coordinate coordinates
);
bool is_anti_diagonal_complete(struct board_coordinate coordinate, char value);
bool is_diagonal_complete(struct board_coordinate coordinate, char value);
bool is_vertical_complete(int y, char value);
bool is_horizontal_complete(int x, char value);
char get_player_symbol(int current_player);
struct board_coordinate get_board_coordinate(char value);

int main() {
  int current_player = 1;
  char input;
  int turn = 1;
  int game_over = GAME_IS_NOT_OVER;

  clear_screen();
  draw_board();
  
	do {
    printf("Player %d turn. Enter a number: ", current_player);
    // space inserted before "%c" to consume newline from previous run 
    scanf(" %c", &input);

    struct board_coordinate coordinates = get_board_coordinate(input);  
    
    if (coordinates.i != -1 && isdigit(board_values[coordinates.i][coordinates.j])) {
      
      board_values[coordinates.i][coordinates.j] = get_player_symbol(current_player);

			game_over = check_game_over(current_player, turn, coordinates); 
    
      turn = turn + 1;

      if (game_over == GAME_IS_NOT_OVER)
        current_player = (current_player % 2) ? 2 : 1;

      clear_screen();
    	draw_board();
    } else {
      clear_screen();
    	draw_board();
      red();
      printf("Invalid move!\n");
      reset_color();
    }


  } while (game_over == GAME_IS_NOT_OVER); 
  
  if (game_over == DRAW) {
    yellow();
    printf("Draw!");
  } else {
    green();
    printf("Player %d won!\n", current_player);
  }
  
	reset_color();
	printf("Press \"Enter\" to exit...\n");
	fflush(stdin);
	getchar();

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

char get_player_symbol(int current_player) {
	return current_player == 1 ? 'x' : 'o';
}

bool is_anti_diagonal_complete(struct board_coordinate coordinate, char value) {
	int x = coordinate.i;
	int y = coordinate.j;
	int n = 3;
	if(x + y == n - 1){
		for(int i = 0; i < n; i++){
			if(board_values[i][(n - 1) - i] != value)
				break;
      if(i == n - 1){
				return true;
			}
		}
	}
  return false;
}

bool is_diagonal_complete(struct board_coordinate coordinate, char value) {
	int x = coordinate.i;
	int y = coordinate.j;
	if(x == y){
		for(int i = 0; i < 3; i++){
			if(board_values[i][i] != value)
				break;
      if(i == 2){
				return true;
			}
		}
	}
  return false;
}

bool is_vertical_complete(int y, char value) {
	for(int i = 0; i < 3; i++) {
		if(board_values[i][y] != value) {
			break;
		}
    if(i == 2) {
			return true;
		}
	}
	return false;
}

bool is_horizontal_complete(int x, char value) {
	for(int i = 0; i < 3; i++) {
		if(board_values[x][i] != value) {
			break;
		}
		if(i == 2) {
			return true;
		}
	}
	return false;
}

int check_game_over(
  int current_player, int turn, struct board_coordinate coordinate
) {
  if (turn == 9) {
    return DRAW;
  }

	char symbol = get_player_symbol(current_player);

  if (
    is_horizontal_complete(coordinate.i, symbol)
    || is_vertical_complete(coordinate.j, symbol) 
    || is_diagonal_complete(coordinate, symbol)
		|| is_anti_diagonal_complete(coordinate, symbol)
  ) {
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

void draw_board(int i) {
  printf("Player 1: (x) - Player 2: (o)");
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
