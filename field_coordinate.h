/*
 * field_coordinate.h 
 * gucoordinates 
 *
 * Created by Callum McColl on 20/06/2020.
 * Copyright © 2020 Callum McColl. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgement:
 *
 *        This product includes software developed by Callum McColl.
 *
 * 4. Neither the name of the author nor the names of contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or
 * modify it under the above terms or under the terms of the GNU
 * General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef FIELD_COORDINATE_H
#define FIELD_COORDINATE_H

#include <guunits/guunits.h>
#include <stdbool.h>
#include "cartesian_coordinate.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A field_coordinate is a coordinate for an object that faces a certain
 * direction (such as a robot) on the field. 
 * 
 * The coordinate describes the location of the object on the field
 * (with position) as well as the direction that the object is facing
 * (with heading).
 */
typedef struct gu_field_coordinate
{

    /**
     * The position of the object on the field.
     *
     * If the field is viewed where the home side is in the west and the
     * away side is in the east, then the x asix runs north to south. The
     * y axis runs west to east. A negative x value indicates a position
     * in the northern half of the field while a positive x value indicates
     * a position in the southern half of the field. A negative y value
     * indicates a position in the western side of the field whereas a positive
     * y value indicates a position in the eastern side of the field. A value
     * of zero for both x and y indicate that the object is in the middle of
     * the field.
     *
     * As an example, if we take an actual full sized 100 meter field, then
     * the middle of the goal line on the home side of the field would be at
     * the coordinates (0, -50). The middle of the away goal line would be
     * (0, 50). The middle line which separates the two sides of a field which 
     * is 60 meters wide runs from the points (-30, 0) to (30, 0). 
     */
    gu_cartesian_coordinate position;

    /**
     * The direction where the object is facing.
     *
     * If the field is viewed where the home side is in the west and the away
     * side is in the ast, then the direction runs counter clockwise where the
     * zero direction faces directly south. Therefore, 90 degrees points
     * directly east, 180 degrees points directly north and 270 degrees points
     * directly west.
     */
    degrees_t heading;


} gu_field_coordinate;

bool gu_field_coordinate_equals(const gu_field_coordinate, const gu_field_coordinate);

#ifdef __cplusplus
}
#endif

#endif  /* FIELD_COORDINATE_H */
