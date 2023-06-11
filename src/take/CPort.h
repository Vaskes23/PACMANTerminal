//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CPORT_H
#define PA2_PACMAN_CPORT_H

#include "CTake.h"
#include "../CPacManGame.h"

/**
 * \class CPort
 * \brief This class is used for the teleports in the game
 */
class CPort : public CTake{
public:
    /**
    * \brief Default constructor.
    */
    CPort();

    /**
    * \brief Destructor.
    */
    ~CPort();

    /**
     * \brief Checks the number of teleport in the ascii map. If it's not an even number it will throw an error
     * \param portCount[in] - Number of ports present in the map
     */
    void checkNumberOfPorts(int portCount);


    /**
     * \brief Changes the location of the player or of the ghosts that get in the teleport
     * \param entity[in] - The game entity (player or ghost) to be teleported
     * \param x[in], y[in], x1[in], y1[in], x2[in], y2[in], x3[in], y3[in] - Coordinates used for teleporting the entity
     */
    void portChangeLocation(CPacManGame *entity, int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);


    /**
     * \brief Changes the direction of the entity in case that the teleport would end in a different direction
     * \param entity[in] - The game entity (player or ghost) whose direction is to be changed
     * \param x[in], y[in], x1[in], y1[in], x2[in], y2[in], x3[in], y3[in] - Coordinates used for changing the direction of the entity
     */
    void portChangeDirection(CPacManGame *entity, int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);

private:
    int portCount; /**< Count of teleportation ports present in the game */
};

#endif //PA2_PACMAN_CPORT_H
