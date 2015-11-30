/*!
 * \file Rect.h
 * \brief Rect
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_RECT_H
#define ISKN_RECT_H

#include "GlobalDefines.h"

namespace ISKN_API
{

/*!
 * \class Rect
 * \brief Defines a rectangle in the plane using integer precision
 */
CLASS Rect : public Size
{

public :

    /*!
    * \brief Rect:Constructs a null rectangle.
    */
    Rect();

    /*!
     * \brief Rect :Constructs a rectangle with (top,left) as its top-left corner
     *               and the given width and height.
     * \param left :The left corner coordinates.
     * \param top  :The top corner coordinates.
     * \param width :The rectangle width.
     * \param height :The rectangle height.
     */
    Rect(float left, float top, float width, float height);

    /*!
     * \brief Rect:Constructs a rectangle as a copy of an other given rectangle.
     * \param src :A Rect.
     */
    Rect(const Rect &src);

    /*!
     * \brief operator = Copy the given Rect to this Rect.
     * \param src : a Rect.
     * \return a Rect.
     */
    Rect &operator=(const Rect &src);

    float Left,Top;
};
END_CLASS

}

#endif // ISKN_RECT_H
