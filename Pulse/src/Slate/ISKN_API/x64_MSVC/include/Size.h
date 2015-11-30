/*!
 * \file Size.h
 * \brief Size
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_SIZE_H
#define ISKN_SIZE_H

#include "GlobalDefines.h"

namespace ISKN_API
{

/*!
 * \class Size
 * \brief defines the size of a two-dimensional object( Width, Height).
 */
CLASS Size
{
public:

    /*!
     * \brief Size : Constructs a Size with a Width and a Height set to zero.
     */
    Size();

    /*!
     * \brief Size : Constructs a Size with the given width and height.
     * \param width : Width on float precision.
     * \param height :height on float precision.
     */
    Size(float width, float height);

    /*!
     * \brief Size : Constructs a Size as a copy of an other given size
     * \param src  :a Size object.
     */
    Size(const Size &src);

    /*!
     * \brief operator : Copy the given Size to this Size.
     * \param src : a Size
     * \return : a Size
     */
    Size &operator=(const Size &src);

    float Width, Height;


};

END_CLASS

}

#endif // ISKN_SIZE_H
