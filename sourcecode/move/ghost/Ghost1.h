//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_GHOST1_H
#define PA2_PACMAN_GHOST1_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "./CGhost.h"

using namespace std;

/**
 * \class Ghost1
 * \brief This class overrides the virtual function from the CGhost class and by that defines how the ghost should behave
 */
class Ghost1 : public CGhost {
public:
    /**
     * \brief Constructor for Ghost1
     */
    Ghost1();

    /**
     * \brief Destructor for Ghost1
     */
    ~Ghost1();

    /**
     * \brief Overriding of the virtual function to suit the following style of ghost 1 (Blinky)
     */
    void followingStyle() override;
};

#endif //PA2_PACMAN_GHOST1_H