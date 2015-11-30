/*!
 * \file EventHardware.h
 * \brief Hardware generated event 
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTHARDWARE_H
#define ISKN_EVENTHARDWARE_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \brief The Slate hardware Events enum
 */
enum HardwareEventType : unsigned char
{
    HE_BUTTON1_PRESSED      = 2, /*!< The button 1 has been pressed by user */
    HE_BUTTON2_PRESSED      = 3, /*!< The button 2 has been pressed by user */
    HE_SDCARD_OUT           = 4, /*!< The SD card has been ejected */
    HE_SDCARD_IN            = 5, /*!< A new SD card has been inserted */
};

/*!
 * \class EventHardware
 * \brief Contain Hardware events
 */
CLASS EventHardware
{
public :
    /*!
     * \brief Get Hardware Event Type
     * \return the Slate Hardware event type
     */
    HardwareEventType getHardwareEventType();

private :
    HardwareEventType hardwareEventType;
};
END_CLASS
}

#endif // ISKN_EVENTHARDWARE_H
