/*
 * RelativeCoordinate.cc 
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

#include "RelativeCoordinate.hpp"
#include "conversions.h"

#if __cplusplus >= 201703L
#include <optional>
#endif

GU::RelativeCoordinate::RelativeCoordinate() {}

GU::RelativeCoordinate::RelativeCoordinate(degrees_t t_direction, centimetres_u t_distance)
{
    set_direction(t_direction);
    set_distance(t_distance);
}

GU::RelativeCoordinate::RelativeCoordinate(const RelativeCoordinate& other)
{
    set_direction(other.direction());
    set_distance(other.distance());
}

GU::RelativeCoordinate::RelativeCoordinate(const gu_relative_coordinate & other)
{
    set_direction(other.direction);
    set_distance(other.distance);
}

#if __cplusplus >= 201103L
GU::RelativeCoordinate::RelativeCoordinate(RelativeCoordinate&& other)
{
    set_direction(other.direction());
    set_distance(other.distance());
    other.set_direction(0);
    other.set_distance(0);
}
#endif

GU::RelativeCoordinate::~RelativeCoordinate() {}

GU::RelativeCoordinate& GU::RelativeCoordinate::operator=(const RelativeCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_direction(other.direction());
    set_distance(other.distance());
    return *this;
}

GU::RelativeCoordinate& GU::RelativeCoordinate::operator=(const gu_relative_coordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_direction(other.direction);
    set_distance(other.distance);
    return *this;
}

#if __cplusplus >= 201103L
GU::RelativeCoordinate& GU::RelativeCoordinate::operator=(RelativeCoordinate&& other)
{
    if (&other == this) {
        return *this;
    }
    set_direction(other.direction());
    set_distance(other.distance());
    other.set_direction(0);
    other.set_distance(0);
    return *this;
}
#endif

bool GU::RelativeCoordinate::cameraCoordinate(const GU::Robot &robot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, GU::CameraCoordinate &other) const
{
    GU::PercentCoordinate temp;
    if (!percentCoordinate(robot, cameraOffset, temp))
        return false;
    other = temp.cameraCoordinate(resWidth, resHeight);
    return true;
}

bool GU::RelativeCoordinate::pixelCoordinate(const GU::Robot &robot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, GU::PixelCoordinate &other) const
{
    GU::PercentCoordinate temp;
    if (!percentCoordinate(robot, cameraOffset, temp))
        return false;
    other = temp.pixelCoordinate(resWidth, resHeight);
    return true;
}
    
bool GU::RelativeCoordinate::percentCoordinate(const GU::Robot &robot, const int cameraOffset, GU::PercentCoordinate &other) const
{
    gu_percent_coordinate temp;
    if (!rr_coord_to_pct_coord(*this, robot, cameraOffset, &temp))
    {
        return false;
    }
    other = temp;
    return true;
}

#if __cplusplus >= 201703L
std::optional<GU::CameraCoordinate> GU::RelativeCoordinate::cameraCoordinate(const GU::Robot &robot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    const std::optional<GU::PixelCoordinate> p = pixelCoordinate(robot, cameraOffset, resWidth, resHeight);
    if (p.has_value())
    {
        return p.value().cameraCoordinate();
    }
    return std::nullopt;
}

std::optional<GU::PixelCoordinate> GU::RelativeCoordinate::pixelCoordinate(const GU::Robot &robot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    const std::optional<GU::PercentCoordinate> p = percentCoordinate(robot, cameraOffset);
    if (p.has_value())
    {
        return p.value().pixelCoordinate(resWidth, resHeight);
    }
    return std::nullopt;
}

std::optional<GU::PercentCoordinate> GU::RelativeCoordinate::percentCoordinate(const GU::Robot &robot, const int cameraOffset) const
{
    GU::PercentCoordinate temp;
    const bool result = percentCoordinate(robot, cameraOffset, temp);
    if (result) {
        return std::optional<GU::PercentCoordinate>(temp);
    }
    return std::nullopt;
}
#endif

GU::CartesianCoordinate GU::RelativeCoordinate::cartesianCoordinate() const
{
    return rr_coord_to_cartesian_coord(*this);
}

GU::FieldCoordinate GU::RelativeCoordinate::fieldCoordinate(const degrees_t heading) const
{
    return rr_coord_to_field_coord(*this, heading);
}

degrees_t GU::RelativeCoordinate::direction() const
{
    return gu_relative_coordinate::direction;
}

void GU::RelativeCoordinate::set_direction(const degrees_t newValue)
{
    gu_relative_coordinate::direction = newValue;
}

centimetres_u GU::RelativeCoordinate::distance() const
{
    return gu_relative_coordinate::distance;
}

void GU::RelativeCoordinate::set_distance(const centimetres_u newValue)
{
    gu_relative_coordinate::distance = newValue;
}

bool GU::RelativeCoordinate::operator==(const RelativeCoordinate &other) const
{
    return gu_relative_coordinate_equals(*this, other);
}

bool GU::RelativeCoordinate::operator!=(const RelativeCoordinate &other) const
{
    return !(*this == other);
}

bool GU::RelativeCoordinate::operator==(const gu_relative_coordinate &other) const
{
    return gu_relative_coordinate_equals(*this, other);
}

bool GU::RelativeCoordinate::operator!=(const gu_relative_coordinate &other) const
{
    return !(*this == other);
}
