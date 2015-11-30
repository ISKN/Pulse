/*!
 * \file SlateManager.h
 * \brief SlateManager
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_SLATEMANAGER_H
#define ISKN_SLATEMANAGER_H


#include "GlobalDefines.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include "LanguageId.h"
#include "Listener.h"
#include "Device.h"


namespace ISKN_API
{

/*!
 * \brief Possible blocks for event registration
 */
enum AutoBlockType : unsigned short int
{
    AUTO_NONE               = 0,         /*!< Unsubscribe */
    AUTO_STATUS             = (1 << 0),  /*!< Subscribe to status changed event */
    AUTO_SOFTWARE_EVENTS    = (1 << 1),  /*!< Subscribe to Software events (Object IN, Object OUT, handshake) */
    AUTO_PEN_2D             = (1 << 2),  /*!< Subscribe to Pen 2D events (Pen tip position, orientation and contact status in 2D) */
    AUTO_PEN_3D             = (1 << 3),  /*!< Subscribe to Pen 3D events (Pen tip position, orientation and contact status in 3D) */
    AUTO_OBJECT_3D          = (1 << 4),  /*!< Subscribe to Object 3D events (Generic magnetic object position and orientation in 3D) */
    AUTO_ACCELEROMETER      = (1 << 5),  /*!< Subscribe to Accelerometer events */
    AUTO_HARDWARE_EVENTS    = (1 << 6),  /*!< Subscribe to hardware events (button pressed, sd card inserted or removed...)  */
    AUTO_DISK_STATUS        = (1 << 7),  /*!< Subscribe to disk status changed events */
    AUTO_ERROR              = (1 << 8),  /*!< Subscribe to Error */
    AUTO_ALL                = 0xFFFF     /*!< Subscribe to all events */
};


/*!
 * \brief operator | to combine AutoBlockType
 */
inline AutoBlockType operator | (AutoBlockType a, AutoBlockType b) { return((AutoBlockType)((unsigned short int)(a)|(unsigned short int)(b))) ; }


/*!
 * \brief Send a unique request
 */
enum SingleRequestBlockType : unsigned char
{
    REQ_STATUS          = 1,  /*!< ask for a status block */
    REQ_DESCRIPTION     = 2,  /*!< ask for a description block */
    REQ_OBJECT_STATUS   = 3,  /*!< ask for object status (in field of vew or not and which object is in the field of view) */
    REQ_PEN_2D          = 4,  /*!< ask for pen 2D block */
    REQ_PEN_3D          = 5,  /*!< ask for pen 3D block */
    REQ_OBJECT_3D       = 6,  /*!< ask for object 3D block */
    REQ_ACCELEROMETER   = 7,  /*!< ask for an accelerometer block */
    REQ_DISK_STATUS     = 9,  /*!< ask for a disk status block */
    REQ_DIRECTORY       = 10, /*!< ask for directory block */
    REQ_NEW_PAGE        = 11  /*!< ask for new page */
};


/*!
 * \brief Communication types
 */
enum CommLayerType
{
    CL_USB=0,       /*!< USB layer */
    CL_BLUETOOTH=1, /*!< Bluetooth layer */
};


#if defined(_WIN32) | TARGET_OS_MACOSX | defined(linux)
    #define CL_DEFAULT CL_USB                           /*! Define the USB layer as default on PC/MAC */
#else
    #define CL_DEFAULT CL_BLUETOOTH                     /*! Define the bluetooth layer as default on IOS */
#endif

#define DEFAULT_MAX_EVENTS 30000

/*!
 * \class SlateManager
 * \brief Main Class for access to the communication layer.
 *      It represents the entry point to the Slatde.
 */

CLASS SlateManager
{

	public :
        SlateManager(const CommLayerType tpe=CL_DEFAULT) ;
        virtual ~SlateManager() ;

        /*!
         * \brief setLanguage
         * \param lg
         */
		void setLanguage(LanguageId lg) ;

        /*!
         * \brief getLanguage
         * \return the language id
         */
		LanguageId getLanguage() ;

        /*!
         * \brief registerForEvent
         * \param listener
         * \return
         */
        bool registerListener(Listener *listener) ;

        /*!
         * \brief unregisterForEvent
         * \return
         */
        bool unregisterListener(Listener *listener) ;

        /*!
         * \brief Ask for a connection (asynchronous on iOS, synchronous on others)
         * \return true on success, false if an error occurred
         */
        bool connect();

        /*!
         * \brief Ask for disconnection (asynchronous on iOS, synchronous on others)
         * \return true on success, false if an error occurred
         */
        bool disconnect();

        /*!
         * \brief Connection state
         * \return true if connected, false if an error occurred
         */
        bool isConnected();

        /*!
         * \brief Register for automatic events
         * \param mask: Possible blocks for event registration
         * \return true on success, false if an error occurred
         */
        bool subscribe(AutoBlockType mask);

        /*!
         * \brief Ask for a single request
         * \param request: The requested block
         * \return true on success, false if an error occurred
         */
        bool request(SingleRequestBlockType request);

        /*!
         * \brief Get access to the connected device
         * \return Device object
         */
        Device & getDevice();

        /*!
        * \brief pInternals
        * \warning Don't use this (internal use only)
        */
            void *pInternals ;
} ;

END_CLASS

}

#endif // ISKN_SLATEMANAGER_H

