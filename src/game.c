// src/game.c
#include <time.h>
#include "game.h"
#include "board.h"
#include "input.h"
#include "match.h"
#include "platform.h"
#include "utils.h"

static void init_remaining_from_contract(GameState* g) {
    g->remainS = g->c.targetS;
    g->remainF = g->c.targetF;
    g->remainP = g->c.targetP;
    g->remainO = g->c.targetO;
    g->remainM = g->c.targetM;
}
 
int game_init(GameState* g, const char* player, int levelIndex) {
    (void)player; // pas utilisé pour le moment

    if (levelIndex < 0 || levelIndex >= NUM_LEVELS) {
        return 0;
    }

    g->levelIndex = levelIndex;
    g->c = contracts_get(levelIndex);

    g->movesLeft   = g->c.movesMax > 0 ? g->c.movesMax : 30;
    g->secondsLeft = g->c.seconds  > 0 ? g->c.seconds  : 120;

    init_remaining_from_contract(g);

    unsigned seed = (unsigned)time(NULL);
    if (!board_generate_stable(&g->board, &seed, 5000)) {
        return 0;
    }

    return 1;
}

int game_play_level(GameState* g, unsigned* rng) {
    Cursor cur;
    input_init(&cur);

    int lastSecondTick = plt_now_ms();

    while (1) {
        utils_clear_screen();

        board_draw(&g->board,
                   cur.row,
                   cur.col,
                   cur.hasSelection ? cur.selRow : -1,
                   cur.hasSelection ? cur.selCol : -1);

        board_draw_ui(g->movesLeft, g->lives, g->secondsLeft,
                      g->remainS, g->remainF, g->remainP,
                      g->remainO, g->remainM);

        // Gestion du timer (1 seconde)
        int now = plt_now_ms();
        if (now - lastSecondTick >= 1000) {
            lastSecondTick += 1000;
            if (g->secondsLeft > 0) {
                g->secondsLeft--;
            }
            if (g->secondsLeft <= 0) {
                return 0; // Temps écoulé -> échec
            }
        }

        int didSwap = 0;
        int quit = input_poll(&cur, &g->board, &didSwap);
        if (quit) {
            return -1; // joueur quitte
        }

        if (didSwap) {
            g->movesLeft--;

            MatchList ml;
            int gainedPts = 0;

            // Cascades
            while (match_find(&g->board, &ml) && ml.count > 0) {
                (void)match_apply(&g->board, &ml,
                                  &g->remainS, &g->remainF, &g->remainP,
                                  &g->remainO, &g->remainM, &gainedPts);

                board_apply_gravity(&g->board);
                board_refill(&g->board, rng);
            }

            // Contrat rempli ?
            if (g->remainS <= 0 && g->remainF <= 0 &&
                g->remainP <= 0 && g->remainO <= 0 &&
                g->remainM <= 0) {
                return 1; // victoire
            }

            // Plus de coups ?
            if (g->movesLeft <= 0) {
                return 0; // échec
            }
        }
    }
}
