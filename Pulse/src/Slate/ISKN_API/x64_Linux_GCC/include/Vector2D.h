/*!
 * \file Vector2D.h
 * \brief Vector2D
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_VECTOR2D_H
#define ISKN_VECTOR2D_H


#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \class Vector2D
 * \brief Represents a vector  in 2D space.
 *
 */
CLASS Vector2D
{
    public:

    /*!
     * \brief Vector2D :Constructs a Vector2D with x and y set to zero.
     */

	Vector2D() ;

    /*!
     * \brief Vector2D :Constructs a Vector3D with the given x and y.
     * \param x
     * \param y
     */
	Vector2D(float x, float y) ;

    /*!
     * \brief Vector2D :Constructs a Vector2D as a copy of an other given Vector2D.
     * \param src :a Vector2D
     */
	Vector2D(const Vector2D &src) ;

    /*!
     * \brief operator = Copy the given Vector2D to this Vector2D.
     * \param src : a Vector2D
     * \return : a Vector2D
     */
	Vector2D &operator=(const Vector2D &src) ;

    /*!
     * \brief getNorm :Computes the norm of a the 2D Vector.
     * \return the norm of the vector
     */
	float getNorm() ;

    /*!
     * \brief getNormalized: Normalizes the currect vector in place.
     * \return the normalized unit vector form of this vector.
     */
	Vector2D getNormalized() ;

    float      X, Y ;
} ;

END_CLASS  

}

#endif // ISKN_VECTOR2D_H

