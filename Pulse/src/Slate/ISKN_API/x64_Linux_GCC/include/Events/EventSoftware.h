/*!
 * \file EventSoftware.h
 * \brief Embedded software generated event
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTSOFTWARE_H
#define ISKN_EVENTSOFTWARE_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \brief The SoftwareEventType enum
 */
enum SoftwareEventType : unsigned char
{
    SE_OBJECT_IN     = 1, /*!< A new object (with ISKN certified magnet) has entered in the detection area */
    SE_OBJECT_OUT    = 2, /*!< The object has left the detection area */
    SE_HANDSHAKE     = 3, /*!< Handshake sent by the Slate every second */
} ;

/*!
 * \class EventSoftware
 * \brief Contain Software event parameters
 */
CLASS EventSoftware
{
public :
    /*!
     * \brief If the Software event is related to an object (containing ISKN certified magnet),
     *  this method returns the object ID Otherwise it returns 0
     * \return the object ID
     */
    int getObjectID();

    /*!
     * \brief gets the Software Event Type
     * \return the software event id
     */
    SoftwareEventType getSoftwareEventType();

private :
    unsigned char objectID;
    SoftwareEventType softwareEventType;
};
END_CLASS
}

#endif // ISKN_EVENTSOFTWARE_H
