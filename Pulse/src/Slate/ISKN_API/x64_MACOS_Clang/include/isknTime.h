/*!
 * \file isknTime.h
 * \brief isknTime
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/


#ifndef ISKNTIME_H
#define ISKNTIME_H


#include "GlobalDefines.h"

namespace ISKN_API
{

/*!
 * \class isknTime
 * \brief Handle time
 */
CLASS ISKNTime
{
  public :

	unsigned short int Hour, Minute, Second ;

	public :

    /*!
     * \brief isknTime :Constructs a time according the local time zone.
     */
    ISKNTime() ;

    /*!
     * \brief isknTime :Constructs a time with hour h, minute m, seconds s
     * \param hour :must be in the range 0 to 23.
     * \param minute :must be in the range 0 to 59.
     * \param second :must be in the range 0 to 59.
     */
    ISKNTime(unsigned short int hour, unsigned short int minute, unsigned short int second) ;

    /*!
     * \brief isknTime : Constructs an isknTime as a copy of an other given isknTime
     * \param src :an isknTime object.
     */
    ISKNTime(const ISKNTime &src) ;

    /*!
     * \brief operator = Copy the given isknTime to this isknTime.
     * \param src : an isknTime
     * \return : an isknTime
     */
    ISKNTime &operator=(const ISKNTime &src) ;
} ;

END_CLASS

}

#endif // ISKNTIME_H
