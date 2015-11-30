/*!
 * \file EventFileOperation.h
 * \brief File operation event 
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTFILEOPERATION_H
#define ISKN_EVENTFILEOPERATION_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \struct EventFileOperation
 * \brief File content operation
 */
STRUCT EventFileOperation
{
#ifdef _WIN32
    unsigned long long Operation;       /*!< internal operation file */
#else
    unsigned long int Operation;        /*!< internal operation file */
#endif
    unsigned char Status;               /*!< internal status */
};
END_STRUCT
}

#endif // ISKN_EVENTFILEOPERATION_H
