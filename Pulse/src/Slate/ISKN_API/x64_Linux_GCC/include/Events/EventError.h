/*!
 * \file EventError.h
 * \brief Error occurred on the slate
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/
#ifndef ISKN_EVENTERROR_H
#define ISKN_EVENTERROR_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \struct EventError
 * \brief Slate event error
 */
STRUCT EventError
{
    unsigned char ErrorCode;    /*!< Error code */
    int Parameter;              /*!< Error parameter */
};
END_STRUCT
}

#endif // ISKN_EVENTERROR_H