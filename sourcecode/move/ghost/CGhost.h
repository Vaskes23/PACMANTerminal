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

    /**
    * @brief This function is used to move the ghost on the map
     * @param game_map is the map on which the ghost is moving
     * @param cherryEaten is a boolean value that tells us if the cherry was eaten or not
    */
    void moveGhost(std::vector<std::vector<char>>& game_map, bool cherryEaten);

    /**
    * @brief This function is used to reset the position of the ghost
    */
    void resetPosition();

    int x;
    int y;
protected:

    int getNewDirection(vector<vector<char>>& game_map, int& new_x, int& new_y, char& newChar);
    void getStuck(int& new_x, int& new_y, char& newChar, vector<vector<char>>& game_map);

    int lastDirection;
    char previousChar;
    int initialX;
    int initialY;
};

#endif //PA2_PACMAN_CGHOST_H