/**
 * @file test_match.c
 * @brief Unit tests for match detection
 */
#include "../src/board.h"
#include "../src/match.h"
#include <stdio.h>
#include <string.h>

static void setup_test_board(Board* b, const char* pattern) {
    memset(b, 0, sizeof(Board));
    /* Simple pattern: first 5 chars map to first row */
    for (int i = 0; i < 5 && pattern[i]; i++) {
        b->cells[0][i] = (Item)pattern[i];
    }
}

int main(void) {
    printf("Testing match detection...\n");

    Board board;
    MatchList ml;

    /* Test horizontal line of 3 */
    setup_test_board(&board, "SSSFF");
    int found = match_find(&board, &ml);

    if (found < 1) {
        printf("FAIL: Did not detect horizontal line of 3\n");
        return 1;
    }
    printf("PASS: Detected horizontal line of 3\n");

    /* Test horizontal line of 4 */
    setup_test_board(&board, "SSSSF");
    found = match_find(&board, &ml);

    if (found < 1) {
        printf("FAIL: Did not detect horizontal line of 4\n");
        return 1;
    }

    int hasLine4 = 0;
    for (int i = 0; i < ml.count; i++) {
        if (ml.list[i].type == MT_LINE4) {
            hasLine4 = 1;
            break;
        }
    }

    if (!hasLine4) {
        printf("FAIL: Line of 4 not detected as MT_LINE4\n");
        return 1;
    }
    printf("PASS: Detected horizontal line of 4\n");

    /* Test vertical line */
    memset(&board, 0, sizeof(Board));
    board.cells[0][0] = IT_S;
    board.cells[1][0] = IT_S;
    board.cells[2][0] = IT_S;

    found = match_find(&board, &ml);

    if (found < 1) {
        printf("FAIL: Did not detect vertical line of 3\n");
        return 1;
    }
    printf("PASS: Detected vertical line of 3\n");

    /* Test match_apply */
    setup_test_board(&board, "SSSFF");
    found = match_find(&board, &ml);

    int remainS = 10, remainF = 10, remainP = 10, remainO = 10, remainM = 10;
    int gainedPts = 0;

    match_apply(&board, &ml, &remainS, &remainF, &remainP, &remainO, &remainM, &gainedPts);

    if (board.cells[0][0] != 0 || board.cells[0][1] != 0 || board.cells[0][2] != 0) {
        printf("FAIL: match_apply did not remove matched items\n");
        return 1;
    }

    if (remainS != 7) {
        printf("FAIL: Contract not updated correctly (expected remainS=7, got %d)\n", remainS);
        return 1;
    }

    printf("PASS: match_apply removes items and updates contract\n");

    printf("\nAll match tests passed!\n");
    return 0;
}
