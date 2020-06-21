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

#include <math.h>
#include <stdio.h>


gu_pixel_coordinate cam_coord_to_px_coord(const gu_camera_coordinate coord)
{
    const pixels_u maxX = coord.res_width - 1;
    const pixels_t x = px_u_to_px_t(coord.x) - f_to_px_t(floorf(px_u_to_f(maxX) / 2.0f));
    const pixels_u maxY = coord.res_height - 1;
    const pixels_t y = px_u_to_px_t(maxY - coord.y) - f_to_px_t(floorf(px_u_to_f(maxY) / 2.0f));
    const gu_pixel_coordinate out = { x, y, coord.res_width, coord.res_height };
    return out;
}

gu_camera_coordinate px_coord_to_cam_coord(const gu_pixel_coordinate coord)
{
    const pixels_u maxX = coord.res_width - 1;
    const pixels_u x = px_t_to_px_u(coord.x + f_to_px_t(floorf(px_u_to_f(maxX) / 2.0f)));
    const pixels_u maxY = coord.res_height - 1;
    const pixels_u y = px_t_to_px_u(-coord.y - f_to_px_t(floorf(px_u_to_f(maxY) / 2.0f)) + px_u_to_px_t(maxY));
    const gu_camera_coordinate out = { x, y, coord.res_width, coord.res_height };
    return out;
}

gu_percent_coordinate px_coord_to_pct_coord(const gu_pixel_coordinate coord)
{
    const pixels_t maxX = px_u_to_px_t(coord.res_width) - 1;
    const pixels_t maxY = px_u_to_px_t(coord.res_height) - 1;
    const float x = px_t_to_f(2 * coord.x - (maxX % 2)) / px_t_to_f(maxX);
    const float y = px_t_to_f(2 * coord.y - (maxY % 2)) / px_t_to_f(maxY);
    const gu_percent_coordinate newCoord = { f_to_pct_f(x), f_to_pct_f(y) };
    return newCoord;
}

gu_pixel_coordinate pct_coord_to_px_coord(const gu_percent_coordinate coord, const pixels_u res_width, const pixels_u res_height)
{
    const pixels_t maxX = px_u_to_px_t(res_width) - 1;
    const pixels_t maxY = px_u_to_px_t(res_height) - 1;
    const float pixelsX = (pct_f_to_f(coord.x) * px_t_to_f(maxX) + px_t_to_f(maxX % 2)) / 2.0f;
    const float pixelsY = (pct_f_to_f(coord.y) * px_t_to_f(maxY) + px_t_to_f(maxY % 2)) / 2.0f;
    const gu_pixel_coordinate newCoord = { f_to_px_t(pixelsX), f_to_px_t(pixelsY), res_width, res_height };
    return newCoord;
}


bool px_coord_to_rr_coord(const gu_pixel_coordinate coord, const gu_robot robot, gu_relative_coordinate * out, const int cameraOffset)
{
    return pct_coord_to_rr_coord(px_coord_to_pct_coord(coord), robot, out, cameraOffset);
}

bool pct_coord_to_rr_coord(const gu_percent_coordinate coord, const gu_robot robot, gu_relative_coordinate * out, const int cameraOffset)
{
    const gu_camera camera = robot.cameras[cameraOffset];
    const degrees_f pitch = robot.headPitch + camera.vDirection - f_to_deg_f(pct_f_to_f(coord.y)) * (camera.vFov / 2.0f);
    if (pitch >= 90.0f || pitch <= 0.0f)
    {
        return false;
    }
    const degrees_f yaw = robot.headYaw - f_to_deg_f(pct_f_to_f(coord.x)) * (camera.hFov / 2.0f);
    const radians_f pitchRad = deg_f_to_rad_f(pitch);
    const radians_f yawRad = deg_f_to_rad_f(yaw);
    const centimetres_f relativeHeightToCameraFromNeck = camera.height - robot.cameraHeightOffsets[cameraOffset];
    const float cosPitch = cosf(rad_f_to_f(pitchRad));
    const float sinPitch = sinf(rad_f_to_f(pitchRad));
    const float cosYaw = cosf(rad_f_to_f(yawRad));
    // Avoid division by zero later on.
    if (cosYaw == 0.0f)
    {
        return false;
    }
    const centimetres_f actualCameraHeight = (camera.height - relativeHeightToCameraFromNeck * f_to_cm_f(1.0f - cosPitch)) - camera.centerOffset * f_to_cm_f(sinPitch); 
    const float distance = cm_f_to_f(actualCameraHeight) * tanf(((float) M_PI_2) - rad_f_to_f(pitchRad)) / cosYaw;
    out->distance = f_to_cm_u(fabsf(distance)) - cm_f_to_cm_u(camera.centerOffset);
    out->direction = deg_f_to_deg_t(yaw);
    return true;
}

bool rr_coord_to_pct_coord(const gu_relative_coordinate coord, const gu_robot robot, const int cameraOffset, gu_percent_coordinate * out)
{
    const gu_camera camera = robot.cameras[cameraOffset];
    const degrees_f yaw = deg_t_to_deg_f(coord.direction) - robot.headYaw;
    const percent_f x = f_to_pct_f(deg_f_to_f(-yaw / (camera.hFov / 2.0f)));
    if (x < -1.0f || x > 1.0f)
    {
        return false;
    }
    const radians_f yawRad = deg_f_to_rad_f(yaw);
    const float frontDistance = cm_u_to_f(coord.distance) * cosf(rad_f_to_f(yawRad)) ;//+ cm_f_to_f(camera.centerOffset);
    const centimetres_f relativeHeightToCameraFromNeck = camera.height - robot.cameraHeightOffsets[cameraOffset];
    const float cosPitch = cosf(deg_f_to_rad_f(robot.headPitch));
    const float sinPitch = sinf(deg_f_to_rad_f(robot.headPitch));
    // Avoid division by 0 later
    if (cosPitch == 0.0f) {
        return false;
    }
    const centimetres_f actualCameraHeight = (camera.height - relativeHeightToCameraFromNeck * f_to_cm_f(1.0f - cosPitch)) - camera.centerOffset * f_to_cm_f(sinPitch); 
    const degrees_f totalPitch = rad_f_to_deg_f(f_to_rad_f(atan2f(cm_f_to_f(actualCameraHeight), frontDistance)));
    const degrees_f pitch = totalPitch - camera.vDirection - robot.headPitch;
    const percent_f y = f_to_pct_f(deg_f_to_f(-pitch / (camera.vFov / 2.0f)));
    if (y < -1.0f || y > 1.0f)
    {
        return false;
    }
    out->x = x;
    out->y = y;
    return true;
}

bool rr_coord_to_px_coord(const gu_relative_coordinate coord, const gu_robot robot, const int cameraOffset, gu_pixel_coordinate * out, pixels_u res_width, pixels_u res_height)
{
    gu_percent_coordinate temp = {};
    if (!rr_coord_to_pct_coord(coord, robot, cameraOffset, &temp))
    {
        return false;
    }
    gu_pixel_coordinate converted = pct_coord_to_px_coord(temp, res_width, res_height);
    out->x = converted.x;
    out->y = converted.y;
    out->res_width = converted.res_width;
    out->res_height = converted.res_height;
    return true;
}

gu_cartesian_coordinate rr_coord_to_cartesian_coord(const gu_relative_coordinate coord)
{
    gu_cartesian_coordinate out;
    out.x = f_to_cm_t(cm_u_to_f(coord.distance) * sinf(deg_t_to_f(coord.direction)));
    out.y = f_to_cm_t(cm_u_to_f(coord.distance) * sinf(deg_t_to_f(coord.direction)));
    return out;
}

gu_cartesian_coordinate rr_coord_to_cartesian_coord_from_source(const gu_relative_coordinate coord, const gu_cartesian_coordinate source)
{
    gu_cartesian_coordinate temp = rr_coord_to_cartesian_coord(coord);
    temp.x = source.x + temp.x;
    temp.y = source.y + temp.y;
    return temp;
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
    gu_field_coordinate out = rr_coord_to_field_coord(temp, heading);
    out.position.x = source.position.x + out.position.x;
    out.position.y = source.position.y + out.position.y;
    return out;
}








