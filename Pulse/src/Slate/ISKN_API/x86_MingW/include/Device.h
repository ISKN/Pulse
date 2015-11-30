/*!
 * \file Device.h
 * \brief Device
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_DEVICE_H
#define ISKN_DEVICE_H

#include "GlobalDefines.h"
#include "FileSystem.h"

namespace ISKN_API
{

/*!
 * \class Device
 * \brief Slate specific management
 */
CLASS Device : public FileSystem
{

public:
    /*!
     * \brief Device
     * \warning internal use only
     */
    Device(void *p);

    virtual ~Device();

    /*!
     * \brief Gets the slate ID
     * \return the Slate name
     */
    char * getDeviceName();


    /*!
     * \brief Changes the slate ID
     * \param newName: the new wstring ID
     * \return true if succeeded, otherwise it return false
     *  Be aware : Doesn't support special characters
     */
    bool setDeviceName(char *newName);

    /*!
     * \brief Returns the slate firmware version
     * \return firmware version : XXX.XXX.XXX.XXX
     */
    char *getFirmwareVersion();


    /*!
     * \brief Returns the slate width
     * \return width
     */
    float getWidth();

    /*!
     * \brief Returns the slate height
     * \return height
     */
    float getHeight();

    /*!
     * \brief Returns the slate size
     * \return  a Size object
     */
    const Size &getSlateSize();

    /*!
     * \brief Returns the slate coordinates and size of the active zone
     * \return a Rect object
     */
    const Rect &getActiveZone();

    /*!
     * \brief Gets the slate coordinates and size of the active zone in independent parameters
     * \param left: left start coordinate
     * \param top: top start coordinate
     * \param width: width of the client space
     * \param height: height of the client space
     * \return true on success, false if an error occurred
     */
    bool getActiveZoneParameters(float &left, float &top, float &width, float &height);

    /*!
     * \brief Returns last battery charge
     * \return last battery charge
     */
    float getBatteryCharge();

    /*!
     * \brief Returns card presence
     * \return true if there is a SD card, otherwise it return false
     */
    bool isSDCardInserted();

    /*!
     * \brief Sets the slate internal time
     * \param dt: ISKN datetime class object
     * \param t: ISKN time class object
     * \return true if succeeded, otherwise it return false
     */
    bool setDateTime(const ISKNDate &dt, const ISKNTime &t);

    /*!
     * \brief Changes the slate code
     * \param newPinCode: the new wstring code
     * \return true if succeeded, otherwise it return false
     */
    bool setPinCode(char *newPinCode);


private :
    /*!
    * \brief pInternals
    * \warning Don't use this (internal use only)
    */
    void *pInternals;
} ;

END_CLASS

}

#endif // ISKN_DEVICE_H

