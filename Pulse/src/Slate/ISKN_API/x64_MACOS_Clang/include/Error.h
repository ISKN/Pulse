/*!
 * \file Error.h
 * \brief Error
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_ERROR_H
#define ISKN_ERROR_H

#include "GlobalDefines.h"

#define ERR_API 10000
#define ERR_FUNCTION_NOT_AVAILABLE			(ERR_API+0)
#define ERR_USB_NOT_PRESENT					(ERR_API+1)
#define ERR_BLUETOOTH_NOT_PRESENT			(ERR_API+2)
#define ERR_NO_DEVICE_FOUND                 (ERR_API+3)
#define ERR_API_LAST ERR_NO_DEVICE_FOUND

#define ERR_BUF 12000
#define ERR_BUF_CREATION_EMPTY              (ERR_BUF+1)
#define ERR_BUF_LAST ERR_BUF_CREATION_EMPTY

namespace ISKN_API
{

/*!
 * \class Error
 * \brief Error management
 */
CLASS Error
{

public:

    int Code;

    /*!
     * \brief Error : Constructs an Error with a code set to 0
     */
    Error();

    /*!
     * \brief Error : Constructs an Error with a given code
     * \param code
     */
    Error(int code);

    Error &operator=(const Error &src);

    /*!
     * \brief Return a message if an error has occurred
     * \return wstring message
     * \note the messages are only in English
     */
    std::wstring Message();
};

END_CLASS

}

#endif // ISKN_ERROR_H

