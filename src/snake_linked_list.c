#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "snake.h"

#define SQUARE_SIZE 20

typedef struct SnakeNode {
    Position pos;
    struct SnakeNode *next;
} SnakeNode;

typedef struct {
    SnakeNode *head;
} SnakeLinkedList;

void move_snake_linked(void *snake) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;
    SnakeNode *new_head = malloc(sizeof(SnakeNode));
    new_head->pos.x = s->head->pos.x + SQUARE_SIZE;
    new_head->pos.y = s->head->pos.y;
    new_head->next = s->head;
    s->head = new_head;
}

void grow_snake_linked(void *snake) {
    // Growth handled in move
}

bool check_collision_linked(void *snake) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;
    SnakeNode *head = s->head;
    SnakeNode *temp = head->next;
    while (temp) {
        if (head->pos.x == temp->pos.x && head->pos.y == temp->pos.y) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void print_snake_linked(void *snake) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;
    SnakeNode *current = s->head;
    while (current != NULL) {
        DrawRectangle(current->pos.x, current->pos.y, SQUARE_SIZE, SQUARE_SIZE, GREEN);
        current = current->next;
    }
}
