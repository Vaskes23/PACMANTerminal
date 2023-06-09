//
// Created by Matyas Vascak on 11.05.2023.
//

#include "CPrint.h"

#include <algorithm>
#include <sstream>
#include <ncurses.h>
#include <string>
#include <vector>

CMove cMoveInstance;

WINDOW *CPrint::create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win = newwin(height, width, starty, startx);
    return local_win;
}

// Function to destroy the game window
void CPrint::destroy_win(WINDOW *local_win) {
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);
}

void CPrint::displayMap(WINDOW *win, const std::vector<std::vector<char> > &game_map,
                        const std::vector<std::vector<char> > &displayed_map,
                        std::string game_tag, int cherrysEaten, int pointsEaten, int pacmanLives){
    for (int i = 0; i < game_map.size(); ++i) {
        for (int j = 0; j < game_map[i].size(); ++j) {
            mvwaddch(win, i + 1, j + 1, displayed_map[i][j]);
        }
    }
    mvwprintw(win, 0, game_map[0].size() + 4, "Cherries eaten: %d", cherrysEaten);
    mvwprintw(win, 1, game_map[0].size() + 4, "Points eaten: %d", pointsEaten);
    mvwprintw(win, 2, game_map[0].size() + 4, "Lives: %d", pacmanLives);
    mvwprintw(win, 3, game_map[0].size() + 4, "Game Tag: %s", game_tag.c_str());
    refresh();
    wrefresh(win);
}

void CPrint::displayPauseMenu(WINDOW *win, int highlight) {
    string choices[2] = {"CONTINUE", "EXIT"};
    int x = 4, y = 2;

    box(win, 0, 0);
    for (int i = 0; i < 2; i++) {
        if (i == highlight)
            wattron(win, A_REVERSE);
        mvwprintw(win, y, x, "%s", choices[i].c_str());
        wattroff(win, A_REVERSE);
        y += 2;
    }
    wrefresh(win);
}

void CPrint::displayMenu(WINDOW *win, int highlight) {
    string choices[4] = {"PLAY", "SCORE BOARD", "SETTINGS", "EXIT"};
    int x = 4, y = 2;

    box(win, 0, 0);
    for (int i = 0; i < 4; i++) {
        if (i == highlight)
            wattron(win, A_REVERSE);
        mvwprintw(win, y, x, "%s", choices[i].c_str());
        wattroff(win, A_REVERSE);
        y += 2;
    }
    wrefresh(win);
}

string CPrint::askGameTag(string &game_tag) {
    WINDOW *input_win;
    echo();
    char str[11];
    mvprintw(LINES - 3, 0, "Please enter your game tag (max 10 characters): ");
    wgetnstr(stdscr, str, 10);  // Only allow 10 characters input

    str[10] = '\0'; // ensure null-terminated
    noecho();
    refresh();

    // clear the input line
    for (int i = 0; i < COLS; i++) {
        mvaddch(LINES - 3, i, ' ');
    }

    mvprintw(LINES - 3, 0, "Game tag: %s", str);
    game_tag = str;
    refresh();
    return game_tag;
}



string CPrint::mainMenu() {
    WINDOW *menu_win;
    int highlight = 0;
    int choice = -1;
    int c;
    string name = "";

    int startx, starty, width, height;
    height = 10;
    width = 30;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;

    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    displayMenu(menu_win, highlight);

    string game_tag;
    while (choice == -1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 0)
                    highlight = 3;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == 3) {
                    highlight = 0;
                } else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
        }
        displayMenu(menu_win, highlight);
        if (choice == 0) {
                name = askGameTag(game_tag);
        }
        else if (choice == 1) {
            string scoreboard = cMoveInstance.getScoreBoard("../configurationFiles/highScore.txt");
            displayScoreBoard(menu_win, scoreboard);
            getch();
            wclear(menu_win);
            choice = -1;  // Reset choice here so it doesn't default to starting the game
        } else if (choice == 3) {
            endwin();
            exit(0);
        }
    }

    return name;
}

void CPrint::displayScoreBoard(WINDOW *win, const string &scoreboard) {
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s", scoreboard.c_str());
    wrefresh(win);
}
