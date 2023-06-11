//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CDATA_H
#define PA2_PACMAN_CDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <ncurses.h>

#include "../CPrint.h"

using namespace std;

/**
 * \class CData
 * \brief This class handles the data and printing of the PacMan game.
 */
class CData : public CPrint {
public:

    /**
    * \brief Default constructor.
    */
    CData();

    /**
    * \brief Default destructor.
    */
    ~CData();

    /**
     * \brief This function is used to read the data from the configuration files.
     * \param file[in] - the configuration file to read from.
     * \return bool indicating the success or failure of the operation.
     */
    bool readFromFile(string file);

    /**
     * \brief This function is used to write the data to the configuration files.
     * \param file[in] - the configuration file to write to.
     * \return bool indicating the success or failure of the operation.
     */
    bool writeToFile(string file);

};


#endif //PA2_PACMAN_CDATA_H
