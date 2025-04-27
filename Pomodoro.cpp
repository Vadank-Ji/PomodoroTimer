#include <iostream>
#include <ncurses.h>  // use <ncurses.h> or <pdcurses.h> depending on platform

int main() {
    initscr();          // Initialize screen
    cbreak();           // Disable line buffering
    //nodelay(stdscr, TRUE); // Make getch non-blocking
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();           // Don't echo typed characters

    printw("Press Enter to quit...\n");
    refresh();
    int ch;
    while (true) {
        ch = getch();
        if (ch == '\n' || ch == KEY_ENTER || ch == 10 || ch == 13) {
            break;
        }
        // do other stuff here...
    }
    printw("Enter pressed!\n");
    refresh();
    getch();
    endwin();  // End curses mode
    return 0;
}