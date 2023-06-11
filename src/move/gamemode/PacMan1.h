//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_PACMAN1_H
#define PA2_PACMAN_PACMAN1_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "./CGameMode.h"

using namespace std;

/**
 * \class PacMan1
 * \brief A class that inherits from CGameMode and represents a specific type of pacman.
 */
class PacMan1 : public CGameMode {
public:

    /**
     * \brief Constructor for PacMan1.
     */
    PacMan1();

    /**
     * \brief Destructor for PacMan1.
     */
    ~PacMan1();

    /**
     * \brief Overridden function from CGameMode that sets the specific appearance of the pacman.
     */
    void pacmanAppereance() override;
};

#endif //PA2_PACMAN_PACMAN1_H