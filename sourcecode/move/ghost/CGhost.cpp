//
// Created by Matyas Vascak on 11.05.2023.
//

#include "CGhost.h"

#define WALL '#'

using namespace std;

Ghost::Ghost(int startX, int startY, char startChar) : x(startX), y(startY), lastDirection(KEY_UP),
                                                       previousChar(startChar) {}

void Ghost::moveGhost(vector<vector<char>>& game_map, bool cherryEaten) {
    int new_x = x, new_y = y;
    char newChar = previousChar;

    bool isStuck = true;

    vector<int> directions = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
    shuffle(directions.begin(), directions.end(), default_random_engine(random_device{}()));

    for (int direction : directions) {
        switch (direction) {
            case KEY_UP:
                if (y > 0 && game_map[y - 1][x] != WALL && lastDirection != KEY_DOWN) {
                    new_y--;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
            case KEY_DOWN:
                if (y < game_map.size() - 1 && game_map[y + 1][x] != WALL && lastDirection != KEY_UP) {
                    new_y++;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
            case KEY_LEFT:
                if (x > 0 && game_map[y][x - 1] != WALL && lastDirection != KEY_RIGHT) {
                    new_x--;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
            case KEY_RIGHT:
                if (x < game_map[0].size() - 1 && game_map[y][x + 1] != WALL && lastDirection != KEY_LEFT) {
                    new_x++;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
        }

        if (!isStuck) {
            lastDirection = direction;
            break;
        }
    }

    if (isStuck) {
        switch (lastDirection) {
            case KEY_UP:
                new_y++;
                newChar = game_map[new_y][new_x];
                lastDirection = KEY_DOWN;
                break;
            case KEY_DOWN:
                new_y--;
                newChar = game_map[new_y][new_x];
                lastDirection = KEY_UP;
                break;
            case KEY_LEFT:
                new_x++;
                newChar = game_map[new_y][new_x];
                lastDirection = KEY_RIGHT;
                break;
            case KEY_RIGHT:
                new_x--;
                newChar = game_map[new_y][new_x];
                lastDirection = KEY_LEFT;
                break;
        }
    }

    game_map[y][x] = previousChar;
    x = new_x;
    y = new_y;

}
