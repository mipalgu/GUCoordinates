/*
 * conversions.h 
 * gunavigation 
 *
 * Created by Callum McColl on 18/06/2020.
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

#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <guunits/guunits.h>
#include "camera_coordinate.h"
#include "pixel_coordinate.h"
#include "percent_coordinate.h"
#include "relative_coordinate.h"
#include "cartesian_coordinate.h"
#include "field_coordinate.h"
#include "camera_pivot.h"

#ifdef __cplusplus
extern "C" {
#endif

// Converting between image coordinate systems.
gu_pixel_coordinate cam_coord_to_px_coord(const gu_camera_coordinate) __attribute__((const));
gu_camera_coordinate px_coord_to_cam_coord(const gu_pixel_coordinate) __attribute__((const));
gu_percent_coordinate px_coord_to_pct_coord(const gu_pixel_coordinate) __attribute__((const));
gu_pixel_coordinate pct_coord_to_px_coord(const gu_percent_coordinate, const pixels_u, const pixels_u) __attribute__((const));

// Converting from image coordinate systems to the robot relative coordiante system.
bool px_coord_to_rr_coord(const gu_pixel_coordinate, const gu_camera_pivot, gu_relative_coordinate *, const int) __attribute__((pure, nonnull));
bool pct_coord_to_rr_coord(const gu_percent_coordinate, const gu_camera_pivot, gu_relative_coordinate *, const int) __attribute__ ((pure, nonnull));

// Converting from the robot relative coordinate system to the image coordinate systems.
bool rr_coord_to_pct_coord(const gu_relative_coordinate, const gu_camera_pivot, const int, gu_percent_coordinate *) __attribute__((pure, nonnull));
bool rr_coord_to_px_coord(const gu_relative_coordinate, const gu_camera_pivot, const int, gu_pixel_coordinate *, pixels_u, pixels_u) __attribute__((pure, nonnull));

// Converting from the robot relative coordinate system to the field coordinate systems.
gu_cartesian_coordinate rr_coord_to_cartesian_coord(const gu_relative_coordinate) __attribute__((const));
gu_cartesian_coordinate rr_coord_to_cartesian_coord_from_source(const gu_relative_coordinate, const gu_cartesian_coordinate) __attribute__((const));
gu_field_coordinate rr_coord_to_field_coord(const gu_relative_coordinate, const degrees_t) __attribute__((const));
gu_field_coordinate rr_coord_to_field_coord_from_source(const gu_relative_coordinate, const gu_field_coordinate, const degrees_t) __attribute__((const));

// Converting from field coordinates to relative coordinates.
gu_relative_coordinate cartesian_coord_to_rr_coord(const gu_cartesian_coordinate) __attribute__((const));
gu_relative_coordinate cartesian_coord_to_rr_coord_from_source(const gu_cartesian_coordinate, const gu_cartesian_coordinate) __attribute__((const));
gu_relative_coordinate field_coord_to_rr_coord_to_target(const gu_field_coordinate, const gu_cartesian_coordinate) __attribute__((const));

#ifdef __cplusplus
}
#endif

#endif  /* CONVERSIONS_H */
