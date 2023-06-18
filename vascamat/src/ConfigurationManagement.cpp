//
// Created by Matyas Vascak on 11.06.2023.
//

#include "ConfigurationManagement.h"

#define WALL '#'
#define EMPTY_SPACE ' '
#define CHERRY '%'
#define APPLE '@'
#define POINT '.'
#define TELEPORT 'X'


map<string, pair<int, double>> ConfigurationManagement::readConfig() {
    ifstream config("examples/gameFunctionalitySetup.txt");
    string line;
    while (getline(config, line)) {
        stringstream ss(line);
        string difficulty;
        getline(ss, difficulty, ':');
        int cooldown;
        ss >> cooldown;
        getline(ss, line, ':');  // discard ':'
        double speed;
        ss >> speed;
        difficultySettings[difficulty] = std::make_pair(cooldown, speed);
    }
    config.close();
    return difficultySettings;
}


vector<vector<char> > ConfigurationManagement::readMapFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open map file");
    }

    vector<vector<char> > game_map;
    string line;

    int pacmannumber = 0, ghostnumber = 0, points = 0, cherrys = 0, teleport_count = 0, apples = 0;;

    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        game_map.push_back(row);

        // Count the number of Pacman, Ghosts, Points, Cherrys and Teleports on the map
        for (int i = 0; i < row.size(); ++i) {
            char ch = row[i];
            if (ch == '<') {
                pacmannumber++;
            } else if ( ch == 'A' || ch == 'B' || ch == 'C') {
                ghostnumber++;
            } else if (ch == POINT) {
                points++;
            } else if (ch == CHERRY) {
                cherrys++;
            } else if (ch == APPLE) {
                apples++;
            } else if (ch == TELEPORT) {
                // Save the coordinates of the teleportation points
                teleport[teleport_count] = make_pair(game_map.size() - 1, i);
                teleport_count++;
                if (teleport_count > 2) {
                    throw runtime_error("The map must have exactly two teleportation points ('X')");
                }
            }
        }
    }
    if (pacmannumber != 1) {
        throw runtime_error("The map must have exactly one Pacman ('<')");
    }
    if (ghostnumber < 1 || ghostnumber > 3) {
        throw runtime_error("The map must have between 1 and 3 ghosts ('A', 'B', 'C')");
    }
    if (teleport_count == 2) {
        teleport_exists = true;
    } else if (teleport_count > 0) {
        throw runtime_error("The map must have exactly two teleportation points ('X')");
    }
    totalPoints = points;
    totalCherries = cherrys;
    return game_map;
}

//getters
bool ConfigurationManagement::getTeleportExists() const {
    return teleport_exists;
}

pair<int, int> *ConfigurationManagement::getTeleport() {
    return teleport;
}

int ConfigurationManagement::getTotalCherries() const {
    return totalCherries;
}

int ConfigurationManagement::getTotalPoints() const {
    return totalPoints;
}

void ConfigurationManagement::saveCurrentScore(const string &filename, const string &game_tag, int score) {
    vector<ConfigurationManagement::ScoreEntry> scores = readHighScores(filename);

    // If there are less than 10 scores or the last score is lower than the current score, add the current score
    if (scores.size() < 10 || scores.back().score < score) {
        scores.push_back({game_tag, score});

        // Sort the scores by score in descending order
        sort(scores.begin(), scores.end(),
             [](const ConfigurationManagement::ScoreEntry &a, const ConfigurationManagement::ScoreEntry &b) {
                 return a.score > b.score;
             });

        if (scores.size() > 10) {
            scores.pop_back();
        }

        writeHighScores(filename, scores);
    }
}

vector<ConfigurationManagement::ScoreEntry> ConfigurationManagement::readHighScores(const string &filename) {
    ifstream file(filename);
    vector<ScoreEntry> scores;
    string line;

    // Read the scores from the file
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

void ConfigurationManagement::writeHighScores(const string &filename,
                                              const vector<ConfigurationManagement::ScoreEntry> &scores) {
    ofstream file(filename);

    // Write the scores to the file
    for (const auto &entry: scores) {
        file << entry.game_tag << " " << entry.score << endl;
    }
}

void ConfigurationManagement::displayScoreBoard(WINDOW *win, const string &scoreboard) {
    //The following lines display the scoreboard
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s", scoreboard.c_str());
    wrefresh(win);
}

string ConfigurationManagement::getScoreBoard(const string &filename) {
    vector<ScoreEntry> scores = readHighScores(filename);

    // Create a string representation of the score board
    stringstream ss;
    ss << "SCORE BOARD\n";
    for (int i = 0; i < scores.size(); i++) {
        ss << i + 1 << ". " << scores[i].game_tag << ": " << scores[i].score << "\n";
    }
    return ss.str();
}
