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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A field_coordinate is a coordinate for a robot on the field. 
 * 
 * The coordinate describes the position of the robot on the field
 * (with x and y) as well as the direction that the robot is facing
 * (with heading).
 */
typedef struct gu_field_coordinate
{
    /**
     * The x coordinate for the position on the field.
     *
     * If the field is viewed where the home sides goal box is in the west
     * (and the away goal box is towards the east) then the x axis runs
     * north to south. A negative x value indicates a position in the north
     * side of the field while a postive x value indicates a position in the
     * south side of the field. An x value of zero indicates that the position
     * is in the center of the field.
     */
    centimetres_t x;

    /**
     * The y coordinate for the position on the field.
     *
     * If the field is viewed where the home sides goal box is in the west
     * (and the away goal box is towards the east) then the y axis runs
     * west to east. A negative y value indicates a position on the west side
     * of the field while a positive y value indicates a position on the east
     * side of the field. A y value of zero indicates that the position is in
     * the center of the field.
     */
    centimetres_t y;

    /**
     * The direction where the robot is facing.
     *
     * If the field is viewed where the home sides goal box is in the west
     * (and the away goal box is towards the east) then direction runs counter
     * clockwise where the zero direction is facing directly south. Therefore
     * 90 degrees points directly east, 180 degrees directly north and
     * 270 degrees directly west.
     */
    degrees_t heading;


} gu_field_coordinate;

#ifdef __cplusplus
};
#endif

#endif  /* FIELD_COORDINATE_H */
