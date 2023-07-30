#include "15_puzzle.h"
#include <stdlib.h>

#define TILE_SIZE 80

Position findEmptyTile(const PuzzleState *puzzle) {
    Position emptyPos = { -1, -1 };
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] == 0) {
                emptyPos.x = j;
                emptyPos.y = i;
                break;
            }
        }
    }
    return emptyPos;
}

PuzzleState createSolvedPuzzle() {
    PuzzleState puzzle;
    int counter = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            puzzle.board[i][j] = counter++;
        }
    }
    puzzle.board[BOARD_SIZE - 1][BOARD_SIZE - 1] = 0;
    puzzle.moves = 0;
    return puzzle;
}

void shufflePuzzle(PuzzleState *puzzle) {
    int n = BOARD_SIZE * BOARD_SIZE * 10;
    while (n > 0) {
        int randMove = rand() % 4; // 0: up, 1: down, 2: left, 3: right
        if (isValidMove(puzzle, randMove)) {
            *puzzle = makeMove(puzzle, randMove);
            n--;
        }
    }
    puzzle->moves = 0;
}

int isSolved(const PuzzleState *puzzle) {
    int counter = 1;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] != counter++ && (i != BOARD_SIZE - 1 || j != BOARD_SIZE - 1)) {
                return 0;
            }
        }
    }
    return 1;
}

int isValidMove(const PuzzleState *puzzle, int move) {
    Position emptyPos = findEmptyTile(puzzle);
    switch (move) {
    case 0: // Up
        return emptyPos.y < BOARD_SIZE - 1;
    case 1: // Down
        return emptyPos.y > 0;
    case 2: // Left
        return emptyPos.x < BOARD_SIZE - 1;
    case 3: // Right
        return emptyPos.x > 0;
    default:
        return 0;
    }
}

PuzzleState makeMove(const PuzzleState *puzzle, int move) {
    if (!isValidMove(puzzle, move)) {
        return *puzzle;
    }

    Position emptyPos = findEmptyTile(puzzle);
    PuzzleState newPuzzle = *puzzle;
    switch (move) {
    case 0: // Up
        newPuzzle.board[emptyPos.y][emptyPos.x] = puzzle->board[emptyPos.y + 1][emptyPos.x];
        newPuzzle.board[emptyPos.y + 1][emptyPos.x] = 0;
        break;
    case 1: // Down
        newPuzzle.board[emptyPos.y][emptyPos.x] = puzzle->board[emptyPos.y - 1][emptyPos.x];
        newPuzzle.board[emptyPos.y - 1][emptyPos.x] = 0;
        break;
    case 2: // Left
        newPuzzle.board[emptyPos.y][emptyPos.x] = puzzle->board[emptyPos.y][emptyPos.x + 1];
        newPuzzle.board[emptyPos.y][emptyPos.x + 1] = 0;
        break;
    case 3: // Right
        newPuzzle.board[emptyPos.y][emptyPos.x] = puzzle->board[emptyPos.y][emptyPos.x - 1];
        newPuzzle.board[emptyPos.y][emptyPos.x - 1] = 0;
        break;
    }

    newPuzzle.moves++;
    return newPuzzle;
}

int manhattanDistance(const PuzzleState *puzzle) {
    int distance = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int value = puzzle->board[i][j];
            if (value != 0) {
                int targetX = (value - 1) % BOARD_SIZE;
                int targetY = (value - 1) / BOARD_SIZE;
                distance += abs(j - targetX) + abs(i - targetY);
            }
        }
    }
    return distance;
}

typedef struct {
    PuzzleState state;
    int cost;
} Node;

Node createNode(PuzzleState state, int cost) {
    Node node;
    node.state = state;
    node.cost = cost;
    return node;
}

int compareNodes(const void* a, const void* b) {
    const Node* nodeA = (const Node*)a;
    const Node* nodeB = (const Node*)b;
    return (nodeA->cost - nodeB->cost);
}
