//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CUIMENU_H
#define PA2_PACMAN_CUIMENU_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <ncurses.h>

#include "CPrint.h"
#include "ConfigurationManagement.h"

using namespace std;

/**
 * \class CUIMenu
 * \brief This class is used to handle the printing of various game elements in the PacMan game.
 */
class CUIMenu {

public:
    /**
    * \brief This function is used to print the pause menu.
    * \param win[in] - The window in which the map will be printed
    * \param highlight[in] - The number of the highlighted option
    */
    void displayPauseMenu(WINDOW *win, int highlight);

    /**
    * \brief This function initializes the window and curses.
     * \param height[in] - The height of the window
     * \param width[in] - The width of the window
     * \param starty[in] - The starting Y coordinate of the window
     * \param startx[in] - The starting X coordinate of the window
    */
    void initializeWindowAndCurses(int &height, int &width, int &starty, int &startx);

    /**
    * \brief This function is used to print the main menu.
    * \param win[in] - The window in which the map will be printed
    * \param highlight[in] - The number of the highlighted option
    */
    void displayMenu(WINDOW *win, int highlight);

    /**
     * \brief This function is used to print the settings menu.
     * \param win[in] - The window in which the map will be printed
     * \param highlight[in] - The number of the highlighted option
     */
    void displaySettingsMenu(WINDOW *win, int highlight);

    /**
    * \brief This function is used to print the main menu on the screen.
     * \return The selected option
    */
    string mainMenu();

    /**
     * \brief This function handles the interaction with the settings menu.
     * \return The selected option
     */
    string settingsMenu();
};

#endif //PA2_PACMAN_CUIMENU_H
