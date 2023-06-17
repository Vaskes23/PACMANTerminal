#include "main.h"

using namespace std;

CUtilities cMoveInstanceMain;
CUIMenu CUIMenuInstanceMain;

int main() {
    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();   // Line buffering disabled. pass on everything
    string name = CUIMenuInstanceMain.mainMenu();

    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ISIG;  // Disable the INTR, QUIT and SUSP characters
    tcsetattr(0, TCSANOW, &term);

    int height, width, starty = 0, startx = 0;
    CUIMenuInstanceMain.initializeWindowAndCurses(height, width, starty, startx);

    // Pac-Man-like characters
    vector<char> pacman_chars_up = {'v', '|'};
    vector<char> pacman_chars_down = {'^', '|'};
    vector<char> pacman_chars_right = {'-', '<', '(', '{', '(', '<', '-'};
    vector<char> pacman_chars_left = {'-', '>', ')', '}', ')', '>', '-'};


    vector<char> *currentDirection = &pacman_chars_right;
    vector<vector<char> > gameMap, displayedMap;

    nodelay(stdscr, TRUE);

    int x, y, charIndex;
    char pacmanChar;

    // Initialize game
    cMoveInstanceMain.initializePacman(gameMap, displayedMap, x, y, currentDirection, charIndex,
                                       pacman_chars_right,pacman_chars_left, pacmanChar);

    // Start game
    cMoveInstanceMain.startGame(x, y, gameMap, displayedMap, currentDirection, charIndex, pacman_chars_up,
                                pacman_chars_down,
                                pacman_chars_right, pacman_chars_left, pacmanChar, name);

    endwin();
    return 0;
}