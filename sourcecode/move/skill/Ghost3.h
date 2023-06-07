//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_GHOST3_H
#define PA2_PACMAN_GHOST3_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "./CSkill.h"

using namespace std;

/**
 * \class Ghost3
 * \brief This class overrides the virtual function from the CSkill class and by that defines how the ghost should behave
 */
class Ghost3 : public CSkill {
public:
    /**
     * \brief Constructor for Ghost3
     */
    Ghost3();

    /**
     * \brief Destructor for Ghost3
     */
    ~Ghost3();

    /**
     * \brief Overriding of the virtual function to suit the following style of ghost 3 (Clyde)
     */
    void followingStyle() override;
};

#endif //PA2_PACMAN_GHOST3_H