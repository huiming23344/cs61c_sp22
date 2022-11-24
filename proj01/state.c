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
    free(state->snakes);
    for (int i = 0; i < state->y_size; i++) {
        free(state->board[i]);
    }
    free(state);
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
    char **board_row = state->board;
    for (size_t i = 0; i < state->y_size; i++) {
        fprintf(fp, "%s\n", board_row[i]);
    }
  }

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c) {
    if (c == 'w' || c == 'a' || c == 's' || c == 'd') {
        return true;
    }
  return false;
}

static bool is_snake(char c) {
    if (is_tail(c)) {
        return true;
    }
    if (c == '^' || c == '<' || c == '>' || c == 'v' || c == 'x') {
        return true;
    }
  return false;
}

static char body_to_tail(char c) {
    if (c == '^') return 'w';
    if (c == '<') return 'a';
    if (c == '>') return 'd';
    if (c == 'v') return 's';
  return '?';
}

static int incr_x(char c) {
    if (c == '>' || c == 'd') {
        return 1;
    } else if (c == '<' || c == 'a') {
        return -1;
    }
  return 0;
}

static int incr_y(char c) {
    if (c == 'v' || c == 's') {
        return 1;
    } else if (c == '^' || c == 'w') {
        return -1;
    }
  return 0;
}

/* Task 4.2 */
static char next_square(game_state_t* state, int snum) {
    if (snum >= state->num_snakes) return '?';
    char head = get_board_at(state, state->snakes[snum].head_x, state->snakes[snum].head_y);
    int x = state->snakes[snum].head_x + incr_x(head);
    int y = state->snakes[snum].head_y + incr_y(head);
    return get_board_at(state, x, y);
}

/* Task 4.3 */
static void update_head(game_state_t* state, int snum) {
    char head = get_board_at(state, state->snakes[snum].head_x, state->snakes[snum].head_y);
    int x = state->snakes[snum].head_x + incr_x(head);
    int y = state->snakes[snum].head_y + incr_y(head);
    set_board_at(state, x, y, head);
    state->snakes[snum].head_x = x;
    state->snakes[snum].head_y = y;
}

/* Task 4.4 */
static void update_tail(game_state_t* state, int snum) {
    char tail = get_board_at(state, state->snakes[snum].tail_x, state->snakes[snum].tail_y);
    int x = state->snakes[snum].tail_x + incr_x(tail);
    int y = state->snakes[snum].tail_y + incr_y(tail);
    set_board_at(state, x, y, body_to_tail(get_board_at(state, x, y)));
    set_board_at(state, state->snakes[snum].tail_x, state->snakes[snum].tail_y, ' ');
    state->snakes[snum].tail_x = x;
    state->snakes[snum].tail_y = y;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
    int snake_num = state->num_snakes;
    for (size_t i = 0; i < snake_num; i++) {
        char next_sq = next_square(state, i);
        if (next_sq == '#' || is_snake(next_sq)) {
            state->snakes[i].live = false;
            set_board_at(state, state->snakes[i].head_x, state->snakes[i].head_y, 'x');
        } else if (next_sq == '*') {
            update_head(state, i);
            add_food(state);
        } else {
            update_head(state, i);
            update_tail(state, i);
        }
    };
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
