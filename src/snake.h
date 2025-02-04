#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

typedef struct {
    int x, y;
} Position;

typedef struct {
    void (*move)(void *);
    void (*grow)(void *);
    bool (*check_collision)(void *);
    void (*print)(void *);
} SnakeInterface;

#endif
