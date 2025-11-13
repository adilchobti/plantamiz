// src/match.h
#ifndef MATCH_H
#define MATCH_H

#include "board.h"

typedef enum {
    MT_LINE3,
    MT_LINE4,
    MT_LINE6,
    MT_H,
    MT_RECT
} MatchType;

typedef struct {
    int r;
    int c;
} Pos;

typedef struct {
    MatchType type;
    Item it;
    Pos pos[ROWS * COLS];
    int count;
    int w;
    int h;
} Match;

typedef struct {
    Match list[256];
    int count;
} MatchList;

int match_find(const Board *b, MatchList *out);

int match_apply(Board *b, const MatchList *ml,
                int *remainS, int *remainF, int *remainP,
                int *remainO, int *remainM, int *gainedPts);

#endif
