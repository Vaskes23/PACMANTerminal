//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CFRUIT_H
#define PA2_PACMAN_CFRUIT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "../CTake.h"
#include "../CGhostCollision.h"

using namespace std;

/**
 * \class CFruit
 * \brief This class is used to handle the fruit's behavior in the game.
 */
class CFruit: CTake {

    /**
     * \brief This function is used to activate the effect of the fruit
     * \return boolean indicating success of the operation
     */
    virtual bool activateEffect();

    /**
     * \brief This function is used to deactivate the effect of the fruit
     * \return boolean indicating success of the operation
     */
    virtual bool deactivateEffect();

    /**
     * \brief This function is used to set the appearance of the fruit in the inheriting classes
     */
    virtual void fruitAppearance();

    /**
     * \brief This function is used to set the definition of the ability that the specific fruit will give to the player in the inheriting classes
     */
    virtual void skillDefinition();

    /**
     * \brief This function is used to set the timer for the effect of the fruit
     * \param timeLeft[in] - time left for the effect
     */
    void effectTimer(int timeLeft);

    /**
     * \brief This function is used for adding of points to the score (in this case adding by 1 for every point eaten by pacman)
     * \param fruit[in] - the number of points to be added to the score
     * \return Updated score
     */
    int gainScore(int fruit);

    /**
     * \brief This function will return true if pacman had eaten all the points on the map we counted in the class Ctake using checkEadiblesCount() function
     * \param fruit[in] - the number of fruits to be checked
     * \return Number of edibles left
     */
    int checkEadiblesCount(int fruit);

private:
    int fruit; /**< The fruit count */
    int timeLeft; /**< Time left for the fruit effect */
    int ediblesCount; /**< Count of edibles in the game */
};

#endif //PA2_PACMAN_CFRUIT_H
