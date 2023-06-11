//
// Created by Matyas Vascak on 11.05.2023.
//

#include "CUIMenu.h"

CPrint cPrintInstanceMenu;
ConfigurationManagement configurationManagementMenu;

using namespace std;

void CUIMenu::initializeWindowAndCurses(int &height, int &width, int &starty, int &startx) {
    //initialize window and curses
    height = 1500;
    width = 1500;
    starty = 0;
    startx = 0;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));
}

string CUIMenu::mainMenu() {
    //The following lines display the main menu
    WINDOW *menu_win;
    int highlight = 0;
    int choice = -1;
    int c;
    string name = "";

    //initialize window and curses
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
    //The following lines handle the user input
    while (choice == -1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 0)
                    highlight = 2;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == 2) {
                    highlight = 0;
                } else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
        }
        //The following lines handle the user choice
        displayMenu(menu_win, highlight);
        if (choice == 0) {
            name = cPrintInstanceMenu.askGameTag(game_tag);
        } else if (choice == 1) {//display scoreboard
            string scoreboard = configurationManagementMenu.getScoreBoard("../examples/highScore.txt");
            cPrintInstanceMenu.displayScoreBoard(menu_win, scoreboard);
            getch();
            wclear(menu_win);
            choice = -1;
        } else if (choice == 2) {
            endwin();
            exit(0);
        }
    }
    return name;
}

void CUIMenu::displayPauseMenu(WINDOW *win, int highlight) {
    //The following lines display the pause menu
    string choices[2] = {"CONTINUE", "EXIT"};
    int x = 4, y = 2;

    box(win, 0, 0);
    for (int i = 0; i < 2; i++) {
        if (i == highlight)
            wattron(win, A_REVERSE);//highlight the selected option
        mvwprintw(win, y, x, "%s", choices[i].c_str());
        wattroff(win, A_REVERSE);
        y += 2;
    }
    wrefresh(win);
}

void CUIMenu::displayMenu(WINDOW *win, int highlight) {
    //
    string choices[4] = {"PLAY", "SCORE BOARD", "EXIT"};
    int x = 4, y = 2;

    box(win, 0, 0);//create a box around the window
    for (int i = 0; i < 3; i++) {
        if (i == highlight)
            wattron(win, A_REVERSE);//highlight the selected option
        mvwprintw(win, y, x, "%s", choices[i].c_str());
        wattroff(win, A_REVERSE);
        y += 2;
    }
    wrefresh(win);
}

void CUIMenu::displaySettingsMenu(WINDOW *win, int highlight) {
    //The following lines display the settings menu
    string choices[3] = {"EASY\n10s cooldown, slow enemy",
                         "MEDIUM\n7s cooldown, normal enemy",
                         "HARD\n5s cooldown, fast enemy"};

    box(win, 0, 0);
    for (int i = 0; i < 3; i++) {//display the options
        if (i == highlight)
            wattron(win, A_REVERSE);

        //split the string into two lines
        size_t breakPos = choices[i].find("\n");
        string firstLine = choices[i].substr(0, breakPos);
        string secondLine = choices[i].substr(breakPos + 1);

        //center the text
        int x1 = (getmaxx(win) - firstLine.size()) / 2;
        int x2 = (getmaxx(win) - secondLine.size()) / 2;
        int y = 2 * (i + 1);

        //print the text
        mvwprintw(win, y, x1, "%s", firstLine.c_str());
        mvwprintw(win, y + 1, x2, "%s", secondLine.c_str());

        wattroff(win, A_REVERSE);//remove the highlight
    }
    wrefresh(win);//refresh the window
}

string CUIMenu::settingsMenu() {
    //The following lines display the settings menu
    WINDOW *menu_win;
    int highlight = 0;
    int choice = -1;
    int c;
    string difficulty = "";

    //initialize window and curses
    int startx, starty, width, height;
    height = 10;
    width = 30;
    starty = (LINES - height) / 2;//center the window
    startx = (COLS - width) / 2;

    //create the window
    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    displaySettingsMenu(menu_win, highlight);//display the menu

    //handle user input
    while (choice == -1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 0)
                    highlight = 2;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == 2) {
                    highlight = 0;
                } else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
        }
        //The following lines handle the user choice
        displaySettingsMenu(menu_win, highlight);
        if (choice != -1) {
            difficulty = (choice == 0) ? "EASY" : (choice == 1) ? "MEDIUM" : "HARD";
        }
    }
    //destroy the window
    cPrintInstanceMenu.destroy_win(menu_win);
    clear();
    return difficulty;
}