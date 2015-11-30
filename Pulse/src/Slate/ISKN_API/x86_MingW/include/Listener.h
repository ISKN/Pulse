/*!
 * \file Listener.h
 * \brief Listener
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_LISTENER_H
#define ISKN_LISTENER_H

#include "GlobalDefines.h"
#include "Event.h"

namespace ISKN_API
{

#define timecode_t unsigned int

/*!
 * \class Listener
 * \brief Slate event management
 */
CLASS Listener
{
public:

//    /*!
//     * \brief processEvent : method invoked when an event is dispatched from the slate
//     * \param event : object of the incoming event
//     * \param timecode :relative time code of the pen
//     */
    /*!
     * \brief method invoked when an event is dispatched from the slate
     * \param connection status (connected or not)
     */
    virtual void processEvent(Event &event, timecode_t timecode)=0;

    /*!
     * \brief Method invoked when connection status has changed (connected, couldn't connect)
     * \param connection status (connected or not)
     */
    virtual void connectionStatusChanged(bool connected)=0;


};
END_CLASS

}

#endif // ISKN_LISTENER_H

