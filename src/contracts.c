/**
 * @file contracts.c
 * @brief Contract definitions implementation
 */
#include "contracts.h"
#include <stddef.h>

static const Contract LEVELS[NUM_LEVELS] = {
    /* Level 1 */
    {
        .targetS = 0,
        .targetF = 20,
        .targetP = 0,
        .targetO = 50,
        .targetM = 20,
        .movesMax = 30,
        .seconds = 120
    },
    /* Level 2 */
    {
        .targetS = 55,
        .targetF = 30,
        .targetP = 35,
        .targetO = 45,
        .targetM = 0,
        .movesMax = 40,
        .seconds = 150
    },
    /* Level 3 */
    {
        .targetS = 70,
        .targetF = 60,
        .targetP = 50,
        .targetO = 60,
        .targetM = 40,
        .movesMax = 50,
        .seconds = 180
    }
};

const Contract* contracts_get(int levelIndex) {
    if (levelIndex < 0 || levelIndex >= NUM_LEVELS) {
        return NULL;
    }
    return &LEVELS[levelIndex];
}
