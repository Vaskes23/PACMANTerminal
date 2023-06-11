//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CPACMANGAME_H
#define PA2_PACMAN_CPACMANGAME_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <ncurses.h>

using namespace std;

/**
 * CPacManGame class connects all the other classes together and runs the game.
 */
class CPacManGame {

    /**
     * \brief Used to put the game to its basic (starting) state for a new game.
     */
    void refreshGame();

    /**
     * \brief Used to start the game, and it starts to call all the needed functions in their order.
     */
    void startGame();

    /**
     * \brief Used to pause the game and calls all the needed functions in their order to accomplish that.
     */
    void pauseGame();

    /**
     * \brief Used to end the game and calls all the needed functions in their order to accomplish that,
     * then returns back to the terminal.
     */
    void quitGame();

    /**
     * \brief Called to display the menu of the game either the pause menu or the main menu.
     */
    void displayMenu();

    /**
     * \brief Used to display the map of the game, it calls all the necessary functions to accomplish that.
     */
    void loadMap();

    /**
     * \brief Checks if the terminal window is big enough for the game to run properly.
     * If not, it then prompts the user to resize the window.
     */
    void windowSizeCheck();

    /**
     * \brief Displays the highscore of the players that played the game before and are saved in the highscore file.
     */
    void displayGameStats();

    /**
     * \brief Used to display the score and lives of the player in the right corner of the terminal window
     * while he plays the game.
     */
    void displayScore();

    /**
     * \brief Resets everything in the game except for the configuration files.
     * It sets everything to the first values so that the game can be played again.
     */
    void resetAllValues();
};

#endif //PA2_PACMAN_CPACMANGAME_H
