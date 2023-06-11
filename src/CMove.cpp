//
// Created by Matyas Vascak on 11.05.2023.
//
#include "CMove.h"

#define WALL '#'
#define EMPTY_SPACE ' '
#define CHERRY '%'
#define APPLE '@'
#define POINT '.'
#define TELEPORT 'X'

CPrint cPrintInstance;
CUIMenu cUIMenuInstance;
ConfigurationManagement configurationManagementInstance;

using namespace std;

pair<int, int> CMove::findPacmanInitialPosition(const vector<vector<char> > &gameMap) {
    int x = -1, y = -1;
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

void CMove::initializePacman(vector<vector<char> > &gameMap, vector<vector<char> > &displayedMap, int &x, int &y,
                             vector<char> *&currentDirection, int &charIndex,
                             vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                             vector<char> &pacman_chars_right,
                             vector<char> &pacman_chars_left, char &pacmanChar) {

    int max_height, max_width;

    gameMap = configurationManagementInstance.readMapFromFile("../examples/map1.txt");

    for (int i = 0; i < gameMap.size(); ++i) {
        if (gameMap[i].front() != WALL || gameMap[i].back() != WALL) {
            throw runtime_error("The walls are not complete in the map");
        }
    }

    getmaxyx(stdscr, max_height, max_width);
    if (gameMap.size() >= max_height - 2 || gameMap[0].size() >= max_width - 2) {
        throw runtime_error("The terminal window is not big enough for the map");
    }
    displayedMap = gameMap;

    pacmanInitPos = findPacmanInitialPosition(gameMap);
    x = pacmanInitPos.first;
    y = pacmanInitPos.second;

    currentDirection = &pacman_chars_right;
    charIndex = 0;

    pacmanChar = pacman_chars_left[charIndex];
}

void CMove::handleTeleportation(int &new_x, int &new_y, const vector<vector<char> > &game_map,
                                vector<char> *&current_direction,
                                vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                                vector<char> &pacman_chars_right,
                                vector<char> &pacman_chars_left) {
    if (game_map[new_y][new_x] == TELEPORT && configurationManagementInstance.getTeleportExists()) {
        if (new_y == configurationManagementInstance.getTeleport()[0].first && new_x == configurationManagementInstance.getTeleport()[0].second) {
            new_y = configurationManagementInstance.getTeleport()[1].first;
            new_x = configurationManagementInstance.getTeleport()[1].second;
        } else {
            new_y = configurationManagementInstance.getTeleport()[0].first;
            new_x = configurationManagementInstance.getTeleport()[0].second;
        }
        if (new_x < game_map[0].size() - 1 && game_map[new_y][new_x + 1] != WALL) {
            new_x++;
            current_direction = &pacman_chars_right;
        } else if (new_x > 0 && game_map[new_y][new_x - 1] != WALL) {
            new_x--;
            current_direction = &pacman_chars_left;
        } else if (new_y < game_map.size() - 1 && game_map[new_y + 1][new_x] != WALL) {
            new_y++;
            current_direction = &pacman_chars_down;
        } else if (new_y > 0 && game_map[new_y - 1][new_x] != WALL) {
            new_y--;
            current_direction = &pacman_chars_up;
        }
    }
}

void CMove::saveCurrentScore(const string &filename, const string &game_tag, int score) {
    vector<CMove::ScoreEntry> scores = readHighScores(filename);

    if (scores.size() < 10 || scores.back().score < score) {
        scores.push_back({game_tag, score});

        sort(scores.begin(), scores.end(),
             [](const CMove::ScoreEntry &a, const CMove::ScoreEntry &b) {
                 return a.score > b.score;
             });

        if (scores.size() > 10) {
            scores.pop_back();
        }

        writeHighScores(filename, scores);
    }
}

void CMove::handleInput(int &ch, int &last_ch, bool &paused, WINDOW *pause_win, int &highlight, const string &gameTag,
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
                        cUIMenuInstance.displayPauseMenu(pause_win, highlight);
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
                        cUIMenuInstance.displayPauseMenu(pause_win, highlight);
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
                        score = cherrysEaten + pointsEaten;
                        saveCurrentScore("../examples/highScore.txt", gameTag, score);
                        endwin();
                        exit(0);
                    }
                    break;
                case KEY_UP:
                    highlight = (highlight - 1 + 2) % 2;
                    cUIMenuInstance.displayPauseMenu(pause_win, highlight);
                    break;
                case KEY_DOWN:
                    highlight = (highlight + 1) % 2;
                    cUIMenuInstance.displayPauseMenu(pause_win, highlight);
                    break;
            }
        }
    }
}

void CMove::handleLogic(int &new_x, int &new_y, int &last_ch, const vector<vector<char> > &game_map,
                        vector<char> *&current_direction,
                        vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                        vector<char> &pacman_chars_right,
                        vector<char> &pacman_chars_left) {
    switch (last_ch) {
        case KEY_LEFT:
            if (new_x > 0 && game_map[new_y][new_x - 1] != WALL)
                new_x--;
            current_direction = &pacman_chars_left;
            break;
        case KEY_RIGHT:
            if (new_x < game_map[0].size() - 1 && game_map[new_y][new_x + 1] != WALL)
                new_x++;
            current_direction = &pacman_chars_right;
            break;
        case KEY_UP:
            if (new_y > 0 && game_map[new_y - 1][new_x] != WALL)
                new_y--;
            current_direction = &pacman_chars_up;
            break;
        case KEY_DOWN:
            if (new_y < game_map.size() - 1 && game_map[new_y + 1][new_x] != WALL)
                new_y++;
            current_direction = &pacman_chars_down;
            break;
    }
}


void CMove::handleScoreAndUpdateMaps(int &new_x, int &new_y, int &x, int &y, vector<vector<char> > &game_map,
                                     vector<vector<char> > &displayed_map, int &char_index,
                                     vector<char> *&current_direction,
                                     char &pacman_char, vector<unique_ptr<Ghost>> &ghosts) {

    if (game_map[new_y][new_x] == CHERRY) {
        cherrysEaten++;
        cherryEaten = true;
        cherryEatenTimestamp = time(NULL);
    }

    if (game_map[new_y][new_x] == POINT) {
        pointsEaten++;
    }

    if (game_map[new_y][new_x] == APPLE) {
        pacmanLives += 1;
    }

    displayed_map[y][x] = EMPTY_SPACE;
    game_map[y][x] = EMPTY_SPACE;

    char_index = (char_index + 1) % current_direction->size();
    pacman_char = (*current_direction)[char_index];

    x = new_x;
    y = new_y;

    for (auto &ghostPtr: ghosts) {
        if (x == ghostPtr->x && y == ghostPtr->y && cherryEaten) {
            ghostPtr->resetPosition();
            ghostPoints += 10;
        }
    }
    displayed_map[y][x] = pacman_char;
}


void CMove::startGame(int &x, int &y, vector<vector<char> > &gameMap,
                      vector<vector<char> > &displayedMap, vector<char> *&currentDirection, int &charIndex,
                      vector<char> &pacman_chars_up, vector<char> &pacman_chars_down, vector<char> &pacman_chars_right,
                      vector<char> &pacman_chars_left, char &pacmanChar, const string &gameTag) {
    difficultySettings = configurationManagementInstance.readConfig();
    clear();

    string difficulty = cUIMenuInstance.settingsMenu();
    abilityTime = difficultySettings[difficulty].first;
    defaultMoveDelay = difficultySettings[difficulty].second;

    vector<unique_ptr<Ghost>> ghosts;

    for (auto &ghostPtr: ghosts) {
        ghostPtr->setDefaultMoveDelay(defaultMoveDelay);
    }

    int ch = 0, last_ch = KEY_RIGHT;
    WINDOW *pause_win = cPrintInstance.create_newwin(8, 20, (LINES - 10) / 2, (COLS - 10) / 2);

    bool paused = false, isWinner = false;
    bool gameEnd = false;
    int score = cherrysEaten + pointsEaten, highlight = 0;


    int ghostCounter = 0;

    for (int i = 0; i < gameMap.size(); ++i) {
        for (int j = 0; j < gameMap[i].size(); ++j) {
            if (gameMap[i][j] == 'G') {
                switch (ghostCounter % 3) {
                    case 0:
                        ghosts.push_back(make_unique<GhostA>(j, i, gameMap[i][j], &x, &y));
                        break;
                    case 1:
                        ghosts.push_back(make_unique<GhostB>(j, i, gameMap[i][j], &x, &y));
                        break;
                    case 2:
                        ghosts.push_back(make_unique<GhostC>(j, i, gameMap[i][j]));
                        break;
                }
                gameMap[i][j] = EMPTY_SPACE;
                displayedMap[i][j] = EMPTY_SPACE;
                ghostCounter++;
            }
        }
    }

    while (!gameEnd) {
        int new_x = x, new_y = y;
        handleInput(ch, last_ch, paused, pause_win, highlight, gameTag, score);

        if (paused) { continue; }

        handleLogic(new_x, new_y, last_ch, gameMap, currentDirection, pacman_chars_up, pacman_chars_down,
                    pacman_chars_right, pacman_chars_left);
        handleTeleportation(new_x, new_y, gameMap, currentDirection, pacman_chars_up, pacman_chars_down,
                            pacman_chars_right, pacman_chars_left);

        if (gameMap[new_y][new_x] == WALL) { continue; }

        if (cherryEaten && time(NULL) - cherryEatenTimestamp >= abilityTime) {
            cherryEaten = false;
            for (auto &ghostPtr: ghosts) {
                displayedMap[ghostPtr->y][ghostPtr->x] = 'G';
            }
        }

        for (auto &ghostPtr: ghosts) {
            int old_ghost_x = ghostPtr->x;
            int old_ghost_y = ghostPtr->y;
            ghostPtr->moveGhost(gameMap, cherryEaten);

            displayedMap[old_ghost_y][old_ghost_x] = gameMap[old_ghost_y][old_ghost_x]; // chat gpt change it instead of a empty space to the character that was there before ghost was there
            if (cherryEaten) {
                displayedMap[ghostPtr->y][ghostPtr->x] = 'R';
            } else {
                displayedMap[ghostPtr->y][ghostPtr->x] = 'G';
            }
        }

        handleScoreAndUpdateMaps(new_x, new_y, x, y, gameMap, displayedMap, charIndex, currentDirection, pacmanChar,
                                 ghosts);

        for (auto &ghostPtr: ghosts) {
            if (x == ghostPtr->x && y == ghostPtr->y) {
                pacmanLives--;
                if (pacmanLives <= 0) {
                    gameEnd = true;
                } else {
                    resetPacmanPosition(x, y, displayedMap, pacmanChar);
                }
                break;
            }
        }

        cPrintInstance.displayMap(stdscr, gameMap, displayedMap, gameTag, cherrysEaten, pointsEaten, pacmanLives);
        usleep(100000);

        if (cherrysEaten >= configurationManagementInstance.getTotalCherries() && pointsEaten >= configurationManagementInstance.getTotalPoints()) {
            isWinner = true;
            gameEnd = true;
        }

        if (gameEnd) {
            score = cherrysEaten + pointsEaten + ghostPoints;
            displayEndGameMessage(isWinner, gameTag, score);
            if (isWinner) {
                resetGame(gameMap, displayedMap, x, y, currentDirection, charIndex, pacman_chars_up, pacman_chars_down,
                          pacman_chars_right, pacman_chars_left, pacmanChar);
                gameEnd = false;
                isWinner = false;
                continue;
            }
        }
    }
}

vector<CMove::ScoreEntry> CMove::readHighScores(const string &filename) {
    ifstream file(filename);
    vector<ScoreEntry> scores;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        ScoreEntry entry;
        if (!(iss >> entry.game_tag >> entry.score)) {
            break;
        }
        scores.push_back(entry);
    }

    return scores;
}

void CMove::writeHighScores(const string &filename, const vector<CMove::ScoreEntry> &scores) {
    ofstream file(filename);

    for (const auto &entry: scores) {
        file << entry.game_tag << " " << entry.score << endl;
    }
}

string CMove::getScoreBoard(const string &filename) {
    vector<ScoreEntry> scores = readHighScores(filename);

    stringstream ss;
    ss << "SCORE BOARD\n";
    for (int i = 0; i < scores.size(); i++) {
        ss << i + 1 << ". " << scores[i].game_tag << ": " << scores[i].score << "\n";
    }
    return ss.str();
}

void CMove::resetGame(vector<vector<char> > &gameMap, vector<vector<char> > &displayedMap,
                      int &x, int &y, vector<char> *&currentDirection, int &charIndex,
                      vector<char> &pacman_chars_up, vector<char> &pacman_chars_down, vector<char> &pacman_chars_right,
                      vector<char> &pacman_chars_left, char &pacmanChar) {
    gameMap = configurationManagementInstance.readMapFromFile("../examples/map1.txt");
    displayedMap = gameMap;
    pacmanInitPos = findPacmanInitialPosition(gameMap);
    x = pacmanInitPos.first;
    y = pacmanInitPos.second;
    currentDirection = &pacman_chars_right;
    charIndex = 0;
    pacmanChar = pacman_chars_left[charIndex];

    // Reset game counters
    cherrysEaten = 0;
    pointsEaten = 0;
    cherryEaten = false;
    ghostPoints = 0;
}

void CMove::displayEndGameMessage(bool isWinner, const string &gameTag, int score) {
    if (isWinner) {
        clear();
        mvprintw(LINES / 2, (COLS - 10) / 2, "You Win!");
        refresh();
        sleep(3);
        clear();
    } else {
        saveCurrentScore("../examples/highScore.txt", gameTag, score);
        clear();
        mvprintw(LINES / 2, (COLS - 10) / 2, "Game Over");
        refresh();
        sleep(3);
        endwin();
        exit(0);
    }
}

void CMove::resetPacmanPosition(int &x, int &y, vector<vector<char> > &displayedMap, char &pacmanChar) {
    x = pacmanInitPos.first;
    y = pacmanInitPos.second;
    displayedMap[y][x] = pacmanChar;
}



