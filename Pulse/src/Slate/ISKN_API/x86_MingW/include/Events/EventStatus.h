/*!
 * \file EventsCommon.h
 * \brief Common header for events
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTSTATUS_H
#define ISKN_EVENTSTATUS_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \class EventStatus
 * \brief Contain events status info
 */
CLASS EventStatus
{
public :
    int getBattery();
    int isBatteryInCharge();


private :
    unsigned char Battery;     // charge (in percent)
    unsigned char inCharge;
};
END_CLASS
}

#endif // ISKN_EVENTSTATUS_H
