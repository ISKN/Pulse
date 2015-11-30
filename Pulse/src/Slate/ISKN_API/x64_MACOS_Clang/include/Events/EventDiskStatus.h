/*!
 * \file EventDiskStatus.h
 * \brief Disk status event 
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTDISKSTATUS_H
#define ISKN_EVENTDISKSTATUS_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \class EventDiskStatus
 * \brief Contain Slate disk status event
 */
CLASS EventDiskStatus
{
public :

    /*!
     * \brief getDiskSpace
     * \return available disk space
     */
    unsigned int getFreeDiskSpace();

    /*!
     * \brief get the number of files present on disk
     * \return the numbers of files present on the Slate
     */
    int getFilesNumber();

    /*!
     * \brief get information about disk state
     * \return true if disk is present, otherwise it returns false
     */
    bool isDiskOnline();

    /*!
     * \brief get information about disk state
     * \return true if disk is readable, otherwise it returns false
     */
    bool isDiskReadable();

    /*!
     * \brief get information about disk state
     * \return true if disk is writable, otherwise it returns false
     */
    bool isDiskWriteable();

    /*!
     * \brief ask if the disk has changed (SD->internal or internal->SD) since the last interrogation
     * \return true if disk changed, otherwise it returns false
     */
    bool isDiskChanged();

    /*!
     * \brief isSDCardInserted
     * \return true if the Slate use the SD card slot, otherwise returns false
     */
    bool isSDCardInserted();

    private :
    unsigned char State;
    unsigned int FreeSpace;
    unsigned short int Files;
};
END_CLASS
}

#endif // ISKN_EVENTDISKSTATUS_H
