//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CMAKEOBJECTS_H
#define PA2_PACMAN_CMAKEOBJECTS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <ncurses.h>

#include "./CData.h"

using namespace std;

/**
 * \class CMakeObjects
 * \brief This class is used to handle the creation of objects in the PacMan game.
 */
class CMakeObjects : public CData {
public:

    /**
    * \brief Default constructor.
    */
    CMakeObjects();

    /**
    * \brief Default destructor.
    */
    ~CMakeObjects();

    /**
     * \brief This function is used to load the map from the method createMap() where it was assembled.
     */
    void loadMap();

    /**
    * \brief It returns a number of rows in a map.
    * \return number of rows in a map
    */
    int getRows() const;

    /**
     * \brief It returns a number of columns in a map.
     * \return number of columns in a map
     */
    int getColumns() const;

    /**
     * \brief This function is used to get the height and width of the map.
     */
    void getMapDimensions();

    /**
    * \brief It puts the desired char in the desired position in the 2D char field.
    * \param[in] row - Y coordinate of the desired char we give
    * \param[in] column - X coordinate of the desired char we give
    * \param[in] letter - char which we want to have in the desired position
    */
    void changeCharMap(const int row, const int column, const char letter);

    /**
    * \brief It get the original coordinates of the ghost on the map.
    *
    * It happens before beginning of every game.
    * \param x[out] - takes X coordinates of a ghost
    * \param y[out] - takes Y coordinates of a ghost
    */
    void getGhostCoor(int &x, int &y);

    /**
     * \brief It gets the starting coordinates of pacman on the map.
     *
     * It happens before beginning of every game.
     * \param x[out] - takes X coordinates of a pacman
     * \param y[out] - takes Y coordinates of a pacman
     */
    void getCPacmanCoor(int &x, int &y) const;

private:
    int numberOfRows; /**< number of map rows */
    int numberOfColumn; /**< number of map columns */
    int pacman0X; /**< X coordinate of pacman */
    int pacman0Y; /**< Y coordinate of pacman */
    int pacman1X; /**< X coordinate of pacman */
    int pacman1Y; /**< Y coordinate of pacman */
    int ghost1X; /**< X coordinate of the first ghost in a map */
    int ghost1Y; /**< Y coordinate of the first ghost in a map */
    int ghost2X; /**< X coordinate of the second ghost in a map */
    int ghost2Y; /**< Y coordinate of the second ghost in a map */
    int ghost3X; /**< X coordinate of the third ghost in a map */
    int ghost3Y; /**< Y coordinate of the third ghost in a map */
    int ghost4X; /**< X coordinate of the third ghost in a map */
    int ghost4Y; /**< Y coordinate of the third ghost in a map */
};

#endif //PA2_PACMAN_CMAKEOBJECTS_H
