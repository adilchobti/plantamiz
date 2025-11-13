#include "platform.h"
#include <conio.h>   // _kbhit, _getch
#include <stdio.h>

static HANDLE hOut = NULL;
static CONSOLE_CURSOR_INFO savedCci;
static int savedCursorKnown = 0;
static WORD savedAttrs = 0;
static int savedAttrsKnown = 0;

void plt_init_console(void) {
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Sauver attributs
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(hOut, &info)) {
        savedAttrs = info.wAttributes;
        savedAttrsKnown = 1;
    }

    // Sauver état curseur et le cacher au démarrage
    if (GetConsoleCursorInfo(hOut, &savedCci)) {
        savedCursorKnown = 1;
    }
    plt_hide_cursor(1);

    // Clear + home
    DWORD count;
    COORD home = {0, 0};
    FillConsoleOutputCharacterA(hOut, ' ', 80 * 300, home, &count);
    FillConsoleOutputAttribute(hOut, savedAttrsKnown ? savedAttrs : 7, 80 * 300, home, &count);
    SetConsoleCursorPosition(hOut, home);
}

void plt_shutdown_console(void) {
    // Rétablir couleur
    if (savedAttrsKnown) {
        SetConsoleTextAttribute(hOut, savedAttrs);
    }
    // Afficher curseur
    plt_hide_cursor(0);
    // Remettre taille curseur si on l’a modifié
    if (savedCursorKnown) {
        SetConsoleCursorInfo(hOut, &savedCci);
    }
}

void plt_goto_rc(int r, int c) {
    COORD pos;
    pos.X = (SHORT)c;
    pos.Y = (SHORT)r;
    SetConsoleCursorPosition(hOut, pos);
}

void plt_set_color(int fg, int bg) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    WORD attrs = 0;
    if (GetConsoleScreenBufferInfo(hOut, &info)) {
        attrs = info.wAttributes;
    }
    if (fg >= 0) {
        attrs = (attrs & 0xF0) | (fg & 0x0F);
    }
    if (bg >= 0) {
        attrs = (attrs & 0x0F) | ((bg & 0x0F) << 4);
    }
    SetConsoleTextAttribute(hOut, attrs);
}

void plt_hide_cursor(int hide) {
    CONSOLE_CURSOR_INFO cci;
    if (!GetConsoleCursorInfo(hOut, &cci)) return;
    if (savedCursorKnown == 0) {
        savedCci = cci;
        savedCursorKnown = 1;
    }
    cci.bVisible = hide ? FALSE : TRUE;
    SetConsoleCursorInfo(hOut, &cci);
}

void plt_sleep_ms(int ms) {
    Sleep((DWORD)ms);
}

unsigned int plt_now_ms(void) {
    return GetTickCount();
}

int plt_kbhit(void) {
    return _kbhit();
}

int plt_getch(void) {
    return _getch();
}
