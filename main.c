#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "15_puzzle.h"

#define TILE_SIZE 80
#define BOARD_SIZE 4
#define BOARD_MARGIN 10
#define UI_HEIGHT 60
#define SCREEN_WIDTH (TILE_SIZE * BOARD_SIZE + BOARD_MARGIN * 2)
#define SCREEN_HEIGHT (TILE_SIZE * BOARD_SIZE + UI_HEIGHT + BOARD_MARGIN * 2)

//usefull function for my solver
void printPuzzle(const PuzzleState *puzzle) {
    printf("Current Puzzle State:\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%2d, ", puzzle->board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "15 Puzzle");
    SetTargetFPS(60);

    srand(time(NULL));

    PuzzleState solvedPuzzle = createSolvedPuzzle();

    PuzzleState currentPuzzle = solvedPuzzle;
    shufflePuzzle(&currentPuzzle);

    printPuzzle(&currentPuzzle);

    // Main game loop
    while (!WindowShouldClose()) {
        // Input handling
        if (IsKeyPressed(KEY_R)) {
            currentPuzzle = solvedPuzzle;
            shufflePuzzle(&currentPuzzle);
            printPuzzle(&currentPuzzle);
        } else if (IsKeyPressed(KEY_UP)) {
            currentPuzzle = makeMove(&currentPuzzle, 0); // Move up
        } else if (IsKeyPressed(KEY_DOWN)) {
            currentPuzzle = makeMove(&currentPuzzle, 1); // Move down
        } else if (IsKeyPressed(KEY_LEFT)) {
            currentPuzzle = makeMove(&currentPuzzle, 2); // Move left
        } else if (IsKeyPressed(KEY_RIGHT)) {
            currentPuzzle = makeMove(&currentPuzzle, 3); // Move right
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the puzzle board
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                int value = currentPuzzle.board[i][j];
                Rectangle tileRect = { j * TILE_SIZE + BOARD_MARGIN, i * TILE_SIZE + BOARD_MARGIN, TILE_SIZE, TILE_SIZE };

                // Draw the tiles
                if (value > 0) {
                    DrawRectangleRec(tileRect, DARKGRAY);
                    DrawRectangleLinesEx(tileRect, 4, RAYWHITE);
                    DrawText(TextFormat("%d", value), j * TILE_SIZE + BOARD_MARGIN + TILE_SIZE / 2 - 10, i * TILE_SIZE + BOARD_MARGIN + TILE_SIZE / 2 - 10, 40, WHITE);
                } else {
                    DrawRectangleRec(tileRect, BLACK);
                    DrawRectangleLinesEx(tileRect, 4, DARKGRAY);
                }
            }
        }

        DrawText(TextFormat("Moves: %d", currentPuzzle.moves), BOARD_MARGIN, SCREEN_HEIGHT - UI_HEIGHT + 10, 20, WHITE);

        if (isSolved(&currentPuzzle)) {
            DrawText("Congratulations! Puzzle Solved!", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
