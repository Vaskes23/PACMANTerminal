//
// Created by Matyas Vascak on 11.05.2023.
//

#include "CPrint.h"

using namespace std;

WINDOW *CPrint::create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win = newwin(height, width, starty, startx);//create new window
    return local_win;
}

void CPrint::destroy_win(WINDOW *local_win) {
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);
}

void CPrint::displayMap(WINDOW *win, const std::vector<std::vector<char> > &game_map,
                        const std::vector<std::vector<char> > &displayed_map,
                        std::string game_tag, int cherrysEaten, int pointsEaten, int pacmanLives) {
    //The for loop displays the map
    for (int i = 0; i < game_map.size(); ++i) {
        for (int j = 0; j < game_map[i].size(); ++j) {
            mvwaddch(win, i + 1, j + 1, displayed_map[i][j]);
        }
    }

    //The following lines display the game stats
    mvwprintw(win, 0, game_map[0].size() + 4, "Cherries eaten: %d", cherrysEaten);
    mvwprintw(win, 1, game_map[0].size() + 4, "Points eaten: %d", pointsEaten);
    mvwprintw(win, 2, game_map[0].size() + 4, "Lives: %d", pacmanLives);
    mvwprintw(win, 3, game_map[0].size() + 4, "Game Tag: %s", game_tag.c_str());
    refresh();
    wrefresh(win);
}






