/*
 * Robot.cc 
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

#include "Robot.hpp"
#include "conversions.h"

#include <string.h>

GU::Robot::Robot(): gu_robot() {}

GU::Robot::Robot(degrees_f t_headPitch, degrees_f t_headYaw, const gu_camera t_cameras[GU_ROBOT_NUM_CAMERAS], const centimetres_f t_cameraHeightOffsets[GU_ROBOT_NUM_CAMERAS], int t_numCameras)
{
    set_headPitch(t_headPitch);
    set_headYaw(t_headYaw);
    set_cameras(t_cameras);
    set_cameraHeightOffsets(t_cameraHeightOffsets);
    set_numCameras(t_numCameras);
}

GU::Robot::Robot(const Robot& other)
{
    set_headPitch(other.headPitch());
    set_headYaw(other.headYaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
} 

GU::Robot::Robot(const gu_robot& other)
{
    set_headPitch(other.headPitch);
    set_headYaw(other.headYaw);
    set_cameras(other.cameras);
    set_cameraHeightOffsets(other.cameraHeightOffsets);
    set_numCameras(other.numCameras);
}

#ifdef __cpp_rvalue_references
GU::Robot::Robot(Robot&& other)
{
    set_headPitch(other.headPitch());
    set_headYaw(other.headYaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    other.set_headPitch(0.0f);
    other.set_headYaw(0.0f);
    static const gu_camera newCameras[GU_ROBOT_NUM_CAMERAS] = {};
    static const centimetres_f newCameraHeightOffsets[GU_ROBOT_NUM_CAMERAS] = {};
    other.set_cameras(newCameras);
    other.set_cameraHeightOffsets(newCameraHeightOffsets);
    other.set_numCameras(0);
}
#endif

GU::Robot::~Robot() {}

GU::Robot& GU::Robot::operator=(const Robot& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_headPitch(other.headPitch());
    set_headYaw(other.headYaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    return *this;
}

GU::Robot& GU::Robot::operator=(const gu_robot& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_headPitch(other.headPitch);
    set_headYaw(other.headYaw);
    set_cameras(other.cameras);
    set_cameraHeightOffsets(other.cameraHeightOffsets);
    set_numCameras(other.numCameras);
    return *this;
}

#ifdef __cpp_rvalue_references
GU::Robot& GU::Robot::operator=(Robot&& other)
{
    if (&other == this) {
        return *this;
    }
    set_headPitch(other.headPitch());
    set_headYaw(other.headYaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    other.set_headPitch(0.0f);
    other.set_headYaw(0.0f);
    static const gu_camera newCameras[GU_ROBOT_NUM_CAMERAS] = {};
    static const centimetres_f newCameraHeightOffsets[GU_ROBOT_NUM_CAMERAS] = {};
    other.set_cameras(newCameras);
    other.set_cameraHeightOffsets(newCameraHeightOffsets);
    other.set_numCameras(0);
    return *this;
}
#endif

degrees_f GU::Robot::headPitch() const
{
    return gu_robot::headPitch;
}

void GU::Robot::set_headPitch(const degrees_f newValue)
{
    gu_robot::headPitch = newValue;
}

degrees_f GU::Robot::headYaw() const
{
    return gu_robot::headYaw;
}

void GU::Robot::set_headYaw(const degrees_f newValue)
{
    gu_robot::headYaw = newValue;
}

const gu_camera * GU::Robot::cameras() const
{
    return &gu_robot::cameras[0];
}

void GU::Robot::set_cameras(const gu_camera newValue[GU_ROBOT_NUM_CAMERAS])
{
    memcpy(gu_robot::cameras, newValue, GU_ROBOT_NUM_CAMERAS * sizeof(gu_camera));
}

GU::Camera GU::Robot::camera(const int index) const
{
    return gu_robot::cameras[index];
}

void GU::Robot::set_camera(const int index, const GU::Camera newValue)
{
    gu_robot::cameras[index] = newValue;
}

const centimetres_f * GU::Robot::cameraHeightOffsets() const
{
    return gu_robot::cameraHeightOffsets;
}

void GU::Robot::set_cameraHeightOffsets(const centimetres_f newValue[GU_ROBOT_NUM_CAMERAS])
{
    memcpy(gu_robot::cameraHeightOffsets, newValue, GU_ROBOT_NUM_CAMERAS * sizeof(centimetres_f));
}

centimetres_f GU::Robot::cameraHeightOffset(const int index) const
{
    return gu_robot::cameraHeightOffsets[index];
}

void GU::Robot::set_cameraHeightOffset(const int index, const centimetres_f newValue)
{
    gu_robot::cameraHeightOffsets[index] = newValue;
}

int GU::Robot::numCameras() const
{
    return gu_robot::numCameras;
}

void GU::Robot::set_numCameras(const int newValue)
{
    gu_robot::numCameras = newValue;
}

bool GU::Robot::operator==(const Robot &other) const
{
    return gu_robot_equals(*this, other, 0.0001f);
}

bool GU::Robot::operator!=(const Robot &other) const
{
    return !(*this == other);
}

bool GU::Robot::operator==(const gu_robot &other) const
{
    return gu_robot_equals(*this, other, 0.0001f);
}

bool GU::Robot::operator!=(const gu_robot &other) const
{
    return !(*this == other);
}
