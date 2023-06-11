//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_PACMAN0_H
#define PA2_PACMAN_PACMAN0_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>

#include <ncurses.h>

#include "./CGameMode.h"

using namespace std;

/**
 * \class PacMan0
 * \brief A class that inherits from CGameMode and represents a specific type of pacman.
 */
class PacMan0 : public CGameMode {
public:

    /**
     * \brief Constructor for PacMan0.
     */
    PacMan0();

    /**
     * \brief Destructor for PacMan0.
     */
    ~PacMan0();

    /**
     * \brief Overridden function from CGameMode that sets the specific appearance of the pacman.
     */
    void pacmanAppereance() override;
};

#endif //PA2_PACMAN_PACMAN0_H