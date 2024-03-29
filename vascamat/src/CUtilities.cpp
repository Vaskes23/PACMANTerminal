//
// Created by Matyas Vascak on 11.05.2023.
//
#include "CUtilities.h"

#define WALL '#'
#define EMPTY_SPACE ' '
#define CHERRY '%'
#define APPLE '@'
#define POINT '.'
#define TELEPORT 'X'

ConfigurationManagement configurationManagementInstance;

using namespace std;

pair<int, int> CUtilities::findPacmanInitialPosition(const vector<vector<char> > &gameMap) {
    int x = -1, y = -1;
    // find pacman
    for (int i = 0; i < gameMap.size(); ++i) {
        for (int j = 0; j < gameMap[i].size(); ++j) {
            if (gameMap[i][j] == '<') {
                y = i;
                x = j;
                break;
            }
        }
        if (x != -1 && y != -1) {
            break;
        }
    }
    return make_pair(x, y);
}

void
CUtilities::initializePacman(vector<std::vector<char> > &gameMap, std::vector<std::vector<char> > &displayedMap,
                             std::pair<int, int> &coord, std::vector<char> *&currentDirection, int &charIndex,
                             std::vector<char> &pacman_chars_right,
                             std::vector<char> &pacman_chars_left, char &pacmanChar) {

    int max_height, max_width;

    gameMap = configurationManagementInstance.readMapFromFile("examples/map1.txt");

    // Check if the map is valid
    for (int i = 0; i < gameMap.size(); ++i) {
        // Check every row's front and back
        if (gameMap[i].front() != WALL || gameMap[i].back() != WALL) {
            throw runtime_error("The walls are not complete in the map");
        }
        // Check every cell in the row
        for (int j = 0; j < gameMap[i].size(); ++j) {
            if (i == 0 || i == gameMap.size() - 1) { // Top and bottom row
                if (gameMap[i][j] != WALL) {
                    throw runtime_error("The walls are not complete in the map");
                }
            }
        }
    }

    // check if the terminal window is big enough for the map
    try {
        getmaxyx(stdscr, max_height, max_width);
        if (gameMap.size() >= max_height - 2 || gameMap[0].size() >= max_width - 2) {
            throw runtime_error("The terminal window is not big enough for the map");
        }
    } catch (const runtime_error &e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
    displayedMap = gameMap;

    // initialize pacman
    pacmanInitPos = findPacmanInitialPosition(gameMap);
    coord.first = pacmanInitPos.first;
    coord.second = pacmanInitPos.second;

    currentDirection = &pacman_chars_right;
    charIndex = 0;

    pacmanChar = pacman_chars_left[charIndex];
}


void CUtilities::handleTeleportation(pair<int, int> &new_coord, const vector<vector<char> > &game_map,
                                     vector<char> *&current_direction,
                                     vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                                     vector<char> &pacman_chars_right,
                                     vector<char> &pacman_chars_left) {
    if (game_map[new_coord.second][new_coord.first] == TELEPORT &&
        configurationManagementInstance.getTeleportExists()) {
        if (new_coord.second == configurationManagementInstance.getTeleport()[0].first &&
            new_coord.first == configurationManagementInstance.getTeleport()[0].second) {
            new_coord.second = configurationManagementInstance.getTeleport()[1].first;
            new_coord.first = configurationManagementInstance.getTeleport()[1].second;
        } else {
            new_coord.second = configurationManagementInstance.getTeleport()[0].first;
            new_coord.first = configurationManagementInstance.getTeleport()[0].second;
        }
        // change direction of pacman after teleport
        if (new_coord.first < game_map[0].size() - 1 && game_map[new_coord.second][new_coord.first + 1] != WALL) {
            new_coord.first++;
            current_direction = &pacman_chars_right;
        } else if (new_coord.first > 0 && game_map[new_coord.second][new_coord.first - 1] != WALL) {
            new_coord.first--;
            current_direction = &pacman_chars_left;
        } else if (new_coord.second < game_map.size() - 1 && game_map[new_coord.second + 1][new_coord.first] != WALL) {
            new_coord.second++;
            current_direction = &pacman_chars_down;
        } else if (new_coord.second > 0 && game_map[new_coord.second - 1][new_coord.first] != WALL) {
            new_coord.second--;
            current_direction = &pacman_chars_up;
        }
    }
}


void
CUtilities::handleInput(int &ch, int &last_ch, bool &paused, WINDOW *pause_win, int &highlight, const string &gameTag,
                        int &score) {
    ch = getch();
    if (ch != ERR) {
        if (!paused) {
            switch (ch) {
                case KEY_LEFT:
                case KEY_RIGHT:
                case KEY_UP:
                case KEY_DOWN:
                    last_ch = ch;
                    break;
                case 'P':
                case 'p':
                    paused = !paused;
                    if (paused) {
                        displayPauseMenu(pause_win, highlight);
                    } else {
                        wclear(pause_win);
                        wrefresh(pause_win);
                    }
                    break;
            }
        } else {
            switch (ch) {
                case 'P':
                case 'p':
                    paused = !paused;
                    if (paused) {
                        // display pause menu
                        displayPauseMenu(pause_win, highlight);
                    } else {
                        wclear(pause_win);
                        wrefresh(pause_win);
                    }
                    break;
                case KEY_ENTER:
                case 10:
                case 13:
                    if (highlight == 0) {
                        paused = !paused;
                        if (!paused) {
                            wclear(pause_win);
                            wrefresh(pause_win);
                        }
                    } else if (highlight == 1) {
                        // save score to a config file
                        score = cherrysEaten + pointsEaten;
                        configurationManagementInstance.saveCurrentScore("examples/highScore.txt", gameTag, score);
                        endwin();
                        exit(0);
                    }
                    break;
                case KEY_UP:
                    highlight = (highlight - 1 + 2) % 2;
                    displayPauseMenu(pause_win, highlight);
                    break;
                case KEY_DOWN:
                    highlight = (highlight + 1) % 2;
                    displayPauseMenu(pause_win, highlight);
                    break;
            }
        }
    }
}

void CUtilities::handleLogic(pair<int, int> &new_coord, int &last_ch, const vector<vector<char> > &game_map,
                             vector<char> *&current_direction,
                             vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                             vector<char> &pacman_chars_right,
                             vector<char> &pacman_chars_left) {
    switch (last_ch) {
        case KEY_LEFT:
            if (new_coord.first > 0 && game_map[new_coord.second][new_coord.first - 1] != WALL)
                new_coord.first--;
            current_direction = &pacman_chars_left;
            break;
        case KEY_RIGHT:
            if (new_coord.first < game_map[0].size() - 1 && game_map[new_coord.second][new_coord.first + 1] != WALL)
                new_coord.first++;
            current_direction = &pacman_chars_right;
            break;
        case KEY_UP:
            if (new_coord.second > 0 && game_map[new_coord.second - 1][new_coord.first] != WALL)
                new_coord.second--;
            current_direction = &pacman_chars_up;
            break;
        case KEY_DOWN:
            if (new_coord.second < game_map.size() - 1 && game_map[new_coord.second + 1][new_coord.first] != WALL)
                new_coord.second++;
            current_direction = &pacman_chars_down;
            break;
    }
}


void CUtilities::handleScoreAndUpdateMaps(pair<int, int> &new_coord, std::pair<int, int> &coord, vector<vector<char> > &game_map,
                                          vector<vector<char> > &displayed_map, int &char_index,
                                          vector<char> *&current_direction,
                                          char &pacman_char, vector<unique_ptr<Ghost>> &ghosts) {

    // check if pacman is on the same position as cherry
    if (game_map[new_coord.second][new_coord.first] == CHERRY) {
        cherrysEaten++;
        cherryEaten = true;
        cherryEatenTimestamp = time(NULL);
    }

    // check if pacman is on the same position as point
    if (game_map[new_coord.second][new_coord.first] == POINT) {
        pointsEaten++;
    }

    // check if pacman is on the same position as apple
    if (game_map[new_coord.second][new_coord.first] == APPLE) {
        pacmanLives += 1;
    }

    // update maps with empty space
    displayed_map[coord.second][coord.first] = EMPTY_SPACE;
    game_map[coord.second][coord.first] = EMPTY_SPACE;

    char_index = (char_index + 1) % current_direction->size();
    pacman_char = (*current_direction)[char_index];

    coord.first = new_coord.first;
    coord.second = new_coord.second;

    // check if pacman is on the same position as ghost
    for (auto &ghostPtr: ghosts) {
        if (coord.first == ghostPtr->x && coord.second == ghostPtr->y && cherryEaten) {
            ghostPtr->resetPosition();
            ghostPoints += 10;
        }
    }
    displayed_map[coord.second][coord.first] = pacman_char;
}


void CUtilities::startGame(std::pair<int, int> &coord, vector<vector<char> > &gameMap,
                           vector<vector<char> > &displayedMap, vector<char> *&currentDirection, int &charIndex,
                           vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                           vector<char> &pacman_chars_right,
                           vector<char> &pacman_chars_left, char &pacmanChar, const string &gameTag) {
    difficultySettings = configurationManagementInstance.readConfig();
    clear();

    // difficulty settings
    string difficulty = settingsMenu();
    abilityTime = difficultySettings[difficulty].first;
    defaultMoveDelay = difficultySettings[difficulty].second;

    vector<unique_ptr<Ghost>> ghosts;

    for (auto &ghostPtr: ghosts) {
        ghostPtr->setDefaultMoveDelay(defaultMoveDelay);
    }

    //creates cherry
    int ch = 0, last_ch = KEY_RIGHT;
    WINDOW *pause_win = create_newwin(8, 20, (LINES - 10) / 2, (COLS - 10) / 2);

    bool paused = false, isWinner = false;
    bool gameEnd = false;
    int score = cherrysEaten + pointsEaten, highlight = 0;


    int ghostCounter = 0;

    //creates ghosts
    for (int i = 0; i < gameMap.size(); ++i) {
        for (int j = 0; j < gameMap[i].size(); ++j) {
            char current = gameMap[i][j];
            if (current == 'A' || current == 'B' || current == 'C') {
                //creates ghosts with different abilities
                switch (current) {
                    case 'A':
                        ghosts.push_back(make_unique<GhostA>(j, i, gameMap[i][j], &coord.first, &coord.second));
                        break;
                    case 'B':
                        ghosts.push_back(make_unique<GhostB>(j, i, gameMap[i][j], &coord.first, &coord.second));
                        break;
                    case 'C':
                        ghosts.push_back(make_unique<GhostC>(j, i, gameMap[i][j]));
                        break;
                }
                //clears the spawning locations of the ghosts with white space
                gameMap[i][j] = EMPTY_SPACE;
                displayedMap[i][j] = EMPTY_SPACE;
                ghostCounter++;
            }
        }
    }

    //While pacman is alive
    while (!gameEnd) {
        pair<int, int> new_coord = coord;
        handleInput(ch, last_ch, paused, pause_win, highlight, gameTag, score);

        if (paused) { continue; }

        handleLogic(new_coord, last_ch, gameMap, currentDirection, pacman_chars_up, pacman_chars_down,
                    pacman_chars_right, pacman_chars_left);

        handleTeleportation(new_coord, gameMap, currentDirection, pacman_chars_up, pacman_chars_down,
                            pacman_chars_right, pacman_chars_left);

        if (gameMap[new_coord.second][new_coord.first] == WALL) { continue; }

        // Handle score and update maps
        if (cherryEaten && time(NULL) - cherryEatenTimestamp >= abilityTime) {
            cherryEaten = false;
            for (auto &ghostPtr: ghosts) {
                displayedMap[ghostPtr->y][ghostPtr->x] = 'G';
            }
        }

        // Move ghosts
        for (auto &ghostPtr: ghosts) {
            int old_ghost_x = ghostPtr->x;
            int old_ghost_y = ghostPtr->y;
            ghostPtr->moveGhost(gameMap, cherryEaten);

            // Update displayed map
            displayedMap[old_ghost_y][old_ghost_x] = gameMap[old_ghost_y][old_ghost_x];
            if (cherryEaten) {
                displayedMap[ghostPtr->y][ghostPtr->x] = 'R';
            } else {
                displayedMap[ghostPtr->y][ghostPtr->x] = 'G';
            }
        }

        // Update score and maps
        handleScoreAndUpdateMaps(new_coord, coord, gameMap, displayedMap, charIndex, currentDirection, pacmanChar,
                                 ghosts);

        // Check if pacman is dead
        for (auto &ghostPtr: ghosts) {
            if (coord.first == ghostPtr->x && coord.second == ghostPtr->y) {
                pacmanLives--;
                if (pacmanLives <= 0) {
                    gameEnd = true;
                } else {
                    resetPacmanPosition(coord, displayedMap, pacmanChar);
                }
                break;
            }
        }

        // Display map
        displayMap(stdscr, gameMap, displayedMap, gameTag, cherrysEaten, pointsEaten, pacmanLives);
        usleep(100000);

        // Check if game is over
        if (cherrysEaten >= configurationManagementInstance.getTotalCherries() &&
            pointsEaten >= configurationManagementInstance.getTotalPoints()) {
            isWinner = true;
            gameEnd = true;
        }

        if (gameEnd) {
            // Calculate score
            score = cherrysEaten + pointsEaten + ghostPoints;
            displayEndGameMessage(isWinner, gameTag, score);
            if (isWinner) {
                // Reset pacman position
                resetGame(gameMap, displayedMap, coord, currentDirection, charIndex,
                          pacman_chars_right, pacman_chars_left, pacmanChar);
                gameEnd = false;
                isWinner = false;
                continue;
            }
        }
    }
}


void CUtilities::resetGame(vector<vector<char> > &gameMap, vector<vector<char> > &displayedMap,
                           std::pair<int, int> &coord, vector<char> *&currentDirection, int &charIndex,
                           vector<char> &pacman_chars_right, vector<char> &pacman_chars_left, char &pacmanChar) {

    gameMap = configurationManagementInstance.readMapFromFile("examples/map1.txt");
    displayedMap = gameMap;
    // Reset pacman position
    pacmanInitPos = findPacmanInitialPosition(gameMap);
    coord.first = pacmanInitPos.first;
    coord.second = pacmanInitPos.second;
    currentDirection = &pacman_chars_right;
    charIndex = 0;
    pacmanChar = pacman_chars_left[charIndex];

    // Reset game counters
    cherrysEaten = 0;
    pointsEaten = 0;
    cherryEaten = false;
    ghostPoints = 0;
}

void CUtilities::displayEndGameMessage(bool isWinner, const string &gameTag, int score) {
    if (isWinner) {
        clear();
        mvprintw(LINES / 2, (COLS - 10) / 2, "You Win!");
        refresh();
        sleep(3);
        clear();
    } else {
        configurationManagementInstance.saveCurrentScore("examples/highScore.txt", gameTag, score);
        clear();
        mvprintw(LINES / 2, (COLS - 10) / 2, "Game Over");
        refresh();
        sleep(3);
        endwin();
        exit(0);
    }
}

void CUtilities::resetPacmanPosition(pair<int, int> &coord, vector<vector<char> > &displayedMap, char &pacmanChar) {
    coord.first = pacmanInitPos.first; // reset pacman position
    coord.second = pacmanInitPos.second;
    displayedMap[coord.second][coord.first] = pacmanChar;
}



