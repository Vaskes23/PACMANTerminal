//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CPRINT_H
#define PA2_PACMAN_CPRINT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

#include <ncurses.h>

/**
 * \class CPrint
 * \brief This class is used to handle the printing of various game elements in the PacMan game.
 */
class CPrint{
public:
    /**
    * \brief This function is used to print the map of the game.
     * \param win[in] - The window in which the map will be printed
     * \param game_map[in] - The map of the game stored in vector
     * \param displayed_map[in] - The map of the game that will be displayed
     * \param game_tag[in] - The tag of the game player
     * \param cherrysEaten[in] - The number of cherrys eaten by the player
 */
    void displayMap(WINDOW *win, const std::vector<std::vector<char> > &game_map,
                    const std::vector<std::vector<char> > &displayed_map,
                    std::string game_tag, int cherrysEaten, int pointsEaten, int pacmanLives);


    /**
    * \brief This function is used to get the players game tag.
    * \param game_tag[in] - The tag of the game player
     * \return The tag of the game player
    */
    std::string askGameTag(std::string &game_tag);

    /**
    * \brief This function creates a new window.
     * \param height[in] - The height of the window
     * \param width[in] - The width of the window
     * \param starty[in] - The starting Y coordinate of the window
     * \param startx[in] - The starting X coordinate of the window
    */
    WINDOW *create_newwin(int height, int width, int starty, int startx);

    /**
    * \brief This function is used to destroy a window.
    */
    void destroy_win(WINDOW *local_win);

    /**
     * \brief This function is used to display the scoreboard.
     * \param win[in] - The window in which the scoreboard will be displayed
     * \param scoreboard[in] - The scoreboard that will be displayed
     */
    void displayScoreBoard(WINDOW *win, const std::string &scoreboard);
};

#endif //PA2_PACMAN_CPRINT_H
