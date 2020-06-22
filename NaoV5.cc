/*
 * NaoV5.cc
 * build
 *
 * Created by Callum McColl on 22/6/20.
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

#include "NaoV5.hpp"

#include <guunits/guunits.h>
#include "robot.h"

GU::NaoV5::NaoV5(): GU::Robot(GU_NAO_V5_ROBOT(0.0f, 0.0f)) {}

GU::NaoV5::NaoV5(const NaoV5& other): GU::Robot(other) {}

GU::NaoV5::NaoV5(const ::wb_sensors_torsojointsensors& joints): GU::Robot(GU_NAO_V5_ROBOT(rad_f_to_deg_f(f_to_rad_f(joints.HeadPitch())), rad_f_to_deg_f(f_to_rad_f(joints.HeadYaw())))) {}

#ifdef __cpp_rvalue_references
GU::NaoV5::NaoV5(NaoV5&& other): GU::Robot(other) {}
#endif

GU::NaoV5::~NaoV5() {}

GU::NaoV5& GU::NaoV5::operator=(const GU::NaoV5& other) {
    set_headPitch(other.headPitch());
    set_headYaw(other.headYaw());
    set_cameras(other.cameras());
    set_cameraHeightOffsets(other.cameraHeightOffsets());
    set_numCameras(other.numCameras());
    return *this;
}

GU::NaoV5& GU::NaoV5::operator=(const ::wb_sensors_torsojointsensors& joints)
{
    set_headPitch(rad_f_to_deg_f(f_to_rad_f(joints.HeadPitch())));
    set_headYaw(rad_f_to_deg_f(f_to_rad_f(joints.HeadYaw())));
    return *this;
}

#ifdef __cpp_rvalue_references
GU::NaoV5& GU::NaoV5::operator=(GU::NaoV5&& other) {
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
