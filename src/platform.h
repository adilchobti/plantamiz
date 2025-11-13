#ifndef PLATFORM_H
#define PLATFORM_H


// Windows-only console helpers
// Fournit un petit wrap pour : position curseur, couleur, masquage curseur,
// temporisation, clavier non bloquant, chrono.

#include <windows.h>
/* Codes couleur texte/fond pour la console Windows */
#define CLR_BLACK  0
#define CLR_BLUE   1
#define CLR_GREEN  2
#define CLR_CYAN   3
#define CLR_RED    4
#define CLR_MAGENTA 5
#define CLR_YELLOW 6
#define CLR_WHITE  15


#ifdef __cplusplus
extern "C" {
#endif

// Couleurs 0..15 (palette console Windows)
void plt_init_console(void);
void plt_shutdown_console(void);
void plt_goto_rc(int r, int c);           // r,c en 0-based
void plt_set_color(int fg, int bg);       // 0..15, -1 pour ne pas changer
void plt_hide_cursor(int hide);           // 1 pour cacher, 0 pour montrer
void plt_sleep_ms(int ms);
unsigned int plt_now_ms(void);            // GetTickCount()

int plt_kbhit(void);                      // _kbhit()
int plt_getch(void);                      // _getch() (retourne int 0..255, ou codes spéciaux)

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_H
