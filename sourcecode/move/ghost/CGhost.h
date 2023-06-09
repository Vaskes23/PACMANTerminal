//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CGHOST_H
#define PA2_PACMAN_CGHOST_H

#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <iostream>
#include <vector>


#include <ncurses.h>

#include "../CMove.h"

using namespace std;

/**
 * \class CGhost
 * \brief This class is the parent class for all the ghosts and it describes all the skills that the ghosts can use interchangeably.
 */
class Ghost {
public:
    Ghost(int startX, int startY, char startChar);

    void moveGhost(std::vector<std::vector<char>>& game_map);

    int x;
    int y;
private:
    int lastDirection;
    char previousChar;
};

#endif //PA2_PACMAN_CGHOST_H
