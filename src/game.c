#include <stdio.h>
#include <raylib.h>
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

    SpawnFood();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) break;

        if (IsKeyPressed(KEY_UP)) ((SnakeArray *)snake)->body[0].y -= SQUARE_SIZE;
        if (IsKeyPressed(KEY_DOWN)) ((SnakeArray *)snake)->body[0].y += SQUARE_SIZE;
        if (IsKeyPressed(KEY_LEFT)) ((SnakeArray *)snake)->body[0].x -= SQUARE_SIZE;
        if (IsKeyPressed(KEY_RIGHT)) ((SnakeArray *)snake)->body[0].x += SQUARE_SIZE;

        interface->move(snake);

        if (interface->check_collision(snake)) {
            DrawText("Game Over! Press R to restart.", 200, 300, 20, RED);
            if (IsKeyPressed(KEY_R)) return;
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
