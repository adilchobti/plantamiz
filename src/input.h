#ifndef INPUT_H
#define INPUT_H

#include "board.h"

// Représente le curseur et la sélection
typedef struct {
    int row, col;         // position du curseur
    int hasSelection;     // 0/1
    int selRow, selCol;   // position de la case sélectionnée
} Cursor;

// Initialise le curseur au centre
void input_init(Cursor* cur);

// Lit une entrée utilisateur non bloquante.
// Retourne 1 si l'utilisateur demande de quitter le niveau (ECHAP), 0 sinon.
// didSwap = 1 si une permutation a été effectuée (après sélection + direction)
int input_poll(Cursor* cur, Board* b, int* didSwap);

#endif
