#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

/* Helper function definitions */
static char get_board_at(game_state_t* state, int x, int y);
static void set_board_at(game_state_t* state, int x, int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static int incr_x(char c);
static int incr_y(char c);
static void find_head(game_state_t* state, int snum);
static char next_square(game_state_t* state, int snum);
static void update_tail(game_state_t* state, int snum);
static void update_head(game_state_t* state, int snum);

/* Helper function to get a character from the board (already implemented for you). */
static char get_board_at(game_state_t* state, int x, int y) {
  return state->board[y][x];
}

/* Helper function to set a character on the board (already implemented for you). */
static void set_board_at(game_state_t* state, int x, int y, char ch) {
  state->board[y][x] = ch;
}

/* Task 1 */
game_state_t* create_default_state() {
    snake_t* snake = (snake_t *)malloc(sizeof(bool) + sizeof(int) * 4);
    snake->head_x = 5;
    snake->head_y = 4;
    snake->tail_x = 4;
    snake->tail_y = 4;
    snake->live = true;
    game_state_t *game_state = (game_state_t *)malloc(sizeof(int) * 5);
    game_state->x_size = 14;
    game_state->y_size = 10;
    char **board = (char **)malloc(sizeof(char *) * game_state->y_size);
    for (int y = 0; y < game_state->y_size; y++) {
        board[y] = (char *)malloc(sizeof(char) * game_state->x_size);
        for (int x = 0; x < game_state->x_size; x++) {
            if (x == 0
                || x == game_state->x_size - 1
                || y == 0
                || y == game_state->y_size - 1) {
                board[y][x] = '#';
                //printf("added '#'");
            } else if (y == snake->tail_y && x == snake->tail_x) {
                board[y][x] = 'd';
            } else if (y == snake->head_y && x == snake->head_x) {
                board[y][x] = '>';
            } else if (y == 2 && x == 9) {
                board[y][x] = '*';
            } else {
                //printf("added ' '");
                board[y][x] = ' ';
            }
        }
    };
    game_state->board = board;
    game_state->num_snakes = 1;
    game_state->snakes = snake;
  return game_state;
}

/* Task 2 */
void free_state(game_state_t* state) {
    
    return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  return;
}

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c) {
  // TODO: Implement this function.
  return true;
}

static bool is_snake(char c) {
  // TODO: Implement this function.
  return true;
}

static char body_to_tail(char c) {
  // TODO: Implement this function.
  return '?';
}

static int incr_x(char c) {
  // TODO: Implement this function.
  return 0;
}

static int incr_y(char c) {
  // TODO: Implement this function.
  return 0;
}

/* Task 4.2 */
static char next_square(game_state_t* state, int snum) {
  // TODO: Implement this function.
  return '?';
}

/* Task 4.3 */
static void update_head(game_state_t* state, int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 4.4 */
static void update_tail(game_state_t* state, int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  return NULL;
}

/* Task 6.1 */
static void find_head(game_state_t* state, int snum) {
  // TODO: Implement this function.
  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  return NULL;
}
