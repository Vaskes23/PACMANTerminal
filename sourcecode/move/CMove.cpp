//
// Created by Matyas Vascak on 11.05.2023.
//
#include "CMove.h"

#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

#define WALL '#'
#define EMPTY_SPACE ' '
#define CHERRY '@'
#define POINT '.'
#define TELEPORT 'X'

CPrint cPrintInstance;

int cherrysEaten = 0, pointsEaten = 0; //counter for the number of objects eaten

pair<int, int> teleport[2]; // Store the coordinates of the teleportation points
bool teleport_exists = false; // To check if teleportation point exists in map

using namespace std;

void CMove::initializeWindowAndCurses(int &height, int &width, int &starty, int &startx) {
    // Initialize the window parameters
    height = 1500;
    width = 1500;
    starty = 0;
    startx = 0;

    initscr();              // Start curses mode
    cbreak();               // Line buffering disabled, Pass everything to me
    keypad(stdscr, TRUE);   // Enable function keys
    curs_set(0);            // Hide the cursor
    srand(time(NULL));      // Random seed
}

vector<vector<char> > CMove::readMapFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open map file");
    }

    vector<vector<char> > game_map;
    string line;

    int pacmannumber = 0, ghostnumber = 0, points = 0, cherrys = 0, teleport_count = 0;

    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        game_map.push_back(row);

        //count game objects
        for (int i = 0; i < row.size(); ++i) {
            char ch = row[i];
            if (ch == 'C') {
                pacmannumber++;
            } else if (ch == 'A') {
                ghostnumber++;
            } else if (ch == '.') {
                points++;
            } else if (ch == '@') {
                cherrys++;
            } else if (ch == TELEPORT) {
                teleport[teleport_count] = make_pair(game_map.size() - 1, i);
                teleport_count++;
                if (teleport_count > 2) {
                    throw runtime_error("The map must have exactly two teleportation points ('X')");
                }
            }
        }
    }
    if (pacmannumber != 1) {
        throw runtime_error("The map must have exactly one Pacman ('C')");
    }
    if (ghostnumber < 1 || ghostnumber > 4) {
        throw runtime_error("The map must have between 1 and 4 ghosts ('A')");
    }
    if (teleport_count == 2) {
        teleport_exists = true;
    } else if (teleport_count > 0) {
        throw runtime_error("The map must have exactly two teleportation points ('X')");
    }
    return game_map;
}

pair<int, int> CMove::findPacmanInitialPosition(const vector<vector<char> > &gameMap) {
    int x = -1, y = -1;
    for (int i = 0; i < gameMap.size(); ++i) {
        for (int j = 0; j < gameMap[i].size(); ++j) {
            if (gameMap[i][j] == 'C') {
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

    // Check if the terminal window is big enough for the map
    int max_height, max_width;

    // Load the map from file
    gameMap = readMapFromFile("../configurationFiles/map1.txt");

    // Check if the walls are complete
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

    // Initialize the position of Pacman
    x = findPacmanInitialPosition(gameMap).first;
    y = findPacmanInitialPosition(gameMap).second;

    // Initialize the direction of Pacman
    currentDirection = &pacman_chars_right;
    charIndex = 0;

    // Initialize the Pacman character
    pacmanChar = pacman_chars_left[charIndex];
}

void CMove::handleTeleportation(int &new_x, int &new_y, const vector<vector<char> > &game_map,
                                vector<char> *&current_direction,
                                vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                                vector<char> &pacman_chars_right,
                                vector<char> &pacman_chars_left) {
    if (game_map[new_y][new_x] == TELEPORT && teleport_exists) {
        if (new_y == teleport[0].first && new_x == teleport[0].second) {
            new_y = teleport[1].first;
            new_x = teleport[1].second;
        } else {
            new_y = teleport[0].first;
            new_x = teleport[0].second;
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

void CMove::handleInput(int &ch, int &last_ch, bool &paused, WINDOW *pause_win, int &highlight) {
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
                    paused = !paused; // switch the game state
                    if (paused) {
                        cPrintInstance.displayPauseMenu(pause_win, highlight);
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
                    paused = !paused; // switch the game state
                    if (paused) {
                        cPrintInstance.displayPauseMenu(pause_win, highlight);
                    } else {
                        wclear(pause_win);
                        wrefresh(pause_win);
                    }
                    break;
                case KEY_ENTER:
                case 10:
                case 13:
                    if (highlight == 0) {
                        paused = !paused; // switch the game state
                        if (!paused) {
                            wclear(pause_win);
                            wrefresh(pause_win);
                        }
                    } else if (highlight == 1) {
                        endwin();
                        exit(0);
                    }
                    break;
                case KEY_UP:
                    highlight = (highlight - 1 + 2) % 2;
                    cPrintInstance.displayPauseMenu(pause_win, highlight);
                    break;
                case KEY_DOWN:
                    highlight = (highlight + 1) % 2;
                    cPrintInstance.displayPauseMenu(pause_win, highlight);
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
                                     char &pacman_char) {
    // Check if the new position is a cherry
    if (game_map[new_y][new_x] == CHERRY) {
        cherrysEaten++; // increment the counter for the number of cherries eaten
    }

    // Check if the new position is a point
    if (game_map[new_y][new_x] == POINT) {
        pointsEaten++; // increment the counter for the number of points eaten
    }

    // Clear current character
    displayed_map[y][x] = EMPTY_SPACE;
    game_map[y][x] = EMPTY_SPACE; // Clear the eaten point/cherry from the game map

    // Cycle the Pac-Man character
    char_index = (char_index + 1) % current_direction->size();
    pacman_char = (*current_direction)[char_index];

    // Update x, y
    x = new_x;
    y = new_y;

    // Update the displayed map with the new position of Pacman
    displayed_map[y][x] = pacman_char;
}

void CMove::startGame(int &x, int &y, vector<vector<char> > &gameMap,
                      vector<vector<char> > &displayedMap, vector<char> *&currentDirection, int &charIndex,
                      vector<char> &pacman_chars_up, vector<char> &pacman_chars_down, vector<char> &pacman_chars_right,
                      vector<char> &pacman_chars_left, char &pacmanChar, const string &gameTag) {
    clear();
    int ch = 0, last_ch = KEY_RIGHT;
    WINDOW *pause_win = cPrintInstance.create_newwin(8, 20, (LINES - 10) / 2, (COLS - 10) / 2);

    bool paused = false;
    int highlight = 0;
    bool gameEnd = false; // flag to determine when the game ends

    while (!gameEnd) {
        int new_x = x, new_y = y;

        handleInput(ch, last_ch, paused, pause_win, highlight);

        if (paused) {
            continue; // Don't update the game state if it's paused
        }

        handleLogic(new_x, new_y, last_ch, gameMap, currentDirection, pacman_chars_up, pacman_chars_down,
                    pacman_chars_right, pacman_chars_left);
        handleTeleportation(new_x, new_y, gameMap, currentDirection, pacman_chars_up, pacman_chars_down,
                            pacman_chars_right, pacman_chars_left);

        if (gameMap[new_y][new_x] == WALL) {
            continue;
        }

        handleScoreAndUpdateMaps(new_x, new_y, x, y, gameMap, displayedMap, charIndex, currentDirection, pacmanChar);
        cPrintInstance.displayMap(stdscr, gameMap, displayedMap, gameTag, cherrysEaten, pointsEaten);
        usleep(100000);  // Control the speed of the game

        if (cherrysEaten + pointsEaten == totalCherries + totalPoints) {
            gameEnd = true;
        }
    }

    // After the game ends, update the high scores
    int score = cherrysEaten + pointsEaten;  // calculate the score based on your scoring system
    updateHighScores("../configurationFiles/highScore.txt", gameTag, score);
}

//--------------------------------------------------------------


// Function to read high scores from the file
vector<CMove::ScoreEntry> CMove::readHighScores(const string &filename) {
    ifstream file(filename);
    vector<ScoreEntry> scores;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        ScoreEntry entry;
        if (!(iss >> entry.game_tag >> entry.score)) {
            break;  // Error in parsing
        }
        scores.push_back(entry);
    }

    return scores;
}

// Function to write high scores to the file
void CMove::writeHighScores(const string &filename, const vector<CMove::ScoreEntry> &scores) {
    ofstream file(filename);

    for (const auto &entry : scores) {
        file << entry.game_tag << " " << entry.score << endl;
    }
}

// Function to update high scores if current score is in the top 10
void CMove::updateHighScores(const string &filename, const string &game_tag, int score) {
    vector<CMove::ScoreEntry> scores = readHighScores(filename);

    // Check if the current score is high enough to be in the top 10
    if (scores.size() < 10 || score > scores.back().score) {
        // If the list of scores is already 10, remove the last one
        if (scores.size() == 10) {
            scores.pop_back();
        }

        // Add the new high score
        scores.push_back({game_tag, score});

        // Sort the scores in decreasing order
        sort(scores.begin(), scores.end(),
             [](const CMove::ScoreEntry &a, const CMove::ScoreEntry &b) {
                 return a.score > b.score;
             });

        // Write the updated scores back into the file
        writeHighScores(filename, scores);
    }
}