#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void utils_clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    // Fallback ANSI si jamais…
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
#endif
}

void utils_chomp(char* s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
}

void utils_flush_stdin(void) {
    int ch;
    // On vide tout le tampon jusqu’à fin de ligne
    while ((ch = getchar()) != '\n' && ch != EOF) { /* nop */ }
}

void utils_get_player_name(char* buf, size_t buflen) {
    if (!buf || buflen == 0) return;
    printf("Entrez votre nom: ");
    fflush(stdout);
    if (fgets(buf, (int)buflen, stdin) == NULL) {
        // Valeur par défaut si lecture KO
        snprintf(buf, buflen, "Player");
        return;
    }
    utils_chomp(buf);
    if (buf[0] == '\0') {
        snprintf(buf, buflen, "Player");
    }
}
