/*!
 * \file Vector3D.h
 * \brief Vector3D
 * \author ISKN TEAM
 * \version 0.1
 * \date 31/01/2015
 *
 * This file is part of the "ISKN" library.
 * For conditions of distribution and use, see copyright notice in ISKN_API.h
*/

#ifndef ISKN_VECTOR3D_H
#define ISKN_VECTOR3D_H

#include "GlobalDefines.h"

namespace ISKN_API
{
/*!
 * \class Vector3D
 * \brief Represents a vector  in 3D space.
 *
 */
CLASS Vector3D
{
	public:
    /*!
     * \brief Vector3D: Constructs a Vector3D with x, y  and z set to zero.
     */
	Vector3D() ;

    /*!
     * \brief Vector3D :Constructs a Vector3D with the given x,y and z
     * \param x
     * \param y
     * \param z
     */
	Vector3D(float x, float y, float z=0.0f) ;

    /*!
     * \brief Vector3D :Constructs a Vector3D as a copy of an other given Vector3D.
     * \param src : a Vector3D
     */
	Vector3D(const Vector3D &src) ;

    /*!
     * \brief operator = Copy the given Vector3D to this Vector3D.
     * \param src : a Vector3D.
     * \return a Vector3D
     */
	Vector3D &operator=(const Vector3D &src) ;

    /*!
     * \brief operator = Copy the given Vector2D to this Vector3D with z set to 0.
     * \param src : a Vector2D
     * \return a Vector3D
     */
	Vector3D &operator=(const Vector2D &src) ;

    /*!
     * \brief getNorm :Computes the norm of a the 3D Vector.
     * \return the norm of the vector
     */
	float getNorm() ;
    /*!
     * \brief getNormalized: Normalizes the currect vector in place.
     * \return the normalized unit vector form of this vector.
     */
	Vector3D getNormalized() ;

    float      X, Y, Z ;
} ;
  
END_CLASS

}

#endif // ISKN_VECTOR3D_H
