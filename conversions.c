/*
 * conversions.c 
 * gunavigation 
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

#include "conversions.h"
#include "hidden_conversions.h"
#include <math.h>
#include <float.h>

#include <stdio.h>

/*#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif*/
#ifndef M_PI_2
    #define M_PI_2 1.57079632679489661923
#endif

#define RELATIVE_COORD_MAX_DISTANCE f_to_mm_u(FLT_MAX)

gu_pixel_coordinate cam_coord_to_px_coord(const gu_camera_coordinate coord)
{
    const pixels_u maxX = coord.res_width - 1;
    const pixels_t x = px_u_to_px_t(coord.x) - d_to_px_t(floor(px_u_to_d(maxX) / 2.0));
    const pixels_u maxY = coord.res_height - 1;
    const pixels_t y = px_u_to_px_t(maxY - coord.y) - d_to_px_t(floor(px_u_to_d(maxY) / 2.0));
    const gu_pixel_coordinate out = { x, y, coord.res_width, coord.res_height };
    return out;
}

gu_camera_coordinate px_coord_to_cam_coord(const gu_pixel_coordinate coord)
{
    const pixels_u maxX = coord.res_width - 1;
    const pixels_u x = px_t_to_px_u(coord.x + d_to_px_t(floor(px_u_to_d(maxX) / 2.0)));
    const pixels_u maxY = coord.res_height - 1;
    const pixels_u y = px_t_to_px_u(-coord.y - d_to_px_t(floor(px_u_to_d(maxY) / 2.0)) + px_u_to_px_t(maxY));
    const gu_camera_coordinate out = { x, y, coord.res_width, coord.res_height };
    return out;
}

gu_percent_coordinate px_coord_to_pct_coord(const gu_pixel_coordinate coord)
{
    const pixels_t maxX = px_u_to_px_t(coord.res_width) - 1;
    const pixels_t maxY = px_u_to_px_t(coord.res_height) - 1;
    const double x = px_t_to_d(2 * coord.x - (maxX % 2)) / px_t_to_d(maxX);
    const double y = px_t_to_d(2 * coord.y - (maxY % 2)) / px_t_to_d(maxY);
    const gu_percent_coordinate newCoord = { d_to_pct_d(x), d_to_pct_d(y) };
    return newCoord;
}

gu_pixel_coordinate pct_coord_to_px_coord(const gu_percent_coordinate coord, const pixels_u res_width, const pixels_u res_height)
{
    const pixels_t maxX = px_u_to_px_t(res_width) - 1;
    const pixels_t maxY = px_u_to_px_t(res_height) - 1;
    const double pixelsX = (pct_d_to_d(coord.x) * px_t_to_d(maxX) + px_t_to_d(maxX % 2)) / 2.0;
    const double pixelsY = (pct_d_to_d(coord.y) * px_t_to_d(maxY) + px_t_to_d(maxY % 2)) / 2.0;
    const gu_pixel_coordinate newCoord = { d_to_px_t(pixelsX), d_to_px_t(pixelsY), res_width, res_height };
    return newCoord;
}

gu_relative_coordinate unsafe_pct_coord_to_rr_coord(const gu_percent_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset)
{
    return pct_coord_to_rr_coord(coord, camera_pivot, cameraOffset).value;
}

gu_optional_relative_coordinate pct_coord_to_rr_coord(const gu_percent_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset)
{
    const gu_camera camera = camera_pivot.cameras[cameraOffset];
    const degrees_d pitchToObject = camera_pivot.pitch + camera.vDirection - d_to_deg_d(pct_d_to_d(coord.y)) * (camera.vFov / 2.0);
    const degrees_d yaw = camera_pivot.yaw - d_to_deg_d(pct_d_to_d(coord.x)) * (camera.hFov / 2.0);
    // If the object is below/behind the camera.
    if (pitchToObject >= 90.0)
    {
        const gu_relative_coordinate out = { yaw, 0 };
        const gu_optional_relative_coordinate result = { false, out };
        return result;
    }
    const radians_d pitchRad = deg_d_to_rad_d(pitchToObject);
    const radians_d yawRad = deg_d_to_rad_d(yaw);
    const double cosYaw = cos(rad_d_to_d(yawRad));
    // Is the pitch above the horizontal or are we going to have to devide by zero later on?
    if (pitchToObject <= 0.0 || fabs(cosYaw) < 0.00001)
    {
        const gu_relative_coordinate out = { yaw, RELATIVE_COORD_MAX_DISTANCE };
        const gu_optional_relative_coordinate result = { false, out };
        return result;
    }
    const centimetres_d actualCameraHeight = gu_camera_pivot_calculate_camera_height(camera_pivot, cameraOffset);
    const double distance = cm_d_to_d(actualCameraHeight) * tan((M_PI_2) - rad_d_to_d(pitchRad)) / cosYaw;
    const centimetres_d outDistance = d_to_cm_d(distance) - camera.centerOffset;
    const gu_relative_coordinate out = { yaw, cm_d_to_mm_u(fabs(outDistance)) };
    const gu_optional_relative_coordinate result = { true, out };
    return result;
}

gu_percent_coordinate unsafe_rr_coord_to_pct_coord(const gu_relative_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset)
{
    const gu_camera camera = camera_pivot.cameras[cameraOffset];
    const degrees_d yaw = coord.direction - camera_pivot.yaw;
    const percent_d x = d_to_pct_d(deg_d_to_d(-yaw / (camera.hFov / 2.0)));
    const radians_d yawRad = deg_d_to_rad_d(coord.direction);
    const double frontDistance = cm_d_to_d(mm_u_to_cm_d(coord.distance)) * cos(rad_d_to_d(yawRad)) + cm_d_to_d(camera.centerOffset);
    const centimetres_d actualCameraHeight = gu_camera_pivot_calculate_camera_height(camera_pivot, cameraOffset);
    const degrees_d totalPitch = 90.0 - rad_d_to_deg_d(d_to_rad_d(atan2(frontDistance, cm_d_to_d(actualCameraHeight))));
    const degrees_d pitch = totalPitch - camera.vDirection - camera_pivot.pitch;
    const percent_d y = d_to_pct_d(deg_d_to_d(-pitch / (camera.vFov / 2.0)));
    const gu_percent_coordinate temp = { x, y };
    return temp;
}

gu_optional_percent_coordinate rr_coord_to_pct_coord(const gu_relative_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset)
{
    const gu_percent_coordinate temp = unsafe_rr_coord_to_pct_coord(coord, camera_pivot, cameraOffset);
    const bool has_value = temp.x >= -1.0 && temp.x <= 1.0 && temp.y >= -1.0 && temp.y <= 1.0;
    const gu_optional_percent_coordinate result = { has_value, temp };
    return result;
}

gu_percent_coordinate unsafe_clamped_rr_coord_to_pct_coord(const gu_relative_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset)
{
    gu_percent_coordinate temp = unsafe_rr_coord_to_pct_coord(coord, camera_pivot, cameraOffset);
    if (temp.x < -1.0)
    {
        temp.x = -1.0;
    } 
    else if (temp.x > 1.0) {
        temp.x = 1.0;
    }
    if (temp.y < -1.0)
    {
        temp.y = -1.0;
    }
    else if (temp.y > 1.0) {
        temp.y = 1.0;
    }
    return temp;
}

gu_percent_coordinate unsafe_clamped_tolerance_rr_coord_to_pct_coord(const gu_relative_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset, const percent_d tolerance)
{
    return clamped_tolerance_rr_coord_to_pct_coord(coord, camera_pivot, cameraOffset, tolerance).value;
}

gu_optional_percent_coordinate clamped_tolerance_rr_coord_to_pct_coord(const gu_relative_coordinate coord, const gu_camera_pivot camera_pivot, const int cameraOffset, const percent_d tolerance)
{
    gu_percent_coordinate temp = unsafe_rr_coord_to_pct_coord(coord, camera_pivot, cameraOffset);
    const percent_d lowerBound = -1.0 - tolerance;
    const percent_d upperBound = 1.0 + tolerance;
    if (temp.x < -1.0 && temp.x >= lowerBound)
    {
        temp.x = -1.0;
    } 
    else if (temp.x > 1.0 && temp.x <= upperBound) {
        temp.x = 1.0;
    }
    if (temp.y < -1.0 && temp.y >= lowerBound)
    {
        temp.y = -1.0;
    }
    else if (temp.y > 1.0 && temp.y <= upperBound) {
        temp.y = 1.0;
    }
    const bool has_value = temp.x >= -1.0 && temp.x <= 1.0 && temp.y >= -1.0 && temp.y <= 1.0;
    printf("temp: (%lf, %lf), has_value: %d\n", temp.x, temp.y, has_value);
    const gu_optional_percent_coordinate result = { has_value, temp };
    return result;
}

gu_cartesian_coordinate rr_coord_to_cartesian_coord(const gu_relative_coordinate coord)
{
    const double distance = cm_d_to_d(mm_u_to_cm_d(coord.distance));
    const double rads = rad_d_to_d(deg_d_to_rad_d(coord.direction));
    const gu_cartesian_coordinate out = {
        d_to_cm_t(distance * cos(rads)),
        d_to_cm_t(distance * sin(rads))
    };
    return out;
}

gu_cartesian_coordinate rr_coord_to_cartesian_coord_from_source(const gu_relative_coordinate coord, const gu_cartesian_coordinate source)
{
    gu_cartesian_coordinate temp = rr_coord_to_cartesian_coord(coord);
    temp.x = source.x + temp.x;
    temp.y = source.y + temp.y;
    return temp;
}

gu_cartesian_coordinate rr_coord_to_cartesian_coord_from_field(const gu_relative_coordinate coord, const gu_field_coordinate source)
{
    const gu_relative_coordinate offset = { coord.direction + source.heading, coord.distance };
    return rr_coord_to_cartesian_coord_from_source(offset, source.position);
}

gu_field_coordinate rr_coord_to_field_coord(const gu_relative_coordinate coord, const degrees_t heading)
{
    const gu_cartesian_coordinate temp = rr_coord_to_cartesian_coord(coord);
    gu_field_coordinate out;
    out.position = temp;
    out.heading = heading;
    return out;
}

gu_field_coordinate rr_coord_to_field_coord_from_source(const gu_relative_coordinate coord, const gu_field_coordinate source, const degrees_t heading)
{
    gu_relative_coordinate temp = coord;
    temp.direction = source.heading + temp.direction;
    const gu_cartesian_coordinate position = rr_coord_to_cartesian_coord_from_source(temp, source.position);
    const gu_field_coordinate out = { .position = position, .heading = heading };
    return out;
}

gu_relative_coordinate cartesian_coord_to_rr_coord(const gu_cartesian_coordinate target)
{
    const gu_cartesian_coordinate zero = { 0, 0 };
    return cartesian_coord_to_rr_coord_from_source(zero, target);
}

gu_relative_coordinate cartesian_coord_to_rr_coord_from_source(const gu_cartesian_coordinate source, const gu_cartesian_coordinate target)
{
    const radians_d angle = angle_between_points(source, target);
    const centimetres_d distance = distance_between_points(source, target);
    const gu_relative_coordinate out = {
        rad_d_to_deg_d(angle),
        cm_d_to_mm_u(fabs(distance))
    };
    return out;
}

gu_relative_coordinate field_coord_to_rr_coord_to_target(const gu_field_coordinate source, const gu_cartesian_coordinate target)
{
    gu_relative_coordinate out = cartesian_coord_to_rr_coord_from_source(source.position, target);
    out.direction = normalise_deg_t(deg_d_to_deg_t(out.direction - deg_t_to_deg_d(source.heading)));
    return out;
}

radians_d angle_between_points(const gu_cartesian_coordinate p1, const gu_cartesian_coordinate p2)
{
    const centimetres_t dx = p2.x - p1.x;
    const centimetres_t dy = p2.y - p1.y;
    if (0 == dx) {
        if (0 == dy) {
            return 0.0;
        }
        return dy > 0 ? d_to_rad_d(90.0) : d_to_rad_d(-90.0);
    }
    return d_to_rad_d(atan2(cm_t_to_d(dy), cm_t_to_d(dx)));
}

centimetres_d distance_between_points(const gu_cartesian_coordinate point1, const gu_cartesian_coordinate point2)
{
    const gu_cartesian_coordinate dpoint = { point2.x - point1.x, point2.y - point1.y };
    // Horizontal Lines
    if (0 == dpoint.x) {
        return fabs(cm_t_to_d(dpoint.y));
    }
    // Veritcal Lines
    if (0 == dpoint.y) {
        return fabs(cm_t_to_d(dpoint.x));
    }
    return d_to_cm_d(sqrt(cm_t_to_d(dpoint.x * dpoint.x) + cm_t_to_d(dpoint.y * dpoint.y)));
}

degrees_d normalise_deg_d(degrees_d angle) {
    if (angle + 180.0 == 0.0)
    {
        return 180.0;
    }
    if (angle < 0) {
        angle = fmod(angle, -360);
    } else {
        angle = fmod(angle, 360);
    }
    if (angle < -180) {
        return angle + 360;
    }
    if (angle > 180) {
        return angle - 360;
    }
    return angle;
}

degrees_t normalise_deg_t(degrees_t angle) {
   return deg_d_to_deg_t(normalise_deg_d(deg_t_to_deg_d(angle))); 
}

radians_d normalise_rad_d(radians_d angle) {
    return deg_d_to_rad_d(normalise_deg_d(rad_d_to_deg_d(angle)));
}
