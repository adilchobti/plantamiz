// src/match.c
#include "match.h"
#include <string.h>

static void add_cell(Match* m, int r, int c) {
    m->pos[m->count].r = r;
    m->pos[m->count].c = c;
    m->count++;
}

static void add_line_match(MatchList* out, Item it, Pos* cells, int count) {
    if (count < 3 || out->count >= 256) return;

    Match* m = &out->list[out->count++];
    m->it = it;
    m->count = 0;
    m->w = count;
    m->h = 1;

    if (count >= 6) m->type = MT_LINE6;
    else if (count == 4) m->type = MT_LINE4;
    else m->type = MT_LINE3;

    for (int i = 0; i < count; ++i) {
        add_cell(m, cells[i].r, cells[i].c);
    }
}

int match_find(const Board* b, MatchList* out) {
    out->count = 0;

    // Horizontal
    for (int r = 0; r < ROWS; ++r) {
        Item current = 0;
        Pos cells[COLS];
        int len = 0;

        for (int c = 0; c <= COLS; ++c) {
            Item it = (c < COLS) ? b->cells[r][c] : 0;

            if (it != 0 && it == current) {
                cells[len].r = r;
                cells[len].c = c;
                len++;
            } else {
                if (current != 0 && len >= 3) {
                    add_line_match(out, current, cells, len);
                }
                if (it != 0) {
                    current = it;
                    len = 1;
                    cells[0].r = r;
                    cells[0].c = c;
                } else {
                    current = 0;
                    len = 0;
                }
            }
        }
    }

    // Vertical
    for (int c = 0; c < COLS; ++c) {
        Item current = 0;
        Pos cells[ROWS];
        int len = 0;

        for (int r = 0; r <= ROWS; ++r) {
            Item it = (r < ROWS) ? b->cells[r][c] : 0;

            if (it != 0 && it == current) {
                cells[len].r = r;
                cells[len].c = c;
                len++;
            } else {
                if (current != 0 && len >= 3) {
                    add_line_match(out, current, cells, len);
                }
                if (it != 0) {
                    current = it;
                    len = 1;
                    cells[0].r = r;
                    cells[0].c = c;
                } else {
                    current = 0;
                    len = 0;
                }
            }
        }
    }

    return out->count > 0;
}

static void update_remaining_for_item(Item it,
                                      int* remainS, int* remainF, int* remainP,
                                      int* remainO, int* remainM) {
    switch (it) {
        case 'S': if (*remainS > 0) (*remainS)--; break;
        case 'F': if (*remainF > 0) (*remainF)--; break;
        case 'P': if (*remainP > 0) (*remainP)--; break;
        case 'O': if (*remainO > 0) (*remainO)--; break;
        case 'M': if (*remainM > 0) (*remainM)--; break;
        default: break;
    }
}

int match_apply(Board* b, const MatchList* ml,
                int* remainS, int* remainF, int* remainP,
                int* remainO, int* remainM, int* gainedPts) {
    int mark[ROWS][COLS] = {0};
    *gainedPts = 0;

    // Marquage des cases à supprimer
    for (int i = 0; i < ml->count; ++i) {
        const Match* m = &ml->list[i];
        for (int k = 0; k < m->count; ++k) {
            int r = m->pos[k].r;
            int c = m->pos[k].c;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                mark[r][c] = 1;
            }
        }
    }

    int totalDeleted = 0;

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (mark[r][c] && b->cells[r][c] != 0) {
                Item it = b->cells[r][c];
                // MAJ du contrat
                update_remaining_for_item(it, remainS, remainF, remainP,
                                          remainO, remainM);
                // Suppression
                b->cells[r][c] = 0;
                totalDeleted++;
            }
        }
    }

    // Pour l'instant, on ne calcule pas un score compliqué
    *gainedPts = totalDeleted;
    return totalDeleted;
}
