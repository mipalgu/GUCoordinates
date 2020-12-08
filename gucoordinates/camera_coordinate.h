/*
 * camera_coordinate.h 
 * gucoordinates 
 *
 * Created by Callum McColl on 19/06/2020.
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

#ifndef CAMERA_COORDINATE_H
#define CAMERA_COORDINATE_H

#include <guunits/guunits.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A `gu_camera_coordinate` represents the coordinate of a pixel within an
 * image where the (0, 0) coordinate is in the top left corner.
 */
typedef struct gu_camera_coordinate {

    /**
     * The x coordinate of the pixel within the image.
     *
     * The x coordinate must be in the range of:
     *  0 <= x < res_width
     */
    pixels_u x;

    /**
     * The y coordinate of the pixel within the image.
     *
     * The y coordinate must be in the range of:
     *  0 <= y < res_height
     */
    pixels_u y;

    /**
     * The width of the resolution of the image.
     */
    pixels_u res_width;

    /**
     * The height of the resolution of the image.
     */
    pixels_u res_height;

} gu_camera_coordinate;

bool gu_camera_coordinate_equals(const gu_camera_coordinate lhs, const gu_camera_coordinate rhs) __attribute__((const));

pixels_t gu_camera_coordinate_x_lower_bound(const gu_camera_coordinate) __attribute__((const));
pixels_t gu_camera_coordinate_y_lower_bound(const gu_camera_coordinate) __attribute__((const));
pixels_t gu_camera_coordinate_x_upper_bound(const gu_camera_coordinate) __attribute__((const));
pixels_t gu_camera_coordinate_y_upper_bound(const gu_camera_coordinate) __attribute__((const));

#ifdef __cplusplus
}
#endif

#endif  /* CAMERA_COORDINATE_H */
