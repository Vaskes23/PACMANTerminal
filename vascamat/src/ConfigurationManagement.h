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

/**
 * \@file ConfigurationManagement.h Is responsible for the configuration of the game.
 */


/**
 * \class ConfigurationManagement
 * \brief This class is used to manage the configuration of the game.
 */
class ConfigurationManagement {
public:

    /**
     * @brief This struct represents an entry in the high scores file.
     * @param game_tag[in] - The tag of the game
     * @param score[in] - The score of the game
     */
    struct ScoreEntry {
        std::string game_tag;
        int score;
    };

    /**
     * \brief This function is read the configuration file of the pacman game.
     * \return Configuration data
     */
    std::map<std::string, std::pair<int, double>> readConfig();

    /**
    * \brief This function reads the map from a file.
    * \param filename[in] - The name of the file
     * \return The map of the game
    */
    std::vector<std::vector<char> > readMapFromFile(const std::string &filename);

    /**
     * \brief This function is used to get the difficulty settings.
     * \return The map of the difficulty settings
     */
    bool getTeleportExists() const;

    /**
     * \brief This function is used to get the difficulty settings.
     * \return The map of the difficulty settings
     */
    std::pair<int, int> *getTeleport();

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


    /**
     * @brief This function saves the current score to the high scores file.
     * @param filename[in] - The name of the high scores file
     * @param game_tag[in] - The tag of the game
     * @param score[in] - The score of the game
     */
    void saveCurrentScore(const std::string &filename, const std::string &game_tag, int score);


    /**
     * @brief This function reads the high scores from the high scores file.
     * @param filename[in] - The name of the high scores file
     * @return The vector of high scores
     */
    std::vector<ScoreEntry> readHighScores(const std::string &filename);

    /**
     * @brief This function writes the high scores to the high scores file.
     * @param filename[in] - The name of the high scores file
     * @param scores[in] - The vector of high scores
     */
    void writeHighScores(const std::string &filename, const std::vector<ScoreEntry> &scores);

    /**
     * \brief This function is used to display the scoreboard.
     * \param win[in] - The window in which the scoreboard will be displayed
     * \param scoreboard[in] - The scoreboard that will be displayed
     */
    void displayScoreBoard(WINDOW *win, const std::string &scoreboard);

    /**
    * @brief This function displays the high scores.
     * @param filename[in] - The name of the high scores file
     * @return The string of the high scores
    */
    std::string getScoreBoard(const std::string &filename);


protected:
    std::map<std::string, std::pair<int, double>> difficultySettings; /**< The map of the difficulty settings */
    bool teleport_exists = false; /**< The boolean which tells if the teleport exists */
    int totalCherries = 0; /**< The total number of cherries in the game */
    int totalPoints = 0; /**< The total number of points in the game */
    std::pair<int, int> teleport[2]; /**< The teleport coordinates */
};


#endif //PA2_PACMAN_CONFIGURATIONMANAGEMENT_H
