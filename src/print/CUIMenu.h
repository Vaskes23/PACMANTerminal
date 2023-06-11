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

#include "./CPrint.h"

using namespace std;

/**
 * \class CUIMenu
 * \brief This class is used to handle the User Interface Menu in the PacMan game.
 */
class CUIMenu : public CPrint {
public:

    /**
    * \brief Default constructor.
    */
    CUIMenu();

    /**
    * \brief Default destructor.
    */
    ~CUIMenu();

    /**
     * \brief This function is used to show the game menu.
     * \param gameStarted[in] - Boolean indicating if the game has started
     */
    void displayMenu(bool gameStarted);

    /**
     * \brief This function is used to pause the game.
     * \param paused[in] - Boolean indicating if the game is paused
     */
    void pauseGame(bool paused);

    /**
     * \brief This function is used to show the pause menu when the game is paused.
     */
    void displayPauseMenu();

    /**
     * \brief This function is used to show the buttons in the menu and in the pause menu.
     */
    void displayButtons();

    /**
     * \brief This function allows us to switch between different buttons in the menu and in the pause menu.
     * \param buttonIndex[in] - The index of the button to switch to
     */
    void moveBetweenMenus(int buttonIndex);

private:
    bool gameStarted; /**< Boolean indicating if the game has started */
    bool paused; /**< Boolean indicating if the game is paused */
    int buttonIndex; /**< The index of the current button in the menu */
};

#endif //PA2_PACMAN_CUIMENU_H
