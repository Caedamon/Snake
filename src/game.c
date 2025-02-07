#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "snake.h"

typedef struct {
    Position position;
} Food;

Food food;

void SpawnFood() {
    food.position.x = (rand() % (SCREEN_WIDTH / SQUARE_SIZE)) * SQUARE_SIZE;
    food.position.y = (rand() % (SCREEN_HEIGHT / SQUARE_SIZE)) * SQUARE_SIZE;
}

void run_game(const SnakeInterface *interface, void *snake) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake, With Raylib!");
    SetTargetFPS(60);

    Direction dir = RIGHT;
    SpawnFood();

    float moveTimer = 0.0f;
    float moveDelay = 0.15f; // Adjust this to change snake speed (lower = faster)

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) break;

        // Update movement timer
        moveTimer += GetFrameTime();

        // Direction Input
        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && dir != DOWN) dir = UP;
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && dir != UP) dir = DOWN;
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && dir != RIGHT) dir = LEFT;
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && dir != LEFT) dir = RIGHT;

        // Move only when enough time has passed
        if (moveTimer >= moveDelay) {
            moveTimer = 0.0f;  // Reset timer
            interface->move(snake, dir);
        }

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

            // Increase speed by reducing moveDelay (prevent it from getting too fast)
            moveDelay *= 0.95f;
            if (moveDelay < 0.05f) moveDelay = 0.05f;  // Minimum speed limit
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