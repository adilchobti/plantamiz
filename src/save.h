/**
 * @file save.h
 * @brief Save/load player progression
 */
#ifndef SAVE_H
#define SAVE_H

typedef struct {
    char playerName[64];
    int nextLevelIndex;
} Save;

/**
 * @brief Load save data for player
 * @param s [OUT] Save structure to fill
 * @param player [IN] Player name
 * @return 1 if loaded, 0 if not found
 */
int save_load(Save* s, const char* player);

/**
 * @brief Write save data
 * @param s [IN] Save structure to write
 * @return 1 if success, 0 if failure
 */
int save_write(const Save* s);

#endif /* SAVE_H */
