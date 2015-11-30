/*!
 * \file FileSystem.h
 * \brief FileSystem
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_FILESYSTEM_H
#define ISKN_FILESYSTEM_H

#include "GlobalDefines.h"

#include <vector>
#include "FileInfo.h"

namespace ISKN_API
{

/*!
 * \class FileSystem
 * \brief Controls the access to the Slate files
 */
CLASS FileSystem
{
public:
    FileSystem();

    /*!
     * \brief get available space on disk
     * \return free disk space
     */
    long int getFreeDiskSpace();

    /*!
     * \brief get information about selected files
     * \param files: a vector of files
     * \return true if succeeded, otherwise it returns false
     */
    bool getFiles(std::vector<FileInfo> &files);

    /*!
     * \brief remove a file
     * \param numFile: file ID
     * \return true if succeeded, otherwise it returns false
     */
    bool removeFile(int numFile);

    /*!
     * \brief format a disk
     * \return true if succeeded, otherwise it returns false
     */
    bool formatDisk();

    /*!
     * \brief import a file
     * \param numFile: import the selected file (file ID)
     * \return true if succeeded, otherwise it returns false
     */
    bool importFile(int numFile);

    /*!
     * \brief   refresh files infos :
     *          sends a request to the slate to update filesystem
     *          parameters.
     * \return true if succeeded, otherwise it returns false
     */
    bool refresh();

    /*!
     * \brief get information about the selected file
     * \param numFile: file ID
     * \return true if succeeded, otherwise it returns false
     */
    bool getFileInfo(int numFile);

    /*!
     * \brief get the number of files present on disk
     * \return the numbers of files present on the Slate
     */
    int getFilesNumber();

    /*!
     * \brief get information about disk state
     * \return true if disk is present, otherwise it returns false
     */
    bool isDiskOnline();

    /*!
     * \brief get information about disk state
     * \return true if disk is readable, otherwise it returns false
     */
    bool isDiskReadable();

    /*!
     * \brief get information about disk state
     * \return true if disk is writable, otherwise it returns false
     */
    bool isDiskWriteable();

    /*!
     * \brief get information about disk state
     * \return true if disk changed, otherwise it returns false
     */
    bool isDiskChanged();

    /*!
     * \brief get information about disk type
     * \return true if a SD card is in use, otherwise it returns false
     */
    bool isSDCardInserted();

protected :

    /*!
     * \brief hInternals
     * \warning Don't use this (internal use only)
     */
    void *hInternals;
} ;

END_CLASS

}

#endif // ISKN_FILESYSTEM_H
