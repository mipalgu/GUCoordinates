/*
 * OptionalCameraCoordinate.cc 
 * gucoordinates 
 *
 * Created by Callum McColl on 27/07/2020.
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

#include "OptionalCameraCoordinate.hpp"

GU::OptionalCameraCoordinate::OptionalCameraCoordinate() NOEXCEPT {}

GU::OptionalCameraCoordinate::OptionalCameraCoordinate(const GU::CameraCoordinate t_value) NOEXCEPT
{
    set_has_value(true);
    set_value(t_value);
}

GU::OptionalCameraCoordinate::OptionalCameraCoordinate(const bool t_has_value, const GU::CameraCoordinate t_value) NOEXCEPT
{
    set_has_value(t_has_value);
    set_value(t_value);
}

GU::OptionalCameraCoordinate::OptionalCameraCoordinate(const GU::OptionalCameraCoordinate& other) NOEXCEPT
{
    set_has_value(other.has_value());
    set_value(other.value());
}

GU::OptionalCameraCoordinate::OptionalCameraCoordinate(const gu_optional_camera_coordinate &other) NOEXCEPT
{
    set_has_value(other.has_value);
    set_value(other.value);
}

#if __cplusplus >= 201103L
GU::OptionalCameraCoordinate::OptionalCameraCoordinate(GU::OptionalCameraCoordinate&& other) NOEXCEPT
{
    set_has_value(other.has_value());
    other.set_has_value(0.0f);
    set_value(other.value());
    other.set_value(GU::CameraCoordinate());
}
#endif

GU::OptionalCameraCoordinate::~OptionalCameraCoordinate() NOEXCEPT {}

GU::OptionalCameraCoordinate& GU::OptionalCameraCoordinate::operator=(const GU::OptionalCameraCoordinate& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_has_value(other.has_value());
    set_value(other.value());
    return *this;
}

GU::OptionalCameraCoordinate& GU::OptionalCameraCoordinate::operator=(const gu_optional_camera_coordinate& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_has_value(other.has_value);
    set_value(other.value);
    return *this;
}

#if __cplusplus >= 201103L
GU::OptionalCameraCoordinate& GU::OptionalCameraCoordinate::operator=(GU::OptionalCameraCoordinate&& other) NOEXCEPT
{
    if (&other == this)
    {
        return *this;
    }
    set_has_value(other.has_value());
    other.set_has_value(false);
    set_value(other.value());
    other.set_value(GU::CameraCoordinate());
    return *this;
}
#endif

bool GU::OptionalCameraCoordinate::has_value() const NOEXCEPT
{
    return gu_optional_camera_coordinate::has_value;
}

void GU::OptionalCameraCoordinate::set_has_value(const bool newValue) NOEXCEPT
{
    gu_optional_camera_coordinate::has_value = newValue;
}

GU::CameraCoordinate GU::OptionalCameraCoordinate::value() const NOEXCEPT
{
    return gu_optional_camera_coordinate::value;
}

void GU::OptionalCameraCoordinate::set_value(const GU::CameraCoordinate newValue) NOEXCEPT
{
    gu_optional_camera_coordinate::value = newValue;
}
