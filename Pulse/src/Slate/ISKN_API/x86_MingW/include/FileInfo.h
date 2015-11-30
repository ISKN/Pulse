/*!
 * \file FileInfo.h
 * \brief FileInfo
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_FILEINFO_H
#define ISKN_FILEINFO_H

#include "GlobalDefines.h"

namespace ISKN_API
{

/*!
 * \class FileInfo
 * \brief Get information about a file
 */
CLASS FileInfo
{
public:

    /*!
    * \brief FileInfo : Constructs a File with an id and a size set to zero.
    */
    FileInfo();

    /*!
     * \brief FileInfo :Constructs a FileInfoas a copy of an other given FileInfo.
     * \param src
     */
    FileInfo(const FileInfo &src);

    /*!
     * \brief FileInfo : Constructs a FileInfo with the given id, size,date and time.
     * \param id : the file id
     * \param size :the file size
     * \param date : the file creation date
     * \param time : the file creation time
     */
    FileInfo(int id, long int size, const ISKNDate &date, const ISKNTime &time);
    virtual ~FileInfo();

    FileInfo &operator=(const FileInfo &src);

    /*!
     * \brief getId
     * \return the ID of the file
     */
    int getId();

    /*!
     * \brief getSize
     * \return the size of the file
     */
    long int getSize();

    /*!
     * \brief getDate
     * \return the isknDate creation date of the file
     */
    const ISKNDate &getDate();

    /*!
     * \brief getTime
     * \return the isknTime creation time of the file
     */
    const ISKNTime &getTime();

private :
    int Id;
    long int Size;
    ISKNDate fDate;
    ISKNTime fTime;
};
END_CLASS

}

#endif // ISKN_FILEINFO_H

