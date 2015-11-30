/*!
 * \file EventObject3D.h
 * \brief Object move event with 3D object position and orientation
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTOBJECT3D_H
#define ISKN_EVENTOBJECT3D_H

#include "GlobalDefines.h"
#include "Vector3D.h"
#include "Vector2D.h"


namespace ISKN_API
{
/*!
 * \class EventObject3D
 * \brief Contain Slate magnet ring 3D event
 */
CLASS EventObject3D
{
public :
    /*!
     * \brief getPosition
     * \return the position of the magnet ring (xxx.xx millimeters)
     */
    Vector3D getPosition();

    /*!
     * \brief getRotation
     * \return the rotation of the magnet ring (xx.xx degrees)
     */
    Vector2D getRotation();

private :
    short int X;
    short int Y;
    short int Z;
    short int Rx;
    short int Ry;
};
END_CLASS
}

#endif // ISKN_EVENTOBJECT3D_H