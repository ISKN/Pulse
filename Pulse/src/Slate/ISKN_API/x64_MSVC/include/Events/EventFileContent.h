/*!
 * \file EventFileContent.h
 * \brief File content event 
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTFILECONTENT_H
#define ISKN_EVENTFILECONTENT_H

#include "GlobalDefines.h"

namespace ISKN_API
{
#define FILE_BLOCK_SIZE 64

/*!
 * \struct EventFileContent
 * \brief File content event
 */
STRUCT EventFileContent
{
    unsigned short int Id;          /*!< ID of the file */
    unsigned char Status;           /*!< File content status */
    unsigned int NumPart;           /*!< num ID of part */
    unsigned int NbParts;           /*!< numbers of part */
    unsigned short int Size;        /*!< Size of the file */
    char buffer[FILE_BLOCK_SIZE];   /*!< internal buffer */
};
END_STRUCT
}

#endif // ISKN_EVENTFILECONTENT_H