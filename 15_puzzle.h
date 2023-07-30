#ifndef PUZZLE_15_H
#define PUZZLE_15_H

#include <string.h>

#define TILE_SIZE 80
#define BOARD_SIZE 4

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int moves;
} PuzzleState;

typedef struct {
    int x;
    int y;
} Position;

PuzzleState createSolvedPuzzle();
void shufflePuzzle(PuzzleState *puzzle);
int isSolved(const PuzzleState *puzzle);
int isValidMove(const PuzzleState *puzzle, int move);
PuzzleState makeMove(const PuzzleState *puzzle, int move);
int manhattanDistance(const PuzzleState *puzzle);
PuzzleState solvePuzzle(const PuzzleState *initialState);

#endif
