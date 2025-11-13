// src/game.h
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "contracts.h"

typedef struct {
    Contract c;          // contrat du niveau

    int remainS;
    int remainF;
    int remainP;
    int remainO;
    int remainM;

    int movesLeft;
    int secondsLeft;
    int lives;
    int levelIndex;

    Board board;         // plateau de jeu
} GameState;

int game_init(GameState* g, const char* player, int levelIndex);
int game_play_level(GameState* g, unsigned* rng);

#endif
