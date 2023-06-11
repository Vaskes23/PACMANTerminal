//
// Created by Matyas Vascak on 11.05.2023.
//

#ifndef PA2_PACMAN_CPOINT_H
#define PA2_PACMAN_CPOINT_H


#include "CTake.h"
#include "../CPacManGame.h"

/**
 * \class CPoint
 * \brief This class is used for the counting and adding of the pacman points
 */
class CPoint : public CTake {//EXISTENCE A POTREBNOST TETO TRIDY BUDE JESTE ZVAZENA PRI IMPLEMENTACI
public:

    /**
     * \brief Constructor for the CPoint class
     */
    CPoint();

    /**
     * \brief Destructor for the CPoint class
     */
    ~CPoint();

    /**
     * \brief This function will return true if pacman had eaten all the points on the map we counted in the class Ctake using checkEadiblesCount() function
     * \param point[in] - The number of points Pacman has eaten
     * \return True if all points have been eaten, False otherwise
     */
    // bool checkEadiblesCount(int point);
};

#endif //PA2_PACMAN_CPOINT_H
