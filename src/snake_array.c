#include <stdio.h>
#include <raylib.h>
#include "snake.h"

#define SNAKE_MAX 100
#define SQUARE_SIZE 20

typedef struct {
    Position body[SNAKE_MAX];
    int length;
} SnakeArray;

void move_snake_array(void *snake) {
    SnakeArray *s = (SnakeArray *)snake;
    for (int i = s->length - 1; i > 0; i--) {
        s->body[i] = s->body[i - 1];
    }
}

void grow_snake_array(void *snake) {
    SnakeArray *s = (SnakeArray *)snake;
    if (s->length < SNAKE_MAX) {
        s->body[s->length] = s->body[s->length - 1];
        s->length++;
    }
}

bool check_collision_array(void *snake) {
    SnakeArray *s = (SnakeArray *)snake;
    for (int i = 1; i < s->length; i++) {
        if (s->body[0].x == s->body[i].x && s->body[0].y == s->body[i].y) {
            return true;
        }
    }
    return false;
}

void print_snake_array(void *snake) {
    SnakeArray *s = (SnakeArray *)snake;
    for (int i = 0; i < s->length; i++) {
        DrawRectangle(s->body[i].x, s->body[i].y, SQUARE_SIZE, SQUARE_SIZE, GREEN);
    }
}
