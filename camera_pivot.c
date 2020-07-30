/*
 * camera_pivot.c 
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

#include "camera_pivot.h"

#include <stdbool.h>
#include <math.h>

bool gu_camera_pivot_equals(const gu_camera_pivot lhs, const gu_camera_pivot rhs, const double tolerance)
{
    const bool headEqual = fabs(deg_d_to_d(lhs.pitch) - deg_d_to_d(rhs.pitch)) <= tolerance
        && fabs(deg_d_to_d(lhs.yaw) - deg_d_to_d(rhs.yaw)) <= tolerance
        && fabs(cm_d_to_d(lhs.height) - cm_d_to_d(rhs.height)) <= tolerance;
    if (!headEqual || lhs.numCameras != rhs.numCameras)
    {
        return false;
    }
    for (int i = 0; i < lhs.numCameras; i++)
    {
        if (!gu_camera_equals(lhs.cameras[i], rhs.cameras[i], tolerance))
        {
            return false;
        }
    }
    return true;
}

centimetres_d gu_camera_pivot_calculate_camera_height(const gu_camera_pivot camera_pivot, const int cameraOffset)
{
    const gu_camera camera = camera_pivot.cameras[cameraOffset];
    const centimetres_d totalHeight = camera_pivot.height + camera.height;
    const double cosPitch = cos(deg_d_to_rad_d(camera_pivot.pitch));
    const double sinPitch = sin(deg_d_to_rad_d(camera_pivot.pitch));
    return (totalHeight - camera.height * d_to_cm_d(1.0 - cosPitch)) - camera.centerOffset * d_to_cm_d(sinPitch); 
}
