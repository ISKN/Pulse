/*!
 * \file EventDescription.h
 * \brief Slate description event
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTDESCRIPTION_H
#define ISKN_EVENTDESCRIPTION_H

#include "GlobalDefines.h"

#define MAX_VERSION_SIZE 4
#define MAX_DEVICE_NAME_SIZE 20
#define TXT_FIRMWARE_VERSION_SIZE 16



namespace ISKN_API
{
/*!
 * \class EventDescription
 * \brief Contain Slate description
 */
CLASS EventDescription
{
public:
    /*!
     * \brief Get Slate Name
     * \return wstring Slate Name
     */
     char * getDeviceName();

    /*!
     * \brief Get Slate Firmware Version
     * \return firmware version "xxx.xxx.xxx.xxx"
     */
    char *getFirmwareVersion();

    /*!
     * \brief Get client physical size area
     * \return Size physical size area
     */
    Size getSlateSize();

    /*!
     * \brief Returns the slate coordinates and size of the active zone
     * \return Rect useful size area
     */
    Rect getActiveZone();

    /*!
     * \brief Set scaling factor (0.1 or 0.01 regard of the physical width)
     * \warning Do not use this (internal use only)
     */
    void computeScalingFactor();

private:
    unsigned short int SlateWidth;
    unsigned short int SlateHeight;
    unsigned short int ActiveZoneWidth;
    unsigned short int ActiveZoneHeight;
    unsigned short int ActiveZoneLeft;
    unsigned short int ActiveZoneTop;
    char DeviceName[MAX_DEVICE_NAME_SIZE];
    unsigned char FirmwareVersion[MAX_VERSION_SIZE];
};
END_CLASS
}

#endif // ISKN_EVENTDESCRIPTION_H
