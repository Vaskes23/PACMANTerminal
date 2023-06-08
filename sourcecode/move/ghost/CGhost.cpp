//
// Created by Matyas Vascak on 11.05.2023.
//

#include "CGhost.h"

#define WALL '#'
//#define KEY_UP 0
//#define KEY_DOWN 1
//#define KEY_LEFT 2
//#define KEY_RIGHT 3

using namespace std;

Ghost::Ghost(int startX, int startY) : x(startX), y(startY), lastDirection(KEY_UP) {}

void Ghost::moveGhost(vector<vector<char>>& game_map) {
    int new_x = x, new_y = y;

    vector<int> directions = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
    shuffle(directions.begin(), directions.end(), default_random_engine(random_device{}()));

    for (int direction : directions) {
        switch (direction) {
            case KEY_UP:
                if (y > 0 && game_map[y - 1][x] != WALL && lastDirection != KEY_DOWN) {
                    new_y--;
                }
                break;
            case KEY_DOWN:
                if (y < game_map.size() - 1 && game_map[y + 1][x] != WALL && lastDirection != KEY_UP) {
                    new_y++;
                }
                break;
            case KEY_LEFT:
                if (x > 0 && game_map[y][x - 1] != WALL && lastDirection != KEY_RIGHT) {
                    new_x--;
                }
                break;
            case KEY_RIGHT:
                if (x < game_map[0].size() - 1 && game_map[y][x + 1] != WALL && lastDirection != KEY_LEFT) {
                    new_x++;
                }
                break;
        }

        if (new_x != x || new_y != y) {
            lastDirection = direction;
            break;
        }
    }

    game_map[y][x] = ' '; // replace this with your EMPTY_SPACE macro or constant
    x = new_x;
    y = new_y;
    game_map[y][x] = 'G';
}
