/*
 * CameraCoordinate.cc 
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

#include "CameraCoordinate.hpp"
#include "conversions.h"

#if __cplusplus >= 201703L
#include <optional>
#endif

GU::CameraCoordinate::CameraCoordinate() {}

GU::CameraCoordinate::CameraCoordinate(pixels_u t_x, pixels_u t_y, pixels_u t_resWidth, pixels_u t_resHeight)
{
    set_x(t_x);
    set_y(t_y);
    set_resWidth(t_resWidth);
    set_resHeight(t_resHeight);
}

GU::CameraCoordinate::CameraCoordinate(const CameraCoordinate& other)
{
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
}

GU::CameraCoordinate::CameraCoordinate(const gu_camera_coordinate& other)
{
    set_x(other.x);
    set_y(other.y);
    set_resWidth(other.res_width);
    set_resHeight(other.res_height);
}

#if __cplusplus >= 201103L
GU::CameraCoordinate::CameraCoordinate(CameraCoordinate&& other)
{
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
    other.set_x(0);
    other.set_y(0);
    other.set_resWidth(0);
    other.set_resHeight(0);
}
#endif

GU::CameraCoordinate::~CameraCoordinate() {}

GU::CameraCoordinate& GU::CameraCoordinate::operator=(const CameraCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
    return *this;
}

GU::CameraCoordinate& GU::CameraCoordinate::operator=(const gu_camera_coordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_x(other.x);
    set_y(other.y);
    set_resWidth(other.res_width);
    set_resHeight(other.res_height);
    return *this;
}

#if __cplusplus >= 201103L
GU::CameraCoordinate& GU::CameraCoordinate::operator=(CameraCoordinate&& other)
{
    if (&other == this) {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
    other.set_x(0);
    other.set_y(0);
    other.set_resWidth(0);
    other.set_resHeight(0);
    return *this;
}
#endif

GU::PixelCoordinate GU::CameraCoordinate::pixelCoordinate() const
{
    return cam_coord_to_px_coord(*this);
}

GU::PercentCoordinate GU::CameraCoordinate::percentCoordinate() const
{
    return pixelCoordinate().percentCoordinate();
}

GU::RelativeCoordinate GU::CameraCoordinate::relativeCoordinate(const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return percentCoordinate().relativeCoordinate(cameraPivot, cameraOffset);
}

pixels_u GU::CameraCoordinate::x() const
{
    return gu_camera_coordinate::x;
}

void GU::CameraCoordinate::set_x(const pixels_u newValue)
{
    gu_camera_coordinate::x = newValue;
}

pixels_u GU::CameraCoordinate::y() const
{
    return gu_camera_coordinate::y;
}

void GU::CameraCoordinate::set_y(const pixels_u newValue)
{
    gu_camera_coordinate::y = newValue;
}

pixels_u GU::CameraCoordinate::resWidth() const
{
    return gu_camera_coordinate::res_width;
}

void GU::CameraCoordinate::set_resWidth(const pixels_u newValue)
{
    gu_camera_coordinate::res_width = newValue;
}

pixels_u GU::CameraCoordinate::resHeight() const
{
    return gu_camera_coordinate::res_height;
}

void GU::CameraCoordinate::set_resHeight(const pixels_u newValue)
{
    gu_camera_coordinate::res_height = newValue;
}

pixels_t GU::CameraCoordinate::xLowerBound() const
{
    return gu_camera_coordinate_x_lower_bound(*this);
}

pixels_t GU::CameraCoordinate::xUpperBound() const
{
    return gu_camera_coordinate_x_upper_bound(*this);
}

pixels_t GU::CameraCoordinate::yLowerBound() const
{
    return gu_camera_coordinate_y_lower_bound(*this);
}

pixels_t GU::CameraCoordinate::yUpperBound() const
{
    return gu_camera_coordinate_y_upper_bound(*this);
}

bool GU::CameraCoordinate::operator==(const CameraCoordinate &other) const
{
    return gu_camera_coordinate_equals(*this, other);
}

bool GU::CameraCoordinate::operator!=(const CameraCoordinate &other) const
{
    return !(*this == other);
}

bool GU::CameraCoordinate::operator==(const gu_camera_coordinate &other) const
{
    return gu_camera_coordinate_equals(*this, other);
}

bool GU::CameraCoordinate::operator!=(const gu_camera_coordinate &other) const
{
    return !(*this == other);
}
