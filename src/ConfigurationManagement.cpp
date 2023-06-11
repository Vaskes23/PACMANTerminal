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

//CMove cMoveInstanceConfig;

map<string, pair<int, double>> ConfigurationManagement::readConfig() {
    ifstream config("../examples/gameFunctionalitySetup.txt");
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

        for (int i = 0; i < row.size(); ++i) {
            char ch = row[i];
            if (ch == '<') {
                pacmannumber++;
            } else if (ch == 'G') {
                ghostnumber++;
            } else if (ch == POINT) {
                points++;
            } else if (ch == CHERRY) {
                cherrys++;
            } else if (ch == APPLE) {
                apples++;
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
        throw runtime_error("The map must have exactly one Pacman ('<')");
    }
    if (ghostnumber < 1 || ghostnumber > 3) {
        throw runtime_error("The map must have between 1 and 3 ghosts ('G')");
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

bool ConfigurationManagement::getTeleportExists() const {
    return teleport_exists;
}

pair<int, int>* ConfigurationManagement::getTeleport() {
    return teleport;
}

int ConfigurationManagement::getTotalCherries() const {
    return totalCherries;
}

int ConfigurationManagement::getTotalPoints() const{
    return totalPoints;
}
