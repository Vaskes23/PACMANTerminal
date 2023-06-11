//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CGAMEMODE_H
#define PA2_PACMAN_CGAMEMODE_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "../CMove.h"

/**
 * \class CGameMode
 * \brief This class controls how the game is setup and how the game is played.
 */
class CGameMode : public CMove {

    /**
     * \brief Default constructor for CGameMode
     */
    CGameMode();

    /**
     * \brief Destructor for CGameMode
     */
    ~CGameMode();

    /**
     * \brief This function is used to check if there is only one player in the game, and if so, it starts a singleplayer mode.
     * \param pacman[in] - Instance of CGameMode representing the pacman
     * \return boolean indicating if the game is in singleplayer mode
     */
    bool singleplayer(CGameMode *pacman);

    /**
     * \brief This function is used to check if there are two players in the game, and if so, it starts a multiplayer mode.
     * \param pacman[in] - First instance of CGameMode representing the first pacman
     * \param pacman1[in] - Second instance of CGameMode representing the second pacman
     * \return boolean indicating if the game is in multiplayer mode
     */
    bool multiplayer(CGameMode *pacman, CGameMode *pacman1);

    /**
     * \brief This function takes the input from the player and moves the player based on the input.
     * It also checks if the inputs are correct (if the player is pushing the correct buttons so that it won't break the game)
     * \param key0[in] - key input 0
     * \param key1[in] - key input 1
     * \param key2[in] - key input 2
     * \param key3[in] - key input 3
     */
    void playerControlsInput(int key0, int key1, int key2, int key3);

    /**
    * \brief This function takes the input from the player and moves the player based on the input.
    * It also checks if the inputs are correct (if the player is pushing the correct buttons so that it won't break the game)
    * \param key0[in] - key input 0
    * \param key1[in] - key input 1
    * \param key2[in] - key input 2
    * \param key3[in] - key input 3
    * \param key4[in] - key input for econd player 0
    * \param key6[in] - key input for econd player 1
    * \param key6[in] - key input for econd player 2
    * \param key7[in] - key input for econd player 3
    */
    void playerControlsInput(int key0, int key1, int key2, int key3, int key4, int key5, int key6, int key7);

    /**
     * \brief This function makes the animations of pacman eating (i.e. the mouth opening and closing) and changes the direction of the pacman
     * based on the input
     * \param direction[in] - direction of pacman
     */
    void pacmanAnimation(int direction);

    /**
    * \brief This function makes the animations of pacmans eating (i.e. the mouth opening and closing) and changes the direction of the pacmans
    * based on the input in a multiplayer setting
    * \param direction[in] - direction of pacman
 *  /
    void pacmanAnimation(int direction, int direction1);

    /**
     * \brief This polymorphic function is used to make the pacman appear in a certain way to make the game more interesting
     * and also when we have multiplayer to more easily distinguish between the two players
     */
    virtual void pacmanAppereance();

private:
    int key0; /**< Key input 0 */
    int key1; /**< Key input 1 */
    int key2; /**< Key input 2 */
    int key3; /**< Key input 3 */
    int key4; /**< Key input 4 */
    int key5; /**< Key input 5 */
    int key6; /**< Key input 6 */
    int key7; /**< Key input 7 */
    int direction; /**< Direction of pacman */
    int direction1; /**< Direction of second pacman in multiplayer */
};

#endif //PA2_PACMAN
