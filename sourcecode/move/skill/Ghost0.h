//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_GHOST0_H
#define PA2_PACMAN_GHOST0_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "./CSkill.h"

using namespace std;

/**
 * \class Ghost0
 * \brief This class overrides the virtual function from the CSkill class and by that defines how the ghost should behave
 */
class Ghost0 : public CSkill {
public:
    /**
     * \brief Constructor for Ghost0
     */
    Ghost0();

    /**
     * \brief Destructor for Ghost0
     */
    ~Ghost0();

    /**
     * \brief Overriding of the virtual function to suit the following style of ghost 0 (Pinky)
     */
    void followingStyle() override;
};


#endif //PA2_PACMAN_GHOST0_H