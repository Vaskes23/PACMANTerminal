//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CCHERRY_H
#define PA2_PACMAN_CCHERRY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "./CFruit.h"

using namespace std;

/**
 * \class CCherry
 * \brief This class is used to handle the cherry's behavior in the game.
 */
class CCherry : public CFruit {
public:

    /**
     * \brief This function is used to activate the effect of the cherry
     * \return boolean indicating success of the operation
     */
    bool activateEffect() override;

    /**
     * \brief This function is used to deactivate the effect of the cherry
     * \return boolean indicating success of the operation
     */
    bool deactivateEffect() override;

    /**
     * \brief This function is used to set the appearance of the cherry in the game
     */
    void fruitAppearance() override;

    /**
     * \brief This function sets the skill definition for the ability that the cherry will give to the player.
     * In this case, the player will be able to eat ghosts.
     */
    void skillDefinition() override;
};


#endif //PA2_PACMAN_CCHERRY_H

