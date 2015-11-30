/*!
 * \file EventPen3D.h
 * \brief Pen move event with 3D Pen tip position
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTPEN3D_H
#define ISKN_EVENTPEN3D_H

#include "GlobalDefines.h"
#include "Vector3D.h"
#include "Vector2D.h"

namespace ISKN_API
{
/*!
 * \class EventPen3D
 * \brief Contain Slate pen 3D event
 */
CLASS EventPen3D
{
public :
    /*!
     * \brief getPosition
     * \return the position of the pen (xxx.xx millimeters)
     */
    Vector3D getPosition();

    /*!
     * \brief getRotation
     * \return the rotation of the pen (xx.xx degrees)
     */
    Vector2D getRotation();

    /*!
     * \brief getZPaper
     * \return the elevation of the pen from the paper view
     */
    float getZPaper();

    /*!
     * \brief Return is the pen touch the paper
     * \return true if the pen touch the paper, otherwise it return false
     */
    bool Touch();

private :
    short int X;
    short int Y;
    short int Z;
    short int ZPaper;
    short int Rx;
    short int Ry;
    unsigned char Contact;
};
END_CLASS
}

#endif // ISKN_EVENTPEN3D_H