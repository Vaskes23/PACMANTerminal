//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CSCORE_H
#define PA2_PACMAN_CSCORE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <ncurses.h>

#include "./CData.h"

using namespace std;

/**
 * \class CScore
 * \brief This class handles the scores of the PacMan game.
 */
class CScore : public CData {
public:

    /**
    * \brief Default constructor.
    */
    CScore();

    /**
    * \brief Default destructor.
    */
    ~CScore();

    /**
     * \brief This function is used to save the high score to the file it also checks if the score is higher than the previous ones.
     * \param file[in] - the score file to save to.
     */
    void saveHighScoreToFile(CScore *file);

    /**
     * \brief This function is used to read the high score from the file to be compares with the current score.
     * \param file[in] - the score file to read from.
     */
    void readHighScoreFromFile(CScore *file);

    /**
     * \brief This function is used to get the high score players from the file.
     * \param file[in] - the score file to read from.
     */
    void getHighScorePlayers(CScore *file);

    /**
     * \brief This function is used to display the high score players from the file in a table.
     * \param file[in] - the score file to read from.
     */
    void displayHighScorePlayers(CScore *file);
};

#endif //PA2_PACMAN_CSCORE_H
