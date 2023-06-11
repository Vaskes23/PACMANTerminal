//
// Created by Matyas Vascak on 11.06.2023.
//

#ifndef PA2_PACMAN_CONFIGURATIONMANAGEMENT_H
#define PA2_PACMAN_CONFIGURATIONMANAGEMENT_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <map>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <memory>

#include <ncurses.h>

//#include "CMove.h"

using namespace std;

/**
 * \class ConfigurationManagement
 * \brief This class is used to manage the configuration of the game.
 */
class ConfigurationManagement {
public:

    /**
     * \brief This function is read the configuration file of the pacman game.
     */
    map<string, pair<int, double>> readConfig();

    /**
    * \brief This function reads the map from a file.
    * \param filename[in] - The name of the file
    */
    vector<vector<char> > readMapFromFile(const string &filename);

    /**
     * \brief This function is used to get the difficulty settings.
     * \return The map of the difficulty settings
     */
    bool getTeleportExists() const;

    /**
     * \brief This function is used to get the difficulty settings.
     * \return The map of the difficulty settings
     */
    pair<int, int>* getTeleport();

    /**
     * \brief This function is used to get the difficulty settings.
     * \return The map of the difficulty settings
     */
    int getTotalCherries() const;

    /**
     * \brief This function is used to get the difficulty settings.
     * \return The map of the difficulty settings
     */
    int getTotalPoints() const;


//    /**
//     * @brief This function saves the current score to the high scores file.
//     * @param filename[in] - The name of the high scores file
//     * @param game_tag[in] - The tag of the game
//     * @param score[in] - The score of the game
//     */
//    void saveCurrentScore(const string &filename, const string &game_tag, int score);


protected:
    map<string, pair<int, double>> difficultySettings; /**< The map of the difficulty settings */
    bool teleport_exists = false; /**< The boolean which tells if the teleport exists */
    int totalCherries = 0; /**< The total number of cherries in the game */
    int totalPoints = 0; /**< The total number of points in the game */
    pair<int, int> teleport[2]; /**< The teleport coordinates */

};


#endif //PA2_PACMAN_CONFIGURATIONMANAGEMENT_H
