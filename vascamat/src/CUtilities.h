//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CUTILITIES_H
#define PA2_PACMAN_CUTILITIES_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <memory>

#include <ncurses.h>

#include "CPrint.h"
#include "CUIMenu.h"
#include "ConfigurationManagement.h"
#include "CGhost.h"

class Ghost;

using namespace std;

/**
 * \@file CUtilities.h is responsible for the movement of the entities in the game and functions that enable it.
 */

/**
 * \class CUtilities
 * \brief This class controls how the entities in the game move.
 */
class CUtilities : protected CUIMenu, protected CPrint {
public:

    /**
    * \brief This function initializes the pacman.
     * \param gameMap[in] - The map of the game stored in a vector of vectors of chars
     * \param displayedMap[in] - The map of the game displayed in a vector of vectors of chars
     * \param x[in] - The X coordinate of the pacman
     * \param y[in] - The Y coordinate of the pacman
     * \param currentDirection[in] - The current direction of the pacman
     * \param charIndex[in] - The index of the current direction of the pacman
     * \param pacman_chars_up[in] - The vector of chars which represent the pacman when it is moving up
     * \param pacman_chars_down[in] - The vector of chars which represent the pacman when it is moving down
     * \param pacman_chars_right[in] - The vector of chars which represent the pacman when it is moving right
     * \param pacman_chars_left[in] - The vector of chars which represent the pacman when it is moving left
     * \param pacmanChar[in] - The char which represents the pacman
    */
    void initializePacman(vector<vector<char> > &gameMap, vector<vector<char> > &displayedMap, int &x, int &y,
                          vector<char> *&currentDirection, int &charIndex,
                          vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                          vector<char> &pacman_chars_right,
                          vector<char> &pacman_chars_left, char &pacmanChar);


    /**
    * \brief This function finds the initial position of the pacman.
     * \param gameMap[in] - The map of the game stored in a vector of vectors of chars
     * \return The initial position of the pacman
    */
    pair<int, int> findPacmanInitialPosition(const vector<vector<char> > &gameMap);

    /**
    * \brief This function handles the teleportation of the pacman.
     * \param new_x[in] - The new X coordinate of the pacman
     * \param new_y[in] - The new Y coordinate of the pacman
     * \param game_map[in] - The map of the game stored in a vector of vectors of chars
     * \param current_direction[in] - The current direction of the pacman
     * \param pacman_chars_up[in] - The vector of chars which represent the pacman when it is moving up
     * \param pacman_chars_down[in] - The vector of chars which represent the pacman when it is moving down
     * \param pacman_chars_right[in] - The vector of chars which represent the pacman when it is moving right
     * \param pacman_chars_left[in] - The vector of chars which represent the pacman when it is moving left
    */
    void
    handleTeleportation(int &new_x, int &new_y, const vector<vector<char> > &game_map, vector<char> *&current_direction,
                        vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                        vector<char> &pacman_chars_right,
                        vector<char> &pacman_chars_left);


    /**
    * \brief This function handles the input from the user.
     * \param ch[in] - The current character
     * \param last_ch[in] - The last character
     * \param paused[in] - The boolean which tells if the game is paused
     * \param pause_win[in] - The window which is displayed when the game is paused
     * \param highlight[in] - The index of the highlighted option in the pause menu
     * \param gameTag[in] - The tag of the player
     * \param score[in] - The score of the game
    */
    void handleInput(int &ch, int &last_ch, bool &paused, WINDOW *pause_win, int &highlight, const string &gameTag,
                     int &score);


    /**
    * \brief This function starts the game.
     * \param x[in] - The X coordinate of the pacman
     * \param y[in] - The Y coordinate of the pacman
     * \param gameMap[in] - The map of the game stored in a vector of vectors of chars
     * \param displayedMap[in] - The map of the game displayed in a vector of vectors of chars
     * \param currentDirection[in] - The current direction of the pacman
     * \param charIndex[in] - The index of the current direction of the pacman
     * \param pacman_chars_up[in] - The vector of chars which represent the pacman when it is moving up
     * \param pacman_chars_down[in] - The vector of chars which represent the pacman when it is moving down
     * \param pacman_chars_right[in] - The vector of chars which represent the pacman when it is moving right
     * \param pacman_chars_left[in] - The vector of chars which represent the pacman when it is moving left
     * \param pacmanChar[in] - The char which represents the pacman
     * \param gameTag[in] - The tag of the game
    */
    void startGame(int &x, int &y, vector<vector<char> > &gameMap,
                   vector<vector<char> > &displayedMap, vector<char> *&currentDirection, int &charIndex,
                   vector<char> &pacman_chars_up, vector<char> &pacman_chars_down, vector<char> &pacman_chars_right,
                   vector<char> &pacman_chars_left, char &pacmanChar, const string &gameTag);

    /**
     * @brief This function handles the movement logic of the game.
     * @param new_x[in] - The new X coordinate of the pacman
     * @param new_y[in] - The new Y coordinate of the pacman
     * @param last_ch[in] - The last character
     * @param game_map[in] - The map of the game stored in a vector of vectors of chars
     * @param current_direction[in] - The current direction of the pacman
     * @param pacman_chars_up[in] - The vector of chars which represent the pacman when it is moving up
     * @param pacman_chars_down[in] - The vector of chars which represent the pacman when it is moving down
     * @param pacman_chars_right[in] - The vector of chars which represent the pacman when it is moving right
     * @param pacman_chars_left[in] - The vector of chars which represent the pacman when it is moving left
     */
    void handleLogic(int &new_x, int &new_y, int &last_ch, const vector<vector<char> > &game_map,
                     vector<char> *&current_direction,
                     vector<char> &pacman_chars_up, vector<char> &pacman_chars_down,
                     vector<char> &pacman_chars_right,
                     vector<char> &pacman_chars_left);


    /**
     * @brief This function handles the score and updates the maps.
     * @param new_x[in] - The new X coordinate of the pacman
     * @param new_y[in] - The new Y coordinate of the pacman
     * @param x[in] - The X coordinate of the pacman
     * @param y[in] - The Y coordinate of the pacman
     * @param game_map[in] - The map of the game stored in a vector of vectors of chars
     * @param displayed_map[in] - The map of the game displayed in a vector of vectors of chars
     * @param char_index[in] - The index of the current direction of the pacman
     * @param current_direction[in] - The current direction of the pacman
     * @param pacman_char[in] - The char which represents the pacman
     * @param ghosts[in] - The unique vector of ghosts
     */
    void handleScoreAndUpdateMaps(int &new_x, int &new_y, int &x, int &y, vector<vector<char> > &game_map,
                                  vector<vector<char> > &displayed_map, int &char_index,
                                  vector<char> *&current_direction,
                                  char &pacman_char, vector<unique_ptr<Ghost>> &ghosts);


    /**
    * @brief This function displays the end game message.
     * @param isWinner[in] - The boolean which tells if the player won the game
     * @param gameTag[in] - The tag of the game
     * @param score[in] - The score of the game
    */
    void displayEndGameMessage(bool isWinner, const string &gameTag, int score);

    /**
    * @brief This function resets the pacman position.
     * @param x[in] - The X coordinate of the pacman
     * @param y[in] - The Y coordinate of the pacman
     * @param displayedMap[in] - The map of the game displayed in a vector of vectors of chars
     * @param pacmanChar[in] - The char which represents the pacman
    */
    void resetPacmanPosition(int &x, int &y, vector<vector<char> > &displayedMap, char &pacmanChar);


    /**
    * @brief This function resets the game.
     * @param gameMap[in] - The map of the game stored in a vector of vectors of chars
     * @param displayedMap[in] - The map of the game displayed in a vector of vectors of chars
     * @param x[in] - The X coordinate of the pacman
     * @param y[in] - The Y coordinate of the pacman
     * @param currentDirection[in] - The current direction of the pacman
     * @param charIndex[in] - The index of the current direction of the pacman
     * @param pacman_chars_up[in] - The vector of chars which represent the pacman when it is moving up
     * @param pacman_chars_down[in] - The vector of chars which represent the pacman when it is moving down
     * @param pacman_chars_right[in] - The vector of chars which represent the pacman when it is moving right
     * @param pacman_chars_left[in] - The vector of chars which represent the pacman when it is moving left
     * @param pacmanChar[in] - The char which represents the pacman
    */
    void resetGame(vector<vector<char> > &gameMap, vector<vector<char> > &displayedMap,
                   int &x, int &y, vector<char> *&currentDirection, int &charIndex,
                   vector<char> &pacman_chars_up, vector<char> &pacman_chars_down, vector<char> &pacman_chars_right,
                   vector<char> &pacman_chars_left, char &pacmanChar);


private:
    double defaultMoveDelay; /**< The default move delay */
    int cherrysEaten, pointsEaten, pacmanLives = 3; /**< The number of cherries eaten, points eaten and pacman lives */
    long cherryEatenTimestamp; /**< The timestamp of the cherry eaten */
    bool cherryEaten = false; /**< The boolean which tells if the cherry was eaten */
    pair<int, int> pacmanInitPos; /**< The initial pacman coordinates */
    map<string, pair<int, double>> difficultySettings; /**< The map of the difficulty settings */
    int ghostPoints = 0; /**< The number of points for eating a ghost */
    int abilityTime; /**< The time of the ability */
};


#endif //PA2_PACMAN_CUTILITIES_H