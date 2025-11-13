// src/contracts.c
#include "contracts.h"

static const Contract g_contracts[NUM_LEVELS] = {
    // Niveau 1 : 20 fraises, 50 oignons, 20 mandarines en 30 coups, 120s
    { 0, 20, 0, 50, 20, 30, 120 },
    // Niveau 2 : 55 soleils, 35 pommes, 30 fraises, 45 oignons en 40 coups, 150s
    { 55, 30, 35, 45, 0, 40, 150 },
    // Niveau 3 : un peu plus dur
    { 60, 40, 40, 40, 40, 45, 180 }
};

Contract contracts_get(int levelIndex) {
    if (levelIndex < 0 || levelIndex >= NUM_LEVELS) {
        return g_contracts[0];
    }
    return g_contracts[levelIndex];
}
