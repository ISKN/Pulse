/*!
 * \file EventPen2D.h
 * \brief Pen move event with 2D Pen tip position
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTPEN2D_H
#define ISKN_EVENTPEN2D_H

#include "GlobalDefines.h"
#include "Vector2D.h"

namespace ISKN_API
{
/*!
 * \class EventPen2D
 * \brief Contain Slate pen 2D event
 */
CLASS EventPen2D
{
public :
    /*!
     * \brief getPosition
     * \return the position of the pen tip (xxx.xx millimeters)
     */
    Vector2D getPosition();

    /*!
     * \brief getRotation
     * \return the rotation of the pen tip (xx.xx degrees)
     */
    Vector2D getRotation();

    /*!
     * \brief Return is the pen touch the paper
     * \return true if the pen touch the paper, otherwise it return false
     */
    bool Touch();

private :
    short int X;
    short int Y;
    short int Rx;
    short int Ry;
    unsigned char Contact;
};
END_CLASS
}

#endif // ISKN_EVENTPEN2D_H
