#include <stdio.h>
#include <raylib.h>
#include "snake.h"

#define SNAKE_MAX 100

typedef struct {
    Position body[SNAKE_MAX];
    int length;
} SnakeArray;

void move_snake_array(void *snake, Direction dir) {
    SnakeArray *s = (SnakeArray *)snake;

    // Shift body segments
    for (int i = s->length - 1; i > 0; i--) {
        s->body[i] = s->body[i - 1];
    }

    // Update head position based on direction
    switch (dir) {
        case UP:
            s->body[0].y -= SQUARE_SIZE;
        break;
        case DOWN:
            s->body[0].y += SQUARE_SIZE;
        break;
        case LEFT:
            s->body[0].x -= SQUARE_SIZE;
        break;
        case RIGHT:
            s->body[0].x += SQUARE_SIZE;
        break;
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

    // Check wall collision
    if (s->body[0].x < 0 || s->body[0].x >= SCREEN_WIDTH ||
        s->body[0].y < 0 || s->body[0].y >= SCREEN_HEIGHT) {
        return true;
        }

    // Check self collision
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
