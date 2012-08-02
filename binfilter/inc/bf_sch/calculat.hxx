/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

// header for BOOL
#include <bf_svtools/bf_solar.h>

#include <vector>
#include <utility>
class Point;
class Rectangle;
namespace binfilter {

class Line;
class XPolygon;
class XPolyPolygon;

/** @descr  This class clips single lines and polygons at a given rectangle.
        All of it's methods are static, therefore no object has to be created.

        It uses the Liang-Biarsky parametric line-clipping algorithm as described in:
            Computer Graphics: principles and practice, 2nd ed.,
            James D. Foley et al.,
            Section 3.12.4 on page 117.
*/
class SchCalculationHelper
{
public:
    /** @descr  The intersection between an open polygon and a rectangle is
            calculated and the resulting lines are placed into the poly-polygon aResult.
        @param  rPolygon    The polygon is required to be open, ie. it's start and end point
            have different coordinates and that it is continuous, ie. has no holes.
        @param  rRectangle  The clipping area.
        @param  aResult The resulting lines that are the parts of the given polygon lying inside
            the clipping area are stored into aResult whose prior content is deleted first.
     */
    static void IntersectPolygonWithRectangle( const XPolygon& rPolygon, const Rectangle& rRectangle,
                                               XPolyPolygon& aResult );

private:
    /** @descr  The line given by it's two endpoints rP0 and rP1 is clipped at the rectangle
            rRectangle.  If there is at least a part of it visible then TRUE is returned and
            the endpoints of that part are stored in rP0 and rP1.  The points rP0 and rP1
            may have the same coordinates.
        @param  rP0 Start point of the line to clip.  Modified to contain a start point inside
            the clipping area if possible.
        @param  rP1 End point of the line to clip.  Modified to contain an end point inside
            the clipping area if possible.
        @param  rRectangle Clipping area.
        @return If the line lies completely or partly inside the clipping area then TRUE
            is returned.  If the line lies completely outside then FALSE is returned and rP0 and
            rP1 are left unmodified.
    */
    static  BOOL    clip2d  (Point & rP0, Point & rP1, const Rectangle& rRectangle);

    /** @descr  This is a supporting function for clip2d.  It computes a new parametric
            value for an entering (dTE) or leaving (dTL) intersection point with one
            of the edges bounding the clipping area.
            For explanation of the parameters please refer to the literature reference
            given above.
    */
    static  BOOL    CLIPt   (double fDenom, double fNum, double & fTE, double & fTL);
};

} //namespace binfilter
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
