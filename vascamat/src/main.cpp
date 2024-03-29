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

    std::pair<int, int> coord;
    int charIndex;
    char pacmanChar;

    // Initialize game
    cMoveInstanceMain.initializePacman(gameMap, displayedMap, coord, currentDirection, charIndex,
                                       pacman_chars_right,pacman_chars_left, pacmanChar);

    // Start game
    cMoveInstanceMain.startGame(coord, gameMap, displayedMap, currentDirection, charIndex, pacman_chars_up,
                                pacman_chars_down, pacman_chars_right, pacman_chars_left, pacmanChar, name);

    endwin();
    return 0;
}
