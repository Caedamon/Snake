#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "snake.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 20

typedef struct {
    Position position;
} Food;

Food food;

void SpawnFood() {
    food.position.x = (rand() % (SCREEN_WIDTH / SQUARE_SIZE)) * SQUARE_SIZE;
    food.position.y = (rand() % (SCREEN_HEIGHT / SQUARE_SIZE)) * SQUARE_SIZE;
}

void run_game(SnakeInterface *interface, void *snake) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake, With Raylib!");
    SetTargetFPS(60);

    Direction dir = RIGHT;
    SpawnFood();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) break;

        // Direction Input
        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && dir != DOWN) dir = UP;
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && dir != UP) dir = DOWN;
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && dir != RIGHT) dir = LEFT;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && dir != LEFT) dir = RIGHT;

        interface->move(snake, dir);

        // Food Collision
        Position *snake_head;
        if (((SnakeArray *)snake)->length > 0) {
            snake_head = &((SnakeArray *)snake)->body[0];
        } else {
            snake_head = &((SnakeLinkedList *)snake)->head->pos;
        }

        if (snake_head->x == food.position.x && snake_head->y == food.position.y) {
            interface->grow(snake);
            SpawnFood();
        }

        if (interface->check_collision(snake)) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Game Over! Press R to Restart.", 200, 300, 20, RED);
            EndDrawing();

            if (IsKeyPressed(KEY_R)) return;
            continue;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw Snake
        interface->print(snake);

        // Draw Food
        DrawRectangle(food.position.x, food.position.y, SQUARE_SIZE, SQUARE_SIZE, RED);

        EndDrawing();
    }

    CloseWindow();
}