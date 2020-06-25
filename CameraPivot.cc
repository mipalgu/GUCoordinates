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

GU::CameraPivot::CameraPivot() {}

GU::CameraPivot::CameraPivot(degrees_f t_pitch, degrees_f t_yaw, const gu_camera t_cameras[GU_CAMERA_PIVOT_NUM_CAMERAS], const centimetres_f t_cameraHeightOffsets[GU_CAMERA_PIVOT_NUM_CAMERAS], int t_numCameras)
{
    set_pitch(t_pitch);
    set_yaw(t_yaw);
    set_cameras(t_cameras);
    set_cameraHeightOffsets(t_cameraHeightOffsets);
    set_numCameras(t_numCameras);
}

GU::CameraPivot::CameraPivot(const CameraPivot& other)
{
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
} 

GU::CameraPivot::CameraPivot(const gu_camera_pivot& other)
{
    set_pitch(other.pitch);
    set_yaw(other.yaw);
    set_cameras(other.cameras);
    set_cameraHeightOffsets(other.cameraHeightOffsets);
    set_numCameras(other.numCameras);
}

#if __cplusplus >= 201103L
GU::CameraPivot::CameraPivot(CameraPivot&& other)
{
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    other.set_pitch(0.0f);
    other.set_yaw(0.0f);
    static const gu_camera newCameras[GU_CAMERA_PIVOT_NUM_CAMERAS] = {};
    static const centimetres_f newCameraHeightOffsets[GU_CAMERA_PIVOT_NUM_CAMERAS] = {};
    other.set_cameras(newCameras);
    other.set_cameraHeightOffsets(newCameraHeightOffsets);
    other.set_numCameras(0);
}
#endif

GU::CameraPivot::~CameraPivot() {}

GU::CameraPivot& GU::CameraPivot::operator=(const CameraPivot& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    return *this;
}

GU::CameraPivot& GU::CameraPivot::operator=(const gu_camera_pivot& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_pitch(other.pitch);
    set_yaw(other.yaw);
    set_cameras(other.cameras);
    set_cameraHeightOffsets(other.cameraHeightOffsets);
    set_numCameras(other.numCameras);
    return *this;
}

#if __cplusplus >= 201103L
GU::CameraPivot& GU::CameraPivot::operator=(CameraPivot&& other)
{
    if (&other == this) {
        return *this;
    }
    set_pitch(other.pitch());
    set_yaw(other.yaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    other.set_pitch(0.0f);
    other.set_yaw(0.0f);
    static const gu_camera newCameras[GU_CAMERA_PIVOT_NUM_CAMERAS] = {};
    static const centimetres_f newCameraHeightOffsets[GU_CAMERA_PIVOT_NUM_CAMERAS] = {};
    other.set_cameras(newCameras);
    other.set_cameraHeightOffsets(newCameraHeightOffsets);
    other.set_numCameras(0);
    return *this;
}
#endif

degrees_f GU::CameraPivot::pitch() const
{
    return gu_camera_pivot::pitch;
}

void GU::CameraPivot::set_pitch(const degrees_f newValue)
{
    gu_camera_pivot::pitch = newValue;
}

degrees_f GU::CameraPivot::yaw() const
{
    return gu_camera_pivot::yaw;
}

void GU::CameraPivot::set_yaw(const degrees_f newValue)
{
    gu_camera_pivot::yaw = newValue;
}

const gu_camera * GU::CameraPivot::cameras() const
{
    return &gu_camera_pivot::cameras[0];
}

void GU::CameraPivot::set_cameras(const gu_camera newValue[GU_CAMERA_PIVOT_NUM_CAMERAS])
{
    memcpy(gu_camera_pivot::cameras, newValue, GU_CAMERA_PIVOT_NUM_CAMERAS * sizeof(gu_camera));
}

GU::Camera GU::CameraPivot::camera(const int index) const
{
    return gu_camera_pivot::cameras[index];
}

void GU::CameraPivot::set_camera(const int index, const GU::Camera newValue)
{
    gu_camera_pivot::cameras[index] = newValue;
}

const centimetres_f * GU::CameraPivot::cameraHeightOffsets() const
{
    return gu_camera_pivot::cameraHeightOffsets;
}

void GU::CameraPivot::set_cameraHeightOffsets(const centimetres_f newValue[GU_CAMERA_PIVOT_NUM_CAMERAS])
{
    memcpy(gu_camera_pivot::cameraHeightOffsets, newValue, GU_CAMERA_PIVOT_NUM_CAMERAS * sizeof(centimetres_f));
}

centimetres_f GU::CameraPivot::cameraHeightOffset(const int index) const
{
    return gu_camera_pivot::cameraHeightOffsets[index];
}

void GU::CameraPivot::set_cameraHeightOffset(const int index, const centimetres_f newValue)
{
    gu_camera_pivot::cameraHeightOffsets[index] = newValue;
}

int GU::CameraPivot::numCameras() const
{
    return gu_camera_pivot::numCameras;
}

void GU::CameraPivot::set_numCameras(const int newValue)
{
    gu_camera_pivot::numCameras = newValue;
}

bool GU::CameraPivot::operator==(const CameraPivot &other) const
{
    return gu_camera_pivot_equals(*this, other, 0.0001f);
}

bool GU::CameraPivot::operator!=(const CameraPivot &other) const
{
    return !(*this == other);
}

bool GU::CameraPivot::operator==(const gu_camera_pivot &other) const
{
    return gu_camera_pivot_equals(*this, other, 0.0001f);
}

bool GU::CameraPivot::operator!=(const gu_camera_pivot &other) const
{
    return !(*this == other);
}
