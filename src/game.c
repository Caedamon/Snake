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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game with raylib");
    SetTargetFPS(10);

    Direction dir = RIGHT;
    SpawnFood();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) break;

        // Handle direction input
        if (IsKeyPressed(KEY_UP) && dir != DOWN) dir = UP;
        if (IsKeyPressed(KEY_DOWN) && dir != UP) dir = DOWN;
        if (IsKeyPressed(KEY_LEFT) && dir != RIGHT) dir = LEFT;
        if (IsKeyPressed(KEY_RIGHT) && dir != LEFT) dir = RIGHT;

        interface->move(snake, dir);

        if (interface->check_collision(snake)) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Game Over! Press R to restart.", 200, 300, 20, RED);
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