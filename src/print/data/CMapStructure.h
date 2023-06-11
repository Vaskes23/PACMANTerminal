//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CMAPSTRUCTURE_H
#define PA2_PACMAN_CMAPSTRUCTURE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <ncurses.h>

#include "./CMakeObjects.h"

using namespace std;

/**
 * \class CMapStrcuture
 * \brief This class is used to handle the map structure in the PacMan game.
 */
class CMapStrcuture : public CMakeObjects {
public:

    /**
    * \brief Default constructor.
    */
    CMapStrcuture();

    /**
    * \brief Default destructor.
    */
    ~CMapStrcuture();

    /**
     * \brief This function is used to check if the characters in the file that we create map from are valid.
     */
    void checkCharactersValid();

    /**
     * \brief This function is used to read the map from the file and checks then it adds the values to the create map.
     */
    void readMapFromString();

    /**
     * \brief This function is used to create the map by reading maps from the file and creating objects from strings.
     */
    void createMap();

    /**
    * \brief It returns a pointer to 2D char array.
    * \return pointer to 2D char field
    */
    char** getCharMap() const;

    /**
     * \brief It returns a char in the X and Y coordinates.
     * \param x[in] - X coordinate of char we need from 2D char field
     * \param y[in] - Y coordinate of char we need from 2D char field
     * \return char in the X and Y coordinates in the 2D char field
     */
    char getChar(const int x, const int y) const;

    /**
    * \brief It puts the desired char in the desired position in the 2D char field.
    * \param[in] row - Y coordinate of the desired char we give
    * \param[in] column - X coordinate of the desired char we give
    * \param[in] letter - char which we want to have in the desired position
    */
    void changeCharMap(const int row, const int column, const char letter);

private:
    char **charMapArray; /**< pointer to 2D char field */
    char **backUpCharMapArray; /**< pointer to 2D char field - backup */
};

#endif //PA2_PACMAN_CMAPSTRUCTURE_H
