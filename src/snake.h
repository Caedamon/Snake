#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 20

typedef struct {
    int x, y;
} Position;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    void (*move)(void *, Direction);
    void (*grow)(void *);
    bool (*check_collision)(void *);
    void (*print)(void *);
} SnakeInterface;

typedef struct {
    Position body[100];
    int length;
} SnakeArray;

typedef struct SnakeNode {
    Position pos;
    struct SnakeNode *next;
} SnakeNode;

typedef struct {
    SnakeNode *head;
    int grow;
} SnakeLinkedList;

void free_snake_linked(SnakeLinkedList *snake);

#endif
