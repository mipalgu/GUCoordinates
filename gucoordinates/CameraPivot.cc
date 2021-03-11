/*
 * CameraPivot.cc 
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

#include "CameraPivot.hpp"
#include "conversions.h"

#include <string.h>

GU::CameraPivot::CameraPivot() NOEXCEPT {}

GU::CameraPivot::CameraPivot(const degrees_d t_pitch, const degrees_d t_yaw, const centimetres_d t_height, const gu_camera t_cameras[GU_CAMERA_PIVOT_NUM_CAMERAS], int t_numCameras) NOEXCEPT
{
    set_pitch(t_pitch);
    set_yaw(t_yaw);
    set_height(t_height);
    set_cameras(t_cameras);
    set_numCameras(t_numCameras);
}

GU::CameraPivot::CameraPivot(const CameraPivot& other) NOEXCEPT
{
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_height(other.height());
    set_cameras(other.cameras());
    set_numCameras(other.numCameras());
} 

GU::CameraPivot::CameraPivot(const gu_camera_pivot& other) NOEXCEPT
{
    set_pitch(other.pitch);
    set_yaw(other.yaw);
    set_height(other.height);
    set_cameras(other.cameras);
    set_numCameras(other.numCameras);
}

#if __cplusplus >= 201103L
GU::CameraPivot::CameraPivot(CameraPivot&& other) NOEXCEPT
{
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_height(other.height());
    set_cameras(other.cameras());
    set_numCameras(other.numCameras());
    other.set_pitch(0.0);
    other.set_yaw(0.0);
    other.set_height(0.0);
    static const gu_camera newCameras[GU_CAMERA_PIVOT_NUM_CAMERAS] = {};
    other.set_cameras(newCameras);
    other.set_numCameras(0);
}
#endif

GU::CameraPivot::~CameraPivot() NOEXCEPT {}

GU::CameraPivot& GU::CameraPivot::operator=(const CameraPivot& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_height(other.height());
    set_cameras(other.cameras());
    set_numCameras(other.numCameras());
    return *this;
}

GU::CameraPivot& GU::CameraPivot::operator=(const gu_camera_pivot& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_pitch(other.pitch);
    set_yaw(other.yaw);
    set_height(other.height);
    set_cameras(other.cameras);
    set_numCameras(other.numCameras);
    return *this;
}

#if __cplusplus >= 201103L
GU::CameraPivot& GU::CameraPivot::operator=(CameraPivot&& other) NOEXCEPT
{
    if (&other == this) {
        return *this;
    }
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_height(other.height());
    set_cameras(other.cameras());
    set_numCameras(other.numCameras());
    other.set_pitch(0.0);
    other.set_yaw(0.0);
    other.set_height(0.0);
    static const gu_camera newCameras[GU_CAMERA_PIVOT_NUM_CAMERAS] = {};
    other.set_cameras(newCameras);
    other.set_numCameras(0);
    return *this;
}
#endif

degrees_d GU::CameraPivot::pitch() const NOEXCEPT
{
    return gu_camera_pivot::pitch;
}

void GU::CameraPivot::set_pitch(const degrees_d newValue) NOEXCEPT
{
    gu_camera_pivot::pitch = newValue;
}

degrees_d GU::CameraPivot::yaw() const NOEXCEPT
{
    return gu_camera_pivot::yaw;
}

void GU::CameraPivot::set_yaw(const degrees_d newValue) NOEXCEPT
{
    gu_camera_pivot::yaw = newValue;
}


centimetres_d GU::CameraPivot::height() const NOEXCEPT
{
    return gu_camera_pivot::height;
}

void GU::CameraPivot::set_height(const centimetres_d newValue) NOEXCEPT
{
    gu_camera_pivot::height = newValue;
}

const gu_camera * GU::CameraPivot::cameras() const NOEXCEPT
{
    return &gu_camera_pivot::cameras[0];
}

void GU::CameraPivot::set_cameras(const gu_camera newValue[GU_CAMERA_PIVOT_NUM_CAMERAS]) NOEXCEPT
{
    memcpy(gu_camera_pivot::cameras, newValue, GU_CAMERA_PIVOT_NUM_CAMERAS * sizeof(gu_camera));
}

GU::Camera GU::CameraPivot::camera(const int index) const NOEXCEPT
{
    return gu_camera_pivot::cameras[index];
}

void GU::CameraPivot::set_camera(const int index, const GU::Camera newValue) NOEXCEPT
{
    gu_camera_pivot::cameras[index] = newValue;
}

int GU::CameraPivot::numCameras() const NOEXCEPT
{
    return gu_camera_pivot::numCameras;
}

void GU::CameraPivot::set_numCameras(const int newValue) NOEXCEPT
{
    gu_camera_pivot::numCameras = newValue;
}

bool GU::CameraPivot::operator==(const CameraPivot &other) const NOEXCEPT
{
    return gu_camera_pivot_equals(*this, other, 0.0001);
}

bool GU::CameraPivot::operator!=(const CameraPivot &other) const NOEXCEPT
{
    return !(*this == other);
}

bool GU::CameraPivot::operator==(const gu_camera_pivot &other) const NOEXCEPT
{
    return gu_camera_pivot_equals(*this, other, 0.0001);
}

bool GU::CameraPivot::operator!=(const gu_camera_pivot &other) const NOEXCEPT
{
    return !(*this == other);
}
