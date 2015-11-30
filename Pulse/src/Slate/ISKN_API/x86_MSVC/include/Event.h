/*!
 * \file Event.h
 * \brief Event
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_EVENT_H
#define ISKN_EVENT_H

#include "GlobalDefines.h"

#pragma pack(push,1)
#include "Events/EventStatus.h"
#include "Events/EventDescription.h"
#include "Events/EventSoftware.h"
#include "Events/EventPen2D.h"
#include "Events/EventPen3D.h"
#include "Events/EventObject3D.h"
#include "Events/EventAccelerometer.h"
#include "Events/EventHardware.h"
#include "Events/EventDiskStatus.h"
#include "Events/EventFileDescriptor.h"
#include "Events/EventFileContent.h"
#include "Events/EventFileOperation.h"
#include "Events/EventError.h"
#include "Events/EventFileContents.h"
#pragma pack(pop)

#define UINT32 unsigned int

namespace ISKN_API
{
/*!
 * \brief The EventType enum
 */
enum EventType : unsigned char
{
    EVT_STATUS					= 1,  /*!< Status event */
    EVT_DESCRIPTION				= 2,  /*!< Description event */
    EVT_SOFTWARE				= 3,  /*!< Software event */
    EVT_PEN_2D					= 4,  /*!< Pen 2D event (Vector2D)*/
    EVT_PEN_3D					= 5,  /*!< Pen 3D event (Vector3D)*/
    EVT_OBJECT_3D				= 6,  /*!< Object 3D event */
    EVT_ACCELEROMETER			= 7,  /*!< Accelerometer event */
    EVT_HARDWARE                = 8,  /*!< Hardware event */
    EVT_DISK_STATUS				= 9,  /*!< SD card event */
    EVT_FILE_DESCRIPTOR				= 10, /*!< File info event */
    EVT_FILE_CONTENT			= 11, /*!< File content event */
    EVT_OPERATION_STATUS        = 12, /*!< Operation status event */
    EVT_ERROR					= 13, /*!< Error event */
    EVT_FILE_CONTENTS           = 14, /*!< File contents event */
};


/*!
 * \struct Event
 * \brief Slate incomming events
 */
STRUCT Event
{
    public :
    EventType               Type;             /*!< Event type (see EventType) */
    union
    {
        EventStatus         Status;         /*!< Slate event status (see EventStatus) */
        EventDescription    Description;    /*!< Slate event description (see EventDescription) */
        EventSoftware       SoftwareEvent;  /*!< A software event (see EventSoftware) */
        EventPen2D          Pen2D;          /*!< Slate pen 2D event (see EventPen2D) */
        EventPen3D          Pen3D;          /*!< Slate pen 3D event (see EventPen3D) */

        EventObject3D       Object3D;       /*!< Slate object 3D event (see EventObject3D) */
        EventAccelerometer  Acceleration;   /*!< Slate accelerometer event (see EventAccelerometer) */
        EventHardware       HardwareEvent;  /*!< A software event (see EventHardware) */
        EventDiskStatus     DiskStatus;     /*!< Slate disk status event (see EventDiskStatus) */
        EventFileDescriptor FileDescriptor; /*!< Slate file descriptor event (see EventFileDescriptor) */

        EventFileContent    FileContent;    /*!< Slate file content event (see EventFileContent) */
        EventFileContents   FileContents;   /*!< Slate file contents events (see EventFileContents) */
        EventFileOperation  FileOperation;  /*!< Slate file operation (see EventFileOperation) */
        EventError          Error;          /*!< Slate error event (see EventError) */
    };
};
END_STRUCT

}

#endif // ISKN_EVENT_H
