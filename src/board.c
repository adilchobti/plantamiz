// board.c — Windows-only implementation for Plantamitz
// Remplacer entièrement votre fichier par ce contenu.

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "board.h"

// ======================
// Réglages d'affichage
// ======================
#define BOARD_TOP   4   // ligne console où commence la grille
#define BOARD_LEFT  2   // colonne console où commence la grille

// Couleurs console (0..15) – mapping simple
// 0: Noir, 1: Bleu, 2: Vert, 3: Turquoise, 4: Rouge, 5: Violet,
// 6: Jaune sale, 7: Gris clair, 8: Gris foncé, 9: Bleu vif,
// 10: Vert vif, 11: Turquoise vif, 12: Rouge vif, 13: Magenta vif,
// 14: Jaune, 15: Blanc

// ======================
// Helpers Windows
// ======================
static void goto_rc(int r, int c) {
    COORD pos;
    pos.X = (SHORT)c;
    pos.Y = (SHORT)r;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

static void set_color(int fg, int bg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (WORD)(bg * 16 + fg));
}

static void reset_color(void) {
    set_color(15, 0); // blanc sur fond noir
}

// ======================
// RNG local (LCG simple)
// ======================
static unsigned lcg_next(unsigned *state) {
    // Paramètres LCG classiques (Numerical Recipes)
    *state = (*state) * 1664525u + 1013904223u;
    return *state;
}

static int rnd_range(unsigned *state, int maxExclusive) {
    // retourne un entier dans [0, maxExclusive)
    return (int)(lcg_next(state) % (unsigned)maxExclusive);
}

// ======================
// Mapping Items / Couleurs
// ======================
static int color_for_item(Item it) {
    switch (it) {
        case IT_S: return 14; // S (Soleil) : jaune
        case IT_F: return 12; // F (Fraise) : rouge
        case IT_P: return 10; // P (Pomme) : vert
        case IT_O: return 13; // O (Oignon) : violet/magenta
        case IT_M: return 9;  // M (Mandarine) : bleu (au choix)
        default:   return 7;  // vide/autre : gris
    }
}

static char char_for_item(Item it, int lowercase) {
    if (it == 0) return ' '; // vide
    char ch = (char)it;
    if (lowercase && ch >= 'A' && ch <= 'Z') {
        ch = (char)(ch - 'A' + 'a');
    }
    return ch;
}

// ======================
// API publique (board.h)
// ======================

void board_fill_random(Board* b, unsigned* rng) {
    static const Item choices[5] = { IT_S, IT_F, IT_P, IT_O, IT_M };
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            b->cells[r][c] = choices[rnd_range(rng, 5)];
        }
    }
}

// Dessine la grille à l’écran.
// curRow/curCol : position du curseur joueur (–1 si pas utilisé)
// selRow/selCol : case sélectionnée (minuscule) (–1 si pas de sélection)
void board_draw(const Board* b, int curRow, int curCol, int selRow, int selCol) {
    // Cadre haut (ligne de séparation)
    reset_color();
    goto_rc(BOARD_TOP - 1, BOARD_LEFT);
    for (int i = 0; i < COLS; ++i) putchar('-');

    for (int r = 0; r < ROWS; ++r) {
        goto_rc(BOARD_TOP + r, BOARD_LEFT);
        for (int c = 0; c < COLS; ++c) {
            const Item it = b->cells[r][c];

            int isCursor = (r == curRow && c == curCol);
            int isSel    = (r == selRow && c == selCol);

            int fg = color_for_item(it);
            int bg = isCursor ? 7 : 0; // gris clair en fond si curseur, sinon fond noir

            set_color(fg, bg);
            // Minuscule si sélectionnée (CDC suggéré)
            char ch = char_for_item(it, isSel ? 1 : 0);
            putchar(ch);
        }
        reset_color();
    }

    // Cadre bas (ligne de séparation)
    goto_rc(BOARD_TOP + ROWS, BOARD_LEFT);
    for (int i = 0; i < COLS; ++i) putchar('-');
    reset_color();
}

// UI bandeau : à afficher au-dessus de la grille
// Les "remainX" sont les quantités restantes à collecter dans le contrat.
void board_draw_ui(
    int movesLeft, int lives, int secondsLeft,
    int remainS, int remainF, int remainP, int remainO, int remainM
) {
    // Lignes 0..2 : UI
    reset_color();

    // Ligne 0 : Contrat
    goto_rc(0, 0);
    set_color(15, 0);
    printf("Contrat restant  | ");
    set_color(color_for_item(IT_S), 0); printf("S:%d ", remainS);
    set_color(color_for_item(IT_F), 0); printf("F:%d ", remainF);
    set_color(color_for_item(IT_P), 0); printf("P:%d ", remainP);
    set_color(color_for_item(IT_O), 0); printf("O:%d ", remainO);
    set_color(color_for_item(IT_M), 0); printf("M:%d ", remainM);
    reset_color();
    printf("  ");

    // Ligne 1 : Moves / Vies / Temps
    goto_rc(1, 0);
    set_color(11, 0); printf("Coups: %d", movesLeft); reset_color();
    printf("   ");
    set_color(10, 0); printf("Vies: %d", lives); reset_color();
    printf("   ");
    set_color(14, 0); printf("Temps: %ds", secondsLeft); reset_color();

    // Ligne 2 : Aide commandes
    goto_rc(2, 0);
    set_color(7, 0);
    printf("ZQSD=Deplacer  ESPACE=Selection/Permutation  ESC=Quitter");
    reset_color();
}

// Applique la gravité : les items tombent vers le bas, les vides (0) remontent.
void board_apply_gravity(Board* b) {
    for (int c = 0; c < COLS; ++c) {
        int write = ROWS - 1; // index où on écrit le prochain item non vide
        for (int r = ROWS - 1; r >= 0; --r) {
            if (b->cells[r][c] != 0) {
                if (write != r) {
                    b->cells[write][c] = b->cells[r][c];
                    b->cells[r][c] = 0;
                }
                --write;
            }
        }
    }
}

// Remplit aléatoirement les vides (0) en haut après gravité.
void board_refill(Board* b, unsigned* rng) {
    static const Item choices[5] = { IT_S, IT_F, IT_P, IT_O, IT_M };
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (b->cells[r][c] == 0) {
                b->cells[r][c] = choices[rnd_range(rng, 5)];
            }
        }
    }
}

// Renvoie 1 si AUCUN run horizontal/vertical de longueur >= 3 n'existe, sinon 0.
// (Les figures H/rectangle seront traitées au niveau de match_find; ici on ne
// vérifie que les runs simples pour la "stabilité initiale" du CDC.)
int board_is_stable(const Board* b) {
    // Check horizontal
    for (int r = 0; r < ROWS; ++r) {
        int run = 1;
        for (int c = 1; c < COLS; ++c) {
            Item prev = b->cells[r][c - 1];
            Item cur  = b->cells[r][c];
            if (prev != 0 && cur == prev) {
                ++run;
                if (run >= 3) return 0; // match trouvé
            } else {
                run = 1;
            }
        }
    }
    // Check vertical
    for (int c = 0; c < COLS; ++c) {
        int run = 1;
        for (int r = 1; r < ROWS; ++r) {
            Item prev = b->cells[r - 1][c];
            Item cur  = b->cells[r][c];
            if (prev != 0 && cur == prev) {
                ++run;
                if (run >= 3) return 0; // match trouvé
            } else {
                run = 1;
            }
        }
    }
    return 1; // stable
}

// Tente de générer un plateau aléatoire S/F/P/O/M sans run >=3 au départ.
// maxTries : nombre d'essais avant d'abandonner.
// Retourne 1 si OK, 0 sinon.
int board_generate_stable(Board* b, unsigned* rng, int maxTries) {
    for (int t = 0; t < maxTries; ++t) {
        board_fill_random(b, rng);
        if (board_is_stable(b)) return 1;
    }
    return 0;
}

// Échange deux cases si coordonnées valides.
void board_swap(Board* b, int r1, int c1, int r2, int c2) {
    if (r1 < 0 || r1 >= ROWS || c1 < 0 || c1 >= COLS) return;
    if (r2 < 0 || r2 >= ROWS || c2 < 0 || c2 >= COLS) return;
    Item tmp = b->cells[r1][c1];
    b->cells[r1][c1] = b->cells[r2][c2];
    b->cells[r2][c2] = tmp;
}
