/*!
 * \file EventAccelerometer.h
 * \brief New Accelerometer data ready
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTACCELEROMETER_H
#define ISKN_EVENTACCELEROMETER_H

#include "GlobalDefines.h"
#include "Vector3D.h"

namespace ISKN_API
{
/*!
 * \class EventAccelerometer
 * \brief Contain Slate accelerometer event
 */
CLASS EventAccelerometer
{
public :
    /*!
     * \brief getAccelerometer
     * \return the acceleration of the Slate (milli-G)
     */
    Vector3D getAccelerometer();

private :
    float Ax;
    float Ay;
    float Az;
    unsigned char operation;
};
END_CLASS
}

#endif // ISKN_EVENTACCELEROMETER_H
