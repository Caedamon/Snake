#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

// Function Declarations
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
    int choice;
    printf("Choose Snake Implementation: 1-Array  2-Linked List\n");
    scanf("%d", &choice);

    SnakeInterface snake_interface;
    void *snake;

    if (choice == 1) {
        static SnakeArray snake_array = {{{5, 5}}, 1};
        snake_interface = (SnakeInterface){move_snake_array, grow_snake_array, check_collision_array, print_snake_array};
        snake = &snake_array;
    } else {
        static SnakeLinkedList snake_linked = {NULL};
        snake_linked.head = malloc(sizeof(SnakeNode));
        snake_linked.head->pos.x = 5;
        snake_linked.head->pos.y = 5;
        snake_linked.head->next = NULL;
        snake_interface = (SnakeInterface){move_snake_linked, grow_snake_linked, check_collision_linked, print_snake_linked};
        snake = &snake_linked;
    }

    run_game(&snake_interface, snake);
    return 0;
}
