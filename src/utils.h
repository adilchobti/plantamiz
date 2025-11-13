#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/* Efface l’écran (console Windows via system("cls")). */
void utils_clear_screen(void);

/* Lit proprement le nom du joueur (fgets + trim). */
void utils_get_player_name(char* buf, size_t buflen);

/* Vide tout ce qui traîne dans stdin jusqu’à \n ou EOF. */
void utils_flush_stdin(void);

/* Enlève \n final si présent. */
void utils_chomp(char* s);

#endif
