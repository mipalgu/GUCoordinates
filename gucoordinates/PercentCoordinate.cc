/*
 * PercentCoordinate.cc 
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

#include "PercentCoordinate.hpp"
#include "conversions.h"

#if __cplusplus >= 201703L
#include <optional>
#endif

GU::PercentCoordinate::PercentCoordinate() {}

GU::PercentCoordinate::PercentCoordinate(percent_d t_x, percent_d t_y)
{
    set_x(t_x);
    set_y(t_y);
}

GU::PercentCoordinate::PercentCoordinate(const PercentCoordinate& other)
{
    set_x(other.x());
    set_y(other.y());
}

GU::PercentCoordinate::PercentCoordinate(const gu_percent_coordinate & other)
{
    set_x(other.x);
    set_y(other.y);
}

#if __cplusplus >= 201103L
GU::PercentCoordinate::PercentCoordinate(PercentCoordinate&& other)
{
    set_x(other.x());
    set_y(other.y());
    other.set_x(0);
    other.set_y(0);
}
#endif

GU::PercentCoordinate::~PercentCoordinate() {}

GU::PercentCoordinate& GU::PercentCoordinate::operator=(const PercentCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    return *this;
}

GU::PercentCoordinate& GU::PercentCoordinate::operator=(const gu_percent_coordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_x(other.x);
    set_y(other.y);
    return *this;
}

#if __cplusplus >= 201103L
GU::PercentCoordinate& GU::PercentCoordinate::operator=(PercentCoordinate&& other)
{
    if (&other == this) {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    other.set_x(0);
    other.set_y(0);
    return *this;
}
#endif

GU::PixelCoordinate GU::PercentCoordinate::pixelCoordinate(const pixels_u resWidth, const pixels_u resHeight) const
{
    return pct_coord_to_px_coord(*this, resWidth, resHeight);
}

GU::CameraCoordinate GU::PercentCoordinate::cameraCoordinate(const pixels_u resWidth, const pixels_u resHeight) const
{
    return pixelCoordinate(resWidth, resHeight).cameraCoordinate();
}

GU::RelativeCoordinate GU::PercentCoordinate::relativeCoordinate(const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return pct_coord_to_rr_coord(*this, cameraPivot, cameraOffset);
}

percent_d GU::PercentCoordinate::x() const
{
    return gu_percent_coordinate::x;
}

void GU::PercentCoordinate::set_x(const percent_d newValue)
{
    gu_percent_coordinate::x = newValue;
}

percent_d GU::PercentCoordinate::y() const
{
    return gu_percent_coordinate::y;
}

void GU::PercentCoordinate::set_y(const percent_d newValue)
{
    gu_percent_coordinate::y = newValue;
}

percent_d GU::PercentCoordinate::xLowerBound() const
{
    return gu_percent_coordinate_x_lower_bound(*this);
}

percent_d GU::PercentCoordinate::xUpperBound() const
{
    return gu_percent_coordinate_x_upper_bound(*this);
}

percent_d GU::PercentCoordinate::yLowerBound() const
{
    return gu_percent_coordinate_y_lower_bound(*this);
}

percent_d GU::PercentCoordinate::yUpperBound() const
{
    return gu_percent_coordinate_y_upper_bound(*this);
}

bool GU::PercentCoordinate::operator==(const PercentCoordinate &other) const
{
    return gu_percent_coordinate_equals(*this, other, 0.0001);
}

bool GU::PercentCoordinate::operator!=(const PercentCoordinate &other) const
{
    return !(*this == other);
}

bool GU::PercentCoordinate::operator==(const gu_percent_coordinate &other) const
{
    return gu_percent_coordinate_equals(*this, other, 0.0001);
}

bool GU::PercentCoordinate::operator!=(const gu_percent_coordinate &other) const
{
    return !(*this == other);
}
