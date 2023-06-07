#include "print/CPrint.h"
#include "move/CMove.h"

#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

#define WALL '#'
#define EMPTY_SPACE ' '
#define CHERRY '%'
#define POINT '.'
#define TELEPORT 'X'

using namespace std;

CPrint cPrintInstanceMain;
CMove cMoveInstanceMain;



int main() {
    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();   // Line buffering disabled. pass on everything
    string name = cPrintInstanceMain.mainMenu();

    int height, width, starty = 0, startx = 0;
    cMoveInstanceMain.initializeWindowAndCurses(height, width, starty, startx);

    // Pac-Man-like characters
    vector<char> pacman_chars_up;
    pacman_chars_up.push_back('v');
    pacman_chars_up.push_back('|');

    vector<char> pacman_chars_down;
    pacman_chars_down.push_back('^');
    pacman_chars_down.push_back('|');

    vector<char> pacman_chars_right;
    pacman_chars_right.push_back('-');
    pacman_chars_right.push_back('<');
    pacman_chars_right.push_back('(');
    pacman_chars_right.push_back('{');
    pacman_chars_right.push_back('(');
    pacman_chars_right.push_back('<');
    pacman_chars_right.push_back('-');

    vector<char> pacman_chars_left;
    pacman_chars_left.push_back('-');
    pacman_chars_left.push_back('>');
    pacman_chars_left.push_back(')');
    pacman_chars_left.push_back('}');
    pacman_chars_left.push_back(')');
    pacman_chars_left.push_back('>');
    pacman_chars_left.push_back('-');

    vector<char> *currentDirection = &pacman_chars_right;
    vector<vector<char> > gameMap, displayedMap;

    nodelay(stdscr, TRUE); // makes getch() non-blocking

    int x, y, charIndex;
    char pacmanChar;

    cMoveInstanceMain.initializePacman(gameMap, displayedMap, x, y, currentDirection, charIndex,
                     pacman_chars_up, pacman_chars_down, pacman_chars_right,
                     pacman_chars_left, pacmanChar);

    cMoveInstanceMain.startGame(x, y, gameMap, displayedMap, currentDirection, charIndex, pacman_chars_up, pacman_chars_down,
              pacman_chars_right, pacman_chars_left, pacmanChar, name);

    endwin();
    return 0;
}