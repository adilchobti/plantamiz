/**
 * @file save.c
 * @brief Save/load implementation
 */
#include "save.h"
#include <stdio.h>
#include <string.h>

#define SAVE_FILE "save.dat"

int save_load(Save* s, const char* player) {
    FILE* f = fopen(SAVE_FILE, "rb");
    if (!f) {
        return 0;
    }

    Save temp;
    while (fread(&temp, sizeof(Save), 1, f) == 1) {
        if (strcmp(temp.playerName, player) == 0) {
            *s = temp;
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int save_write(const Save* s) {
    Save existing[256];
    int count = 0;

    /* Read all existing saves */
    FILE* f = fopen(SAVE_FILE, "rb");
    if (f) {
        while (fread(&existing[count], sizeof(Save), 1, f) == 1 && count < 256) {
            count++;
        }
        fclose(f);
    }

    /* Update or add new save */
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(existing[i].playerName, s->playerName) == 0) {
            existing[i] = *s;
            found = 1;
            break;
        }
    }

    if (!found && count < 256) {
        existing[count++] = *s;
    }

    /* Write all saves back */
    f = fopen(SAVE_FILE, "wb");
    if (!f) {
        return 0;
    }

    fwrite(existing, sizeof(Save), count, f);
    fclose(f);
    return 1;
}
