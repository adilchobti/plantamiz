/**
 * @file test_board.c
 * @brief Unit tests for board generation and stability
 */
#include "../src/board.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Testing board_generate_stable...\n");

    unsigned rng = 12345;
    Board board;
    int success = 0;

    /* Test 10 stable board generations */
    for (int i = 0; i < 10; i++) {
        if (board_generate_stable(&board, &rng, 1000)) {
            if (board_is_stable(&board)) {
                success++;
            } else {
                printf("FAIL: Generated board is not stable on attempt %d\n", i + 1);
                return 1;
            }
        } else {
            printf("FAIL: Could not generate stable board on attempt %d\n", i + 1);
            return 1;
        }
    }

    printf("PASS: Generated %d stable boards successfully\n", success);

    /* Test board_swap */
    board_fill_random(&board, &rng);
    Item before1 = board.cells[0][0];
    Item before2 = board.cells[0][1];

    board_swap(&board, 0, 0, 0, 1);

    if (board.cells[0][0] != before2 || board.cells[0][1] != before1) {
        printf("FAIL: board_swap did not swap correctly\n");
        return 1;
    }

    printf("PASS: board_swap works correctly\n");

    printf("\nAll board tests passed!\n");
    return 0;
}
