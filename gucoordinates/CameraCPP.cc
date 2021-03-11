/*
 * Camera.cc 
 * guvision_utils 
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

#include "Camera.hpp"

GU::Camera::Camera() NOEXCEPT {}

GU::Camera::Camera(centimetres_d t_height, centimetres_d t_centerOffset, degrees_d t_vDirection, degrees_d t_vFov, degrees_d t_hFov) NOEXCEPT
{
    set_height(t_height);
    set_centerOffset(t_centerOffset);
    set_vDirection(t_vDirection);
    set_vFov(t_vFov);
    set_hFov(t_hFov);
}

GU::Camera::Camera(const Camera& other) NOEXCEPT
{
    set_height(other.height());
    set_centerOffset(other.centerOffset());
    set_vDirection(other.vDirection());
    set_vFov(other.vFov());
    set_hFov(other.hFov());
}

GU::Camera::Camera(const gu_camera& other) NOEXCEPT
{
    set_height(other.height);
    set_centerOffset(other.centerOffset);
    set_vDirection(other.vDirection);
    set_vFov(other.vFov);
    set_hFov(other.hFov);
}

#if __cplusplus >= 201103L
GU::Camera::Camera(Camera&& other) NOEXCEPT
{
    set_height(other.height());
    set_centerOffset(other.centerOffset());
    set_vDirection(other.vDirection());
    set_vFov(other.vFov());
    set_hFov(other.hFov());
}
#endif

GU::Camera::~Camera() NOEXCEPT {}

GU::Camera& GU::Camera::operator=(const Camera& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_height(other.height());
    set_centerOffset(other.centerOffset());
    set_vDirection(other.vDirection());
    set_vFov(other.vFov());
    set_hFov(other.hFov());
    return *this;
}

GU::Camera& GU::Camera::operator=(const gu_camera& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_height(other.height);
    set_centerOffset(other.centerOffset);
    set_vDirection(other.vDirection);
    set_vFov(other.vFov);
    set_hFov(other.hFov);
    return *this;
}

#if __cplusplus >= 201103L
GU::Camera& GU::Camera::operator=(Camera&& other) NOEXCEPT
{
    if (&other == this) {
        return *this;
    }
    set_height(other.height());
    set_centerOffset(other.centerOffset());
    set_vDirection(other.vDirection());
    set_vFov(other.vFov());
    set_hFov(other.hFov());
    return *this;
}

GU::Camera& GU::Camera::operator=(gu_camera&& other) NOEXCEPT
{
    if (&other == this) {
        return *this;
    }
    set_height(other.height);
    set_centerOffset(other.centerOffset);
    set_vDirection(other.vDirection);
    set_vFov(other.vFov);
    set_hFov(other.hFov);
    other.height = 0.0;
    other.centerOffset = 0.0;
    other.vDirection = 0.0;
    other.vFov = 0.0;
    other.hFov = 0.0;
    return *this;
}
#endif

centimetres_d GU::Camera::height() const NOEXCEPT
{
    return gu_camera::height;
}

void GU::Camera::set_height(const centimetres_d newValue) NOEXCEPT
{
    gu_camera::height = newValue;
}

centimetres_d GU::Camera::centerOffset() const NOEXCEPT
{
    return gu_camera::centerOffset;
}

void GU::Camera::set_centerOffset(const centimetres_d newValue) NOEXCEPT
{
    gu_camera::centerOffset = newValue;
}

degrees_d GU::Camera::vDirection() const NOEXCEPT
{
    return gu_camera::vDirection;
}

void GU::Camera::set_vDirection(const degrees_d newValue) NOEXCEPT
{
    gu_camera::vDirection = newValue;
}

degrees_d GU::Camera::vFov() const NOEXCEPT
{
    return gu_camera::vFov;
}

void GU::Camera::set_vFov(const degrees_d newValue) NOEXCEPT
{
    gu_camera::vFov = newValue;
}

degrees_d GU::Camera::hFov() const NOEXCEPT
{
    return gu_camera::hFov;
}

void GU::Camera::set_hFov(const degrees_d newValue) NOEXCEPT
{
    gu_camera::hFov = newValue;
}

bool GU::Camera::operator==(const Camera &other) const NOEXCEPT
{
    return gu_camera_equals(*this, other, 0.0001);
}

bool GU::Camera::operator!=(const Camera &other) const NOEXCEPT
{
    return !(*this == other);
}

bool GU::Camera::operator==(const gu_camera &other) const NOEXCEPT
{
    return gu_camera_equals(*this, other, 0.0001);
}

bool GU::Camera::operator!=(const gu_camera &other) const NOEXCEPT
{
    return !(*this == other);
}
