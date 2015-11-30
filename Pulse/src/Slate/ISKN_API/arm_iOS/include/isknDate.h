/*!
 * \file isknDate.h
 * \brief isknDate
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/


#ifndef ISKNDATE_H
#define ISKNDATE_H

#include "GlobalDefines.h"

/*

Date : simple class to manage dates, platform independant

*/

namespace ISKN_API
{

/*!
 * \class ISKNDate
 * \brief Handle calendar
 */
CLASS ISKNDate
{
public :   
    /*!
         * \brief isknDate:Constructs a date according the local time zone.
         */
        ISKNDate() ;

        /*!
         * \brief isknDate :Constructs a date with year y, month m and day d.
         * \param year
         * \param month
         * \param day
         * \param dayOfWeek
         */
        ISKNDate(unsigned short int year, unsigned short int month, unsigned short int day, unsigned short int dayOfWeek) ;

        /*!
         * \brief isknDate : Constructs a isknDate as a copy of an other given isknDate
         * \param src : an isknDate object.
         */
        ISKNDate(const ISKNDate &src) ;

        /*!
         * \brief operator = Copy the given isknDate to this isknDate.
         * \param src : an isknDate
         * \return : an isknDate
         */
        ISKNDate &operator=(const ISKNDate &src) ;

        unsigned short int Year, Month, Day, DayOfWeek ;
};
END_CLASS

}

#endif // ISKNDATE_H
