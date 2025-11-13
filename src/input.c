#include "input.h"
#include "platform.h"
#include <stdio.h>
#include <conio.h>   // _kbhit, _getch

// Petits helpers
static int clamp(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void input_init(Cursor* cur) {
    cur->row = ROWS / 2;
    cur->col = COLS / 2;
    cur->hasSelection = 0;
    cur->selRow = cur->selCol = -1;
}

// Essaie une permutation (r1,c1) <-> (r2,c2) dans les bornes
static int try_swap(Board* b, int r1, int c1, int r2, int c2) {
    if (r2 < 0 || r2 >= ROWS || c2 < 0 || c2 >= COLS) return 0;
    Item tmp = b->cells[r1][c1];
    b->cells[r1][c1] = b->cells[r2][c2];
    b->cells[r2][c2] = tmp;
    return 1;
}

// ZQSD/Flèches + Espace pour sélectionner + Échap pour quitter
int input_poll(Cursor* cur, Board* b, int* didSwap) {
    *didSwap = 0;
    if (!_kbhit()) return 0;

    int ch = _getch();

    // Flèches : Windows envoie d'abord 224 puis un code
    if (ch == 224) {
        int code = _getch();
        switch (code) {
            case 72: // Up
                cur->row = clamp(cur->row - 1, 0, ROWS - 1);
                break;
            case 80: // Down
                cur->row = clamp(cur->row + 1, 0, ROWS - 1);
                break;
            case 75: // Left
                cur->col = clamp(cur->col - 1, 0, COLS - 1);
                break;
            case 77: // Right
                cur->col = clamp(cur->col + 1, 0, COLS - 1);
                break;
        }
        return 0;
    }

    // Échap -> quitter niveau
    if (ch == 27) {
        return 1;
    }

    // Espace -> sélectionner/désélectionner ou swap si direction juste après
    if (ch == ' ') {
        if (!cur->hasSelection) {
            cur->hasSelection = 1;
            cur->selRow = cur->row;
            cur->selCol = cur->col;
        } else {
            // Un second espace désélectionne
            cur->hasSelection = 0;
            cur->selRow = cur->selCol = -1;
        }
        return 0;
    }

    // z q s d (AZERTY) pour bouger / swap rapide si on a une sélection
    if (ch == 'z' || ch == 'Z' || ch == 'w' || ch == 'W') {
        if (cur->hasSelection) {
            *didSwap = try_swap(b, cur->selRow, cur->selCol, cur->selRow - 1, cur->selCol);
            if (*didSwap) { cur->row = cur->selRow - 1; cur->col = cur->selCol; cur->hasSelection = 0; }
        } else {
            cur->row = clamp(cur->row - 1, 0, ROWS - 1);
        }
        return 0;
    }
    if (ch == 's' || ch == 'S') {
        if (cur->hasSelection) {
            *didSwap = try_swap(b, cur->selRow, cur->selCol, cur->selRow + 1, cur->selCol);
            if (*didSwap) { cur->row = cur->selRow + 1; cur->col = cur->selCol; cur->hasSelection = 0; }
        } else {
            cur->row = clamp(cur->row + 1, 0, ROWS - 1);
        }
        return 0;
    }
    if (ch == 'q' || ch == 'Q' || ch == 'a' || ch == 'A') {
        if (cur->hasSelection) {
            *didSwap = try_swap(b, cur->selRow, cur->selCol, cur->selRow, cur->selCol - 1);
            if (*didSwap) { cur->row = cur->selRow; cur->col = cur->selCol - 1; cur->hasSelection = 0; }
        } else {
            cur->col = clamp(cur->col - 1, 0, COLS - 1);
        }
        return 0;
    }
    if (ch == 'd' || ch == 'D') {
        if (cur->hasSelection) {
            *didSwap = try_swap(b, cur->selRow, cur->selCol, cur->selRow, cur->selCol + 1);
            if (*didSwap) { cur->row = cur->selRow; cur->col = cur->selCol + 1; cur->hasSelection = 0; }
        } else {
            cur->col = clamp(cur->col + 1, 0, COLS - 1);
        }
        return 0;
    }

    return 0;
}
