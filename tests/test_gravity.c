/**
 * @file test_gravity.c
 * @brief Unit tests for gravity and refill
 */
#include "../src/board.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    printf("Testing gravity and refill...\n");

    Board board;
    memset(&board, 0, sizeof(Board));

    /* Create column with holes */
    board.cells[0][0] = IT_S;
    board.cells[1][0] = 0;
    board.cells[2][0] = IT_F;
    board.cells[3][0] = 0;
    board.cells[4][0] = IT_P;

    board_apply_gravity(&board);

    /* Items should fall to bottom */
    if (board.cells[ROWS-1][0] != IT_P ||
        board.cells[ROWS-2][0] != IT_F ||
        board.cells[ROWS-3][0] != IT_S) {
        printf("FAIL: Gravity did not work correctly\n");
        printf("Expected bottom-up: P, F, S\n");
        printf("Got: %c, %c, %c\n",
               (char)board.cells[ROWS-1][0],
               (char)board.cells[ROWS-2][0],
               (char)board.cells[ROWS-3][0]);
        return 1;
    }

    /* Top should be empty */
    for (int r = 0; r < ROWS - 3; r++) {
        if (board.cells[r][0] != 0) {
            printf("FAIL: Top cells should be empty after gravity\n");
            return 1;
        }
    }

    printf("PASS: Gravity works correctly\n");

    /* Test refill */
    unsigned rng = 54321;
    board_refill(&board, &rng);

    int emptyCount = 0;
    for (int r = 0; r < ROWS; r++) {
        if (board.cells[r][0] == 0) {
            emptyCount++;
        }
    }

    if (emptyCount > 0) {
        printf("FAIL: Refill left %d empty cells\n", emptyCount);
        return 1;
    }

    printf("PASS: Refill fills all empty cells\n");

    printf("\nAll gravity tests passed!\n");
    return 0;
}
