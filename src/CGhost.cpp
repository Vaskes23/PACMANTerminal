//
// Created by Matyas Vascak on 11.05.2023.
//

#include "CGhost.h"

using namespace std;

Ghost::Ghost(int startX, int startY, char startChar) : x(startX), y(startY), initialX(startX), initialY(startY),
                                                       lastDirection(KEY_UP), previousChar(startChar) {}

int Ghost::getNewDirection(vector<vector<char>> &game_map, int &new_x, int &new_y, char &newChar) {
    bool isStuck = true;
    vector<int> directions = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
    shuffle(directions.begin(), directions.end(), default_random_engine(random_device{}()));

    for (int direction: directions) {
        switch (direction) {
            case KEY_UP:
                if (y > 0 && game_map[y - 1][x] != WALL && game_map[y - 1][x] != TELEPORT &&
                    lastDirection != KEY_DOWN) {
                    new_y--;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
            case KEY_DOWN:
                if (y < game_map.size() - 1 && game_map[y + 1][x] != WALL && game_map[y + 1][x] != TELEPORT &&
                    lastDirection != KEY_UP) {
                    new_y++;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
            case KEY_LEFT:
                if (x > 0 && game_map[y][x - 1] != WALL && game_map[y][x - 1] != TELEPORT &&
                    lastDirection != KEY_RIGHT) {
                    new_x--;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                }
                break;
            case KEY_RIGHT:
                if (x < game_map[0].size() - 1 && game_map[y][x + 1] != WALL && game_map[y][x + 1] != TELEPORT &&
                    lastDirection != KEY_LEFT) {
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
    return isStuck;
}

void Ghost::getStuck(int &new_x, int &new_y, char &newChar, vector<vector<char>> &game_map) {
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

void Ghost::setDefaultMoveDelay(double delay) {
    defaultMoveDelay = delay;
}

void Ghost::moveGhost(vector<vector<char>> &game_map, bool cherryEaten) {}


void Ghost::resetPosition() {
    x = initialX;
    y = initialY;
    lastDirection = KEY_UP;
}

int Ghost::manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

GhostA::GhostA(int startX, int startY, char startChar, int *p_x, int *p_y)
        : Ghost(startX, startY, startChar), pacman_x(p_x), pacman_y(p_y) {}

void GhostA::setDefaultMoveDelay(double delay) {
    defaultMoveDelay = delay;
}

void GhostA::moveGhost(vector<vector<char>> &game_map, bool cherryEaten) {
    int new_x = x, new_y = y;
    char newChar = previousChar;

    bool isStuck = true;
    vector<int> directions;

    int manhattanDist = manhattanDistance(x, y, *pacman_x, *pacman_y);

    if (!isStuck) {
        x = new_x;
        y = new_y;
        previousChar = newChar;
        moveDelay = defaultMoveDelay; // Reset move delay
    }


    if (moveDelay <= 0) {
        if (manhattanDist <= 12 && !cherryEaten) {
            if (*pacman_x > x && game_map[y][x + 1] != WALL && game_map[y][x + 1] != TELEPORT) {
                directions.push_back(KEY_RIGHT);
            } else if (*pacman_x < x && game_map[y][x - 1] != WALL && game_map[y][x - 1] != TELEPORT) {
                directions.push_back(KEY_LEFT);
            }
            if (*pacman_y > y && game_map[y + 1][x] != WALL && game_map[y + 1][x] != TELEPORT) {
                directions.push_back(KEY_DOWN);
            } else if (*pacman_y < y && game_map[y - 1][x] != WALL && game_map[y - 1][x] != TELEPORT) {
                directions.push_back(KEY_UP);
            }

            for (int direction: directions) {
                switch (direction) {
                    case KEY_UP:
                        new_y--;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                    case KEY_DOWN:
                        new_y++;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                    case KEY_LEFT:
                        new_x--;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                    case KEY_RIGHT:
                        new_x++;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                }
                if (!isStuck) {
                    lastDirection = direction;
                    break;
                }
            }
        } else if (cherryEaten) {
            if (*pacman_x > x && game_map[y][x - 1] != WALL && game_map[y][x - 1] != TELEPORT) {
                directions.push_back(KEY_LEFT);
            } else if (*pacman_x < x && game_map[y][x + 1] != WALL && game_map[y][x + 1] != TELEPORT) {
                directions.push_back(KEY_RIGHT);
            }
            if (*pacman_y > y && game_map[y - 1][x] != WALL && game_map[y - 1][x] != TELEPORT) {
                directions.push_back(KEY_UP);
            } else if (*pacman_y < y && game_map[y + 1][x] != WALL && game_map[y + 1][x] != TELEPORT) {
                directions.push_back(KEY_DOWN);
            }
            for (int direction: directions) {
                switch (direction) {
                    case KEY_UP:
                        new_y--;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                    case KEY_DOWN:
                        new_y++;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                    case KEY_LEFT:
                        new_x--;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                    case KEY_RIGHT:
                        new_x++;
                        newChar = game_map[new_y][new_x];
                        isStuck = false;
                        break;
                }
                if (!isStuck) {
                    lastDirection = direction;
                    break;
                }
            }
        } else {
            isStuck = getNewDirection(game_map, new_x, new_y, newChar);
        }
        if (!isStuck) {
            x = new_x;
            y = new_y;
            previousChar = newChar;
        } else {
            getStuck(new_x, new_y, newChar, game_map);
        }
        game_map[y][x] = previousChar;
        moveDelay = defaultMoveDelay;
    } else if (moveDelay < 0) {
        moveDelay += defaultMoveDelay; // Reset move delay if it becomes negative
    } else {
        moveDelay -= 0.3;
    }
}


GhostB::GhostB(int startX, int startY, char startChar, int *p_x, int *p_y)
        : Ghost(startX, startY, startChar), pacman_x(p_x), pacman_y(p_y) {}

void GhostB::moveGhost(vector<vector<char>> &game_map, bool cherryEaten) {
    int new_x = x, new_y = y;
    char newChar = previousChar;

    bool isStuck = true;
    vector<int> directions;

    if (moveDelay <= 0) {
        if (cherryEaten) {
            if (*pacman_x > x && game_map[y][x - 1] != WALL && game_map[y][x - 1] != TELEPORT) {
                directions.push_back(KEY_LEFT);
            } else if (*pacman_x < x && game_map[y][x + 1] != WALL && game_map[y][x + 1] != TELEPORT) {
                directions.push_back(KEY_RIGHT);
            }
            if (*pacman_y > y && game_map[y - 1][x] != WALL && game_map[y - 1][x] != TELEPORT) {
                directions.push_back(KEY_UP);
            } else if (*pacman_y < y && game_map[y + 1][x] != WALL && game_map[y + 1][x] != TELEPORT) {
                directions.push_back(KEY_DOWN);
            }
        } else {
            if (*pacman_x > x && game_map[y][x + 1] != WALL && game_map[y][x + 1] != TELEPORT) {
                directions.push_back(KEY_RIGHT);
            } else if (*pacman_x < x && game_map[y][x - 1] != WALL && game_map[y][x - 1] != TELEPORT) {
                directions.push_back(KEY_LEFT);
            }
            if (*pacman_y > y && game_map[y + 1][x] != WALL && game_map[y + 1][x] != TELEPORT) {
                directions.push_back(KEY_DOWN);
            } else if (*pacman_y < y && game_map[y - 1][x] != WALL && game_map[y - 1][x] != TELEPORT) {
                directions.push_back(KEY_UP);
            }
        }

        for (int direction: directions) {
            switch (direction) {
                case KEY_UP:
                    new_y--;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                    break;
                case KEY_DOWN:
                    new_y++;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                    break;
                case KEY_LEFT:
                    new_x--;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                    break;
                case KEY_RIGHT:
                    new_x++;
                    newChar = game_map[new_y][new_x];
                    isStuck = false;
                    break;
            }
            if (!isStuck) {
                lastDirection = direction;
                break;
            }
        }

        if (!isStuck) {
            x = new_x;
            y = new_y;
            previousChar = newChar;
        } else {
            getStuck(new_x, new_y, newChar, game_map);
        }

        game_map[y][x] = previousChar;
    } else {
        moveDelay -= 0.3;
    }
}


GhostC::GhostC(int startX, int startY, char startChar) : Ghost(startX, startY, startChar) {}

void GhostC::moveGhost(vector<vector<char>> &game_map, bool cherryEaten) {
    int new_x = x, new_y = y;
    char newChar = previousChar;

    bool isStuck = getNewDirection(game_map, new_x, new_y, newChar);

    if (!isStuck) {
        x = new_x;
        y = new_y;
        previousChar = newChar;
    } else {
        getStuck(new_x, new_y, newChar, game_map);
    }

    game_map[y][x] = previousChar;
    x = new_x;
    y = new_y;
}
