//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CAPPLE_H
#define PA2_PACMAN_CAPPLE_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "./CFruit.h"

using namespace std;

/**
 * \class CApple
 * \brief This class is used to handle the apple's behavior in the game.
 */
class CApple : public CFruit {
public:

    /**
    * \brief This function is used to activate the effect of the apple
    * \return boolean indicating success of the operation
    */
    bool activateEffect() override;

    /**
    * \brief This function is used to deactivate the effect of the apple
    * \return boolean indicating success of the operation
    */
    bool deactivateEffect() override;

    /**
    * \brief This function is used to set the appearance of the apple in the game
    */
    void fruitAppearance() override;

    /**
    * \brief This function sets the ghost definition for the ability that the banana will give to the player.
    * In this case, the player will gain another extra life.
    */
    void skillDefinition() override;
};


#endif //PA2_PACMAN_CAPPLE_H
