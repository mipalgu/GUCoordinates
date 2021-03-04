/*
 * PixelCoordinate.cc 
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

#include "PixelCoordinate.hpp"
#include "conversions.h"

#if __cplusplus >= 201703L
#include <optional>
#endif

GU::PixelCoordinate::PixelCoordinate() NOEXCEPT: gu_pixel_coordinate() {}

GU::PixelCoordinate::PixelCoordinate(pixels_t t_x, pixels_t t_y, pixels_u t_resWidth, pixels_u t_resHeight) NOEXCEPT
{
    set_x(t_x);
    set_y(t_y);
    set_resWidth(t_resWidth);
    set_resHeight(t_resHeight);
}

GU::PixelCoordinate::PixelCoordinate(const PixelCoordinate& other) NOEXCEPT
{
    set_x(other.x());
    set_y(other.y());
    set_resWidth(other.resWidth());
    set_resHeight(other.resHeight());
}

GU::PixelCoordinate::PixelCoordinate(const gu_pixel_coordinate& other) NOEXCEPT
{
    set_x(other.x);
    set_y(other.y);
    set_resWidth(other.res_width);
    set_resHeight(other.res_height);
}

GU::PixelCoordinate::~PixelCoordinate() NOEXCEPT {}

GU::PixelCoordinate& GU::PixelCoordinate::operator=(const PixelCoordinate& other) NOEXCEPT
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

GU::PixelCoordinate& GU::PixelCoordinate::operator=(const gu_pixel_coordinate& other) NOEXCEPT
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

GU::CameraCoordinate GU::PixelCoordinate::cameraCoordinate() const NOEXCEPT
{
    return px_coord_to_cam_coord(*this);
}

GU::PercentCoordinate GU::PixelCoordinate::percentCoordinate() const NOEXCEPT
{
    return px_coord_to_pct_coord(*this);
}

GU::RelativeCoordinate GU::PixelCoordinate::relativeCoordinate(const GU::CameraPivot & cameraPivot, const int cameraOffset) const NOEXCEPT
{
    return percentCoordinate().relativeCoordinate(cameraPivot, cameraOffset);
}

pixels_t GU::PixelCoordinate::x() const NOEXCEPT
{
    return gu_pixel_coordinate::x;
}

void GU::PixelCoordinate::set_x(const pixels_t newValue) NOEXCEPT
{
    gu_pixel_coordinate::x = newValue;
}

pixels_t GU::PixelCoordinate::y() const NOEXCEPT
{
    return gu_pixel_coordinate::y;
}

void GU::PixelCoordinate::set_y(const pixels_t newValue) NOEXCEPT
{
    gu_pixel_coordinate::y = newValue;
}

pixels_u GU::PixelCoordinate::resWidth() const NOEXCEPT
{
    return gu_pixel_coordinate::res_width;
}

void GU::PixelCoordinate::set_resWidth(const pixels_u newValue) NOEXCEPT
{
    gu_pixel_coordinate::res_width = newValue;
}

pixels_u GU::PixelCoordinate::resHeight() const NOEXCEPT
{
    return gu_pixel_coordinate::res_height;
}

void GU::PixelCoordinate::set_resHeight(const pixels_u newValue) NOEXCEPT
{
    gu_pixel_coordinate::res_height = newValue;
}

pixels_t GU::PixelCoordinate::xLowerBound() const NOEXCEPT
{
    return gu_pixel_coordinate_x_lower_bound(*this);
}

pixels_t GU::PixelCoordinate::xUpperBound() const NOEXCEPT
{
    return gu_pixel_coordinate_x_upper_bound(*this);
}

pixels_t GU::PixelCoordinate::yLowerBound() const NOEXCEPT
{
    return gu_pixel_coordinate_y_lower_bound(*this);
}

pixels_t GU::PixelCoordinate::yUpperBound() const NOEXCEPT
{
    return gu_pixel_coordinate_y_upper_bound(*this);
}

bool GU::PixelCoordinate::operator==(const PixelCoordinate &other) const NOEXCEPT
{
    return gu_pixel_coordinate_equals(*this, other);
}

bool GU::PixelCoordinate::operator!=(const PixelCoordinate &other) const NOEXCEPT
{
    return !(*this == other);
}

bool GU::PixelCoordinate::operator==(const gu_pixel_coordinate &other) const NOEXCEPT
{
    return gu_pixel_coordinate_equals(*this, other);
}

bool GU::PixelCoordinate::operator!=(const gu_pixel_coordinate &other) const NOEXCEPT
{
    return !(*this == other);
}
