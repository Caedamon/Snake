#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake.h"

extern void move_snake_array(void *);
extern void grow_snake_array(void *);
extern bool check_collision_array(void *);
extern void print_snake_array(void *);

extern void move_snake_linked(void *);
extern void grow_snake_linked(void *);
extern bool check_collision_linked(void *);
extern void print_snake_linked(void *);

extern void run_game(SnakeInterface *, void *);

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
} SnakeLinkedList;

int main() {
    char input[10];
    int choice = 0;

    printf("Choose Snake Implementation: 1-Array  2-Linked List\n");
    fgets(input, sizeof(input), stdin);

    char *endptr;
    choice = strtol(input, &endptr, 10);

    // Check for conversion errors
    if (endptr == input || *endptr != '\n') {
        printf("Invalid input! Please enter 1 or 2.\n");
        return 1;  // Exit if invalid input
    }

    SnakeInterface snake_interface;
    void *snake;

    if (choice == 1) {
        static SnakeArray snake_array = {{{5, 5}}, 1};
        snake_interface = (SnakeInterface){move_snake_array, grow_snake_array, check_collision_array, print_snake_array};
        snake = &snake_array;
    } else if (choice == 2) {
        static SnakeLinkedList snake_linked = {NULL};
        snake_linked.head = malloc(sizeof(SnakeNode));
        snake_linked.head->pos.x = 5;
        snake_linked.head->pos.y = 5;
        snake_linked.head->next = NULL;
        snake_interface = (SnakeInterface){move_snake_linked, grow_snake_linked, check_collision_linked, print_snake_linked};
        snake = &snake_linked;
    } else {
        printf("Invalid choice! Please enter 1 or 2.\n");
        return 1;
    }

    run_game(&snake_interface, snake);
    return 0;
}
