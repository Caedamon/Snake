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

int main() {
    char input[10];
    int choice = 0;

    while (1) {
        printf("Choose Snake Implementation: 1-Array  2-Linked List\n");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Please enter a valid input\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        char *endptr;
        choice = strtol(input, &endptr, 10);

        if (endptr == input || *endptr != '\0' || (choice != 1 && choice != 2)) {
            printf("Please enter a valid input\n");
        } else {
            break;
        }
    }


    SnakeInterface snake_interface;
    void *snake;

    if (choice == 1) {
        static SnakeArray snake_array = {{{5, 5}}, 1};
        snake_interface = (SnakeInterface){move_snake_array, grow_snake_array, check_collision_array, print_snake_array};
        snake = &snake_array;
    } else if (choice == 2) {
        static SnakeLinkedList snake_linked = {NULL, 0};
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

    // Free the linkedlist memory after game to prevent memory leaks
    if (choice == 2) {
        free_snake_linked((SnakeLinkedList *)snake);
    }
    return 0;
}
