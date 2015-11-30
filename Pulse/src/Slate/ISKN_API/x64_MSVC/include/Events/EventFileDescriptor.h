/*!
 * \file EventFileDescriptor.h
 * \brief File descriptor event 
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTFILEDESCRIPTOR_H
#define ISKN_EVENTFILEDESCRIPTOR_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \class EventFileDescriptor
 * \brief Contain Slate file descriptor event
 */
CLASS EventFileDescriptor
{
public :
    /*!
     * \brief getSize
     * \return the size of the file
     */
    unsigned int getSize();

    /*!
     * \brief getId
     * \return the ID of the file
     */
    int getId();

    /*!
     * \brief getDate
     * \return the creation date of the file
     */
    ISKNDate getDate();

    /*!
     * \brief getTime
     * \return the creation time of the file
     */
    ISKNTime getTime();

private :
    unsigned short int Id;
    unsigned int Size;
    unsigned short int Year;
    unsigned char Month, Day, Hour, Minute, Second;
};
END_CLASS
}

#endif // ISKN_EVENTFILEDESCRIPTOR_H