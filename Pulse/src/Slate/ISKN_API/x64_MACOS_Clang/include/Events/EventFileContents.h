/*!
 * \file EventFileContents.h
 * \brief File contents
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTFILECONTENTS_H
#define ISKN_EVENTFILECONTENTS_H

#include "GlobalDefines.h"
#include <vector>

namespace ISKN_API
{
STRUCT Event;

/*!
 * \struct EventFileContents
 * \brief Slate file contents event
 */
STRUCT EventFileContents
{
public :
    unsigned short int Id;                  /*!< file ID */
    std::vector<Event *> *Events;   /*!< List of incoming files content events */
};
END_STRUCT
}

#endif // ISKN_EVENTFILECONTENTS_H