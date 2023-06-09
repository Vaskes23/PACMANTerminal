//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CMOVE_H
#define PA2_PACMAN_CMOVE_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <random>

#include <ncurses.h>

#include "../CPacManGame.h"
#include "../print/CPrint.h"
#include "ghost/CGhost.h"

class Ghost; // Forward declaration of Ghost

/**
 * \class CMove
 * \brief This class controls how the entities in the game move.
 */
class CMove : public CPacManGame {
public:
    /**
    * \brief This function initializes the window and curses.
     * \param height[in] - The height of the window
     * \param width[in] - The width of the window
     * \param starty[in] - The starting Y coordinate of the window
     * \param startx[in] - The starting X coordinate of the window
    */
    void initializeWindowAndCurses(int &height, int &width, int &starty, int &startx);

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
    * \brief This function reads the map from a file.
    * \param filename[in] - The name of the file
    */
    vector<vector<char> > readMapFromFile(const string &filename);

    /**
    * \brief This function finds the initial position of the pacman.
     * \param gameMap[in] - The map of the game stored in a vector of vectors of chars
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
                                         char &pacman_char, vector<unique_ptr<Ghost>>& ghosts);

    /**
     * @brief This struct represents an entry in the high scores file.
     */
    struct ScoreEntry {
        string game_tag;
        int score;
    };

    /**
     * @brief This function saves the current score to the high scores file.
     * @param filename[in] - The name of the high scores file
     * @param game_tag[in] - The tag of the game
     * @param score[in] - The score of the game
     */
    void saveCurrentScore(const string &filename, const string &game_tag, int score);

    /**
     * @brief This function reads the high scores from the high scores file.
     * @param filename[in] - The name of the high scores file
     */
    vector<ScoreEntry> readHighScores(const string &filename);

    /**
     * @brief This function writes the high scores to the high scores file.
     * @param filename[in] - The name of the high scores file
     * @param scores[in] - The vector of high scores
     */
    void writeHighScores(const string &filename, const vector<ScoreEntry> &scores);


    /**
    * @brief This function displays the high scores.
     * @param filename[in] - The name of the high scores file
    */
    string getScoreBoard(const string &filename);

    /**
    * @brief This function displays the end game message.
     * @param isWinner[in] - The boolean which tells if the player won the game
    */
    void displayEndGameMessage(bool isWinner);

    /**
    * @brief This function resets the pacman position.
     * @param x[in] - The X coordinate of the pacman
     * @param y[in] - The Y coordinate of the pacman
     * @param displayedMap[in] - The map of the game displayed in a vector of vectors of chars
     * @param pacmanChar[in] - The char which represents the pacman
    */
    void resetPacmanPosition(int &x, int &y, vector<vector<char> > &displayedMap, char &pacmanChar);

private:
    int totalCherries = 0;
    int totalPoints = 0;
};


#endif //PA2_PACMAN_CMOVE_H