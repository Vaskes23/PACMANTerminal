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
#include <queue>
#include <random>
#include <algorithm>

#include <ncurses.h>


#define WALL '#'
#define TELEPORT 'X'
#define EMPTY_SPACE ' '
using namespace std;



/**
 * \@file CGhost.h Is responsible for the movement of the ghosts.
 */

/**
 * \class CGhost
 * \brief This class is the parent class for all the ghosts and it describes all the skills that the ghosts can use interchangeably.
 */
class Ghost {
public:

    /**
     * \brief Constructor for Ghost
     */
    Ghost(int startX, int startY, char startChar);

    /**
    * @brief This virtual function is used to move the ghost on the map
     * @param game_map is the map on which the ghost is moving
     * @param cherryEaten is a boolean value that tells us if the cherry was eaten or not
    */
    virtual void moveGhost(std::vector<std::vector<char>> &game_map, bool cherryEaten);

    /**
    * @brief This function is used to reset the position of the ghost
    */
    void resetPosition();

    /**
    * \brief This function is used to set the default move delay of the ghost
    * @param delay is the new default move delay
    */
    virtual void setDefaultMoveDelay(double delay);

    /**
     * @brief Destructor for Ghost
     */
    virtual ~Ghost() = default;

    int x, y;  /**< Z and Y coordinated for movement */
    double moveDelay = 0; /**< Delay for movement of ghosts */
    double defaultMoveDelay = 0.3;  /**< Delay for movement of ghosts */
protected:

    /**
    * @brief This function is used to get the new direction of the ghost
     * @param game_map is the map on which the ghost is moving
     * @param new_x is the new x coordinate of the ghost
     * @param new_y is the new y coordinate of the ghost
     * @param newChar is the new character of the ghost
     * @return The new direction of the ghost
    */
    int getNewDirection(std::vector<std::vector<char>> &game_map, int &new_x, int &new_y, char &newChar);

    /**
    * @brief This function checks if the ghost is stuck and if it is, it gets it unstuck
     * @param new_x is the new x coordinate of the ghost
     * @param new_y is the new y coordinate of the ghost
     * @param newChar is the new character of the ghost
     * @param game_map is the map on which the ghost is moving
    */
    void getStuck(int &new_x, int &new_y, char &newChar, std::vector<std::vector<char>> &game_map);

    /**
    * @brief This function claculates the manhattan distance between two points
     * @param x1 is the x coordinate of the ghost
     * @param y1 is the y coordinate of the ghost
     * @param x2 is the x coordinate of the pacman
     * @param y2 is the y coordinate of the pacman
     * @return The manhattan distance between the two points
    */
    int manhattanDistance(int x1, int y1, int x2, int y2);


    int lastDirection; /**< This variable stores the last direction of the ghost */
    char previousChar;/**< This variable stores the previous character of the ghost */
    int initialX;/**< This variable stores the initial x coordinate of the ghost */
    int initialY;/**< This variable stores the initial y coordinate of the ghost */
};

/**
 * \class GhostA
 * \brief This class is the child class of Ghost and it describes the skills of the first ghost
 */
class GhostA : public Ghost {
public:

    /**
     * \brief Constructor for GhostA
     */
    GhostA(int startX, int startY, char startChar, int *p_x, int *p_y);


    /**
     * \brief This function is used to move the ghost on the map
     * @param game_map is the map on which the ghost is moving
     * @param cherryEaten is a boolean value that tells us if the cherry was eaten or not
     */
    void moveGhost(std::vector<std::vector<char>> &game_map, bool cherryEaten) override;

    /**
     * \brief This function is used to get the new direction of the ghost
     * @param game_map is the map on which the ghost is moving
     * @param new_x is the new x coordinate of the ghost
     * @param new_y is the new y coordinate of the ghost
     * @param newChar is the new character of the ghost
     * @return the new direction of the ghost
     */
    int getNewDirectionPath(std::vector<std::vector<char>> &game_map, int &new_x, int &new_y, char &newChar);

    /**
    * \brief This function is used to set the default move delay of the ghost
    * @param delay is the new default move delay
    */
     void setDefaultMoveDelay(double delay) override;

private:
    int *pacman_x; /**< This variable stores the x coordinate of the pacman */
    int *pacman_y; /**< This variable stores the y coordinate of the pacman */
};

/**
 * \brief This class is the child class of Ghost and it describes the skills of the second ghost
 */
class GhostB : public Ghost {
public:

    /**
     * \brief Constructor for GhostB
     */
    GhostB(int startX, int startY, char startChar, int *p_x, int *p_y);

    /**
     * \brief This function is used to move the ghost on the map
     * @param game_map is the map on which the ghost is moving
     * @param cherryEaten is a boolean value that tells us if the cherry was eaten or not
     */
    void moveGhost(std::vector<std::vector<char>> &game_map, bool cherryEaten) override;

private:
    int *pacman_x; /**< This variable stores the x coordinate of the pacman */
    int *pacman_y; /**< This variable stores the y coordinate of the pacman */
};

/**
 * \brief This class is the child class of Ghost and it describes the skills of the third ghost
 */
class GhostC : public Ghost {
public:

    /**
     * \brief Constructor for GhostC
     */
    GhostC(int startX, int startY, char startChar);

    /**
     * \brief This function is used to move the ghost on the map
     * @param game_map is the map on which the ghost is moving
     * @param cherryEaten is a boolean value that tells us if the cherry was eaten or not
     */
    void moveGhost(std::vector<std::vector<char>> &game_map, bool cherryEaten) override;
};


#endif //PA2_PACMAN_CGHOST_H