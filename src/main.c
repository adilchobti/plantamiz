#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "board.h"
#include "match.h"
#include "contracts.h"
#include "save.h"
#include "platform.h"
#include "game.h"
#include "utils.h"

int main(void) {
    /* Init console */
    plt_init_console();
    plt_hide_cursor(0);

    utils_clear_screen();
    printf("===================================\n");
    printf("          PLANTAMITZ 2025\n");
    printf("      Match-3 Console Game en C\n");
    printf("===================================\n\n");
    fflush(stdout);

    /* Nom joueur + save */
    char playerName[64];
    utils_get_player_name(playerName, sizeof(playerName));

    Save save;
    int hasSave = save_load(&save, playerName);

    int startLevel = 0;
    if (hasSave) {
        printf("\nProgression trouvée ! Niveau %d.\n", save.nextLevelIndex + 1);
        printf("Appuyez sur ENTREE pour continuer...\n");
        fflush(stdout);
        utils_flush_stdin();   // <- IMPORTANT : vide tout avant d’attendre
        getchar();             // attend un vrai Enter de l’utilisateur
        startLevel = save.nextLevelIndex;
    } else {
        strcpy(save.playerName, playerName);
        save.nextLevelIndex = 0;
    }

    /* RNG */
    unsigned rng = (unsigned)time(NULL);

    /* Boucle de jeu */
    int currentLevel = startLevel;
    int lives = 5;

    while (currentLevel < NUM_LEVELS) {
        utils_clear_screen();
        printf("Niveau %d/%d - Vies: %d\n", currentLevel + 1, NUM_LEVELS, lives);
        printf("Appuyez sur ENTREE pour commencer...\n");
        fflush(stdout);
        utils_flush_stdin();   // <- IMPORTANT : purge avant d’attendre
        getchar();

        /* State */
        GameState gameState;
        gameState.lives = lives;

        if (!game_init(&gameState, playerName, currentLevel)) {
            printf("Erreur: niveau invalide !\n");
            printf("Appuyez sur ENTREE pour quitter.\n");
            fflush(stdout);
            utils_flush_stdin();
            getchar();
            break;
        }

        /* Gameplay */
        plt_hide_cursor(1);
        utils_clear_screen();

        int result = game_play_level(&gameState, &rng);

        plt_hide_cursor(0);
        utils_clear_screen();

        if (result == -1) {
            /* Abandon */
            printf("Partie abandonnée.\n");
            printf("Appuyez sur ENTREE pour quitter.\n");
            fflush(stdout);
            utils_flush_stdin();
            getchar();
            break;
        } else if (result == 1) {
            /* Victoire */
            printf("Niveau %d terminé !\n", currentLevel + 1);
            currentLevel++;
            lives = 5; /* reset vies */

            /* Sauvegarde */
            save.nextLevelIndex = currentLevel;
            save_write(&save);

            if (currentLevel >= NUM_LEVELS) {
                printf("\nFélicitations ! Tous les niveaux sont terminés !\n");
                printf("Appuyez sur ENTREE pour quitter.\n");
                fflush(stdout);
                utils_flush_stdin();
                getchar();
                break;
            }

            printf("Appuyez sur ENTREE pour continuer...\n");
            fflush(stdout);
            utils_flush_stdin();
            getchar();
        } else {
            /* Échec */
            lives--;
            printf("Échec ! Vies restantes: %d\n", lives);

            if (lives <= 0) {
                printf("\nGame Over ! Toutes les vies perdues.\n");
                lives = 5;
                currentLevel = 0;
                save.nextLevelIndex = 0;
                save_write(&save);
                printf("Retour au niveau 1.\n");
            }

            printf("Appuyez sur ENTREE pour continuer...\n");
            fflush(stdout);
            utils_flush_stdin();
            getchar();
        }
    }

    /* Cleanup */
    plt_set_color(CLR_WHITE, CLR_BLACK);
    plt_hide_cursor(0);
    utils_clear_screen();
    printf("Merci d'avoir joué à Plantamitz !\n");
    fflush(stdout);

    return 0;
}
