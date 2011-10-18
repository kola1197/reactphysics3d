/********************************************************************************
* ReactPhysics3D physics library, http://code.google.com/p/reactphysics3d/      *
* Copyright (c) 2010 Daniel Chappuis                                            *
*********************************************************************************
*                                                                               *
* Permission is hereby granted, free of charge, to any person obtaining a copy  *
* of this software and associated documentation files (the "Software"), to deal *
* in the Software without restriction, including without limitation the rights  *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
* copies of the Software, and to permit persons to whom the Software is         *
* furnished to do so, subject to the following conditions:                      *
*                                                                               *
* The above copyright notice and this permission notice shall be included in    *
* all copies or substantial portions of the Software.                           *
*                                                                               *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
* THE SOFTWARE.                                                                 *
********************************************************************************/

#ifndef BOX_SHAPE_H
#define BOX_SHAPE_H

// Libraries
#include <cfloat>
#include "Shape.h"
#include "../mathematics/mathematics.h"


// ReactPhysics3D namespace
namespace reactphysics3d {

/*  -------------------------------------------------------------------
    Class BoxShape :
        This class represents a 3D box. Those axis are unit length.
        The three extents are half-widths of the box along the three
        axis x, y, z local axis. The "transform" of the corresponding
        rigid body gives an orientation and a position to the box.
    -------------------------------------------------------------------
*/
class BoxShape : public Shape {
    private :
        Vector3 extent;           // Extent sizes of the box in the x, y and z direction

    public :
        BoxShape(const Vector3& extent);        // Constructor
        virtual ~BoxShape();                     // Destructor

        const Vector3& getExtent() const;                                                           // Return the extents of the box
        void setExtent(const Vector3& extent);                                                      // Set the extents of the box
        virtual Vector3 getLocalExtents(double margin=0.0) const;                                   // Return the local extents in x,y and z direction
        virtual Vector3 getLocalSupportPoint(const Vector3& direction, double margin=0.0) const;    // Return a local support point in a given direction
        virtual void computeLocalInertiaTensor(Matrix3x3& tensor, double mass) const;               // Return the local inertia tensor of the shape

#ifdef VISUAL_DEBUG
            virtual void draw() const;                                                                      // Draw the Box (only for testing purpose)
#endif
};

// Return the extents of the box
inline const Vector3& BoxShape::getExtent() const {
    return extent;
}

 // Set the extents of the box
inline void BoxShape::setExtent(const Vector3& extent) {
    this->extent = extent;
}

// Return the local extents of the shape (half-width) in x,y and z local direction
// This method is used to compute the AABB of the box
inline Vector3 BoxShape::getLocalExtents(double margin) const {
    return extent + Vector3(margin, margin, margin);
}

// Return a local support point in a given direction
inline Vector3 BoxShape::getLocalSupportPoint(const Vector3& direction, double margin) const {
    assert(margin >= 0.0);
    
    return Vector3(direction.getX() < 0.0 ? -extent.getX()-margin : extent.getX()+margin,
                    direction.getY() < 0.0 ? -extent.getY()-margin : extent.getY()+margin,
                    direction.getZ() < 0.0 ? -extent.getZ()-margin : extent.getZ()+margin);
}

}; // End of the ReactPhysics3D namespace

#endif