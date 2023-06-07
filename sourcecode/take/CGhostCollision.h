//
// Created by Matyas Vascak on 12.05.2023.
//

#ifndef PA2_PACMAN_CGHOSTCOLLISION_H
#define PA2_PACMAN_CGHOSTCOLLISION_H

#include "CTake.h"
#include "../CPacManGame.h"

/**
 * \class CGhostCollision
 * \brief This class handles the collisions between Pacman and ghosts in the game
 */
class CGhostCollision : CTake {

    /**
     * \brief This function is called when Pacman collides with a ghost, it removes one life
     * \param oneLive[in] - The amount of lives to be removed
     * \return The updated life count
     */
    int removeLive(int oneLive);

    /**
     * \brief This function is called when Pacman collides with a ghost. It resets the positions of Pacman and the ghosts, but keeps the score and other variables
     * \param hit[in] - Boolean value indicating if a collision occurred
     */
    void resetPosition(bool hit);

private:
    bool hit; /**< Boolean value indicating if a collision occurred */
    int oneLive; /**< The amount of lives to be removed */
};

#endif //PA2_PACMAN_CGHOSTCOLLISION_H
