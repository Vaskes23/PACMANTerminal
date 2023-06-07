//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CTAKE_H
#define PA2_PACMAN_CTAKE_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "../CPacManGame.h"

/**
 * \brief Class that controls what the game does when certain objects collide in the game.
 */
class CTake: public CPacManGame{
public:
    /**
     * \brief Default constructor.
     */
    CTake();

    /**
     * \brief Destructor.
     */
    ~CTake();

    /**
     * \brief Calculates the distance for a collider around object.
     *
     * \param[in] x - X coordinate of first object
     * \param[in] y - Y coordinate of first object
     * \param[in] x1 - X coordinate of second object
     * \param[in] y1 - Y coordinate of second object
     * \return Distance between two objects
     */
    int colliderDist(int x, int y, int x1, int y1);

    /**
     * \brief Counts how many spaces are in the ascii map (the places where the player can move).
     *
     * \param[in] spacesCount - Current count of spaces
     * \return Updated count of spaces
     */
    int checkSpacesCount(int spacesCount);

    /**
     * \brief Checks how many points and fruits are in the map also checks if is more than 0.
     *
     * \param[in] eadiblesCount - Current count of edible items
     * \return Updated count of edible items
     */
    int checkEadiblesCount(int eadiblesCount);

    /**
     * \brief Adds points to the player's score. One point for a point, or ten points for a fruit.
     *
     * \param[in] score - Current score
     * \return Updated score
     */
    int gainScore(int score);

private:
private:
    int x; /**< X coordinate of the first object */
    int y; /**< Y coordinate of the first object */
    int x1; /**< X coordinate of the second object */
    int y1; /**< Y coordinate of the second object */
    int spacesCount; /**< Current count of spaces in the ascii map */
    int eadiblesCount; /**< Current count of edible items in the map */
    int score; /**< Current score of the player */
};

#endif //PA2_PACMAN_CTAKE_H
