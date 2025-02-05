#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "snake.h"

#define SQUARE_SIZE 20
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void move_snake_linked(void *snake, Direction dir) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;

    // Create a new head node
    SnakeNode *new_head = malloc(sizeof(SnakeNode));
    new_head->pos = s->head->pos;

    // Update head position based on direction
    switch (dir) {
        case UP:
            new_head->pos.y -= SQUARE_SIZE;
            break;
        case DOWN:
            new_head->pos.y += SQUARE_SIZE;
            break;
        case LEFT:
            new_head->pos.x -= SQUARE_SIZE;
            break;
        case RIGHT:
            new_head->pos.x += SQUARE_SIZE;
            break;
    }

    new_head->next = s->head;
    s->head = new_head;

    // Remove the tail to maintain length
    if (s->grow) {
        s->head = new_head;
    } else {
        SnakeNode *current = s->head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
}

void grow_snake_linked(void *snake) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;
    s->grow = 1;
}

bool check_collision_linked(void *snake) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;
    SnakeNode *head = s->head;

    // Check wall collision
    if (head->pos.x < 0 || head->pos.x >= SCREEN_WIDTH ||
        head->pos.y < 0 || head->pos.y >= SCREEN_HEIGHT) {
        return true;
    }

    // Check self collision
    SnakeNode *temp = head->next;
    while (temp) {
        if (head->pos.x == temp->pos.x && head->pos.y == temp->pos.y) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void free_snake_linked(SnakeLinkedList *snake) {
    SnakeNode *current = snake->head;
    while (current != NULL) {
        SnakeNode *temp = current;
        current = current->next;
        free(temp);
    }
    snake->head = NULL;
}

void print_snake_linked(void *snake) {
    SnakeLinkedList *s = (SnakeLinkedList *)snake;
    SnakeNode *current = s->head;

    while (current != NULL) {
        Rectangle bodySegment = {current->pos.x, current->pos.y, SQUARE_SIZE, SQUARE_SIZE};
        DrawRectangleRounded(bodySegment, 0.4f, 12, GREEN);  // Tubular appearance
        current = current->next;
    }
}
