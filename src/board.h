/**
 * @file board.h
 * @brief Board representation and manipulation
 */
#ifndef BOARD_H
#define BOARD_H

#define ROWS 25
#define COLS 45

typedef enum {
    IT_S = 'S', /* Soleil */
    IT_F = 'F', /* Fraise */
    IT_P = 'P', /* Pomme */
    IT_O = 'O', /* Oignon */
    IT_M = 'M'  /* Mandarine */
} Item;

typedef struct {
    Item cells[ROWS][COLS];
} Board;

/**
 * @brief Fill board with random items
 * @param b [OUT] Board to fill
 * @param rng [IN/OUT] RNG state
 */
void board_fill_random(Board* b, unsigned* rng);

/**
 * @brief Draw the board to console
 * @param b [IN] Board to draw
 * @param cursorRow [IN] Current cursor row (-1 if none)
 * @param cursorCol [IN] Current cursor column
 * @param selRow [IN] Selected cell row (-1 if none)
 * @param selCol [IN] Selected cell column
 */
void board_draw(const Board* b, int cursorRow, int cursorCol, int selRow, int selCol);

/**
 * @brief Draw UI info (contract, moves, time, lives)
 * @param movesLeft [IN] Moves remaining
 * @param lives [IN] Lives remaining
 * @param secondsLeft [IN] Seconds remaining
 * @param remainS [IN] S items needed
 * @param remainF [IN] F items needed
 * @param remainP [IN] P items needed
 * @param remainO [IN] O items needed
 * @param remainM [IN] M items needed
 */
void board_draw_ui(int movesLeft, int lives, int secondsLeft,
                   int remainS, int remainF, int remainP, int remainO, int remainM);

/**
 * @brief Apply gravity (make items fall down)
 * @param b [IN/OUT] Board to apply gravity to
 */
void board_apply_gravity(Board* b);

/**
 * @brief Refill empty cells (0) with random items from top
 * @param b [IN/OUT] Board to refill
 * @param rng [IN/OUT] RNG state
 */
void board_refill(Board* b, unsigned* rng);

/**
 * @brief Copy board
 * @param src [IN] Source board
 * @param dst [OUT] Destination board
 */
void board_copy(const Board* src, Board* dst);

/**
 * @brief Check if board is stable (no matches >= 3)
 * @param b [IN] Board to check
 * @return 1 if stable, 0 otherwise
 */
int board_is_stable(const Board* b);

/**
 * @brief Generate a stable board (no initial matches)
 * @param b [OUT] Board to generate
 * @param rng [IN/OUT] RNG state
 * @param maxTries [IN] Maximum attempts
 * @return 1 if success, 0 if failed after maxTries
 */
int board_generate_stable(Board* b, unsigned* rng, int maxTries);

/**
 * @brief Swap two adjacent cells
 * @param b [IN/OUT] Board
 * @param r1 [IN] Row of first cell
 * @param c1 [IN] Column of first cell
 * @param r2 [IN] Row of second cell
 * @param c2 [IN] Column of second cell
 */
void board_swap(Board* b, int r1, int c1, int r2, int c2);

#endif /* BOARD_H */
