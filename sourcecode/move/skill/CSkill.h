//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CSKILL_H
#define PA2_PACMAN_CSKILL_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "../CMove.h"

using namespace std;

/**
 * \class CSkill
 * \brief This class is the parent class for all the ghosts and it describes all the skills that the ghosts can use interchangeably.
 */
class CSkill: CMove {

public:
    /**
     * \brief This function is used for the ghosts when we choose easy difficulty and it makes the ghosts move randomly on the
     * map it is also used when the ghosts are in the frightened state and run from pacman
     */
    void randomMovement();

    /**
     * \brief This function is used for scatter movement and is used once in while in the game for the player to get some breathing
     * room it makes the ghosts move to the corners of the map
     */
    void scatterMovement();

    /**
     * \brief When this function is called the ghosts will start chasing the player but each of them will do it differently
     * depending on their particular chasing style
     */
    void chasePacManMovement();

    /**
     * \brief This function is used when the ghosts are eaten by the pacman and they are going back to the ghost house to respawn
     */
    void eatenGoHome();

    /**
     * \brief This function describes each of the ghosts chasing style and is overridden in the child classes
     */
    virtual void followingStyle();
};
#endif //PA2_PACMAN_CSKILL_H
