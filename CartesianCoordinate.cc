/*
 * CartesianCoordinate.cc 
 * gucoordinates 
 *
 * Created by Callum McColl on 21/06/2020.
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

#include "CartesianCoordinate.hpp"
#include "conversions.h"

#if __cplusplus >= 201703L
#include <optional>
#endif

GU::CartesianCoordinate::CartesianCoordinate() {}

GU::CartesianCoordinate::CartesianCoordinate(centimetres_t t_x, centimetres_t t_y)
{
    set_x(t_x);
    set_y(t_y);
}

GU::CartesianCoordinate::CartesianCoordinate(const CartesianCoordinate& other)
{
    set_x(other.x());
    set_y(other.y());
}

GU::CartesianCoordinate::CartesianCoordinate(const gu_cartesian_coordinate & other)
{
    set_x(other.x);
    set_y(other.y);
}

#if __cplusplus >= 201103L
GU::CartesianCoordinate::CartesianCoordinate(CartesianCoordinate&& other)
{
    set_x(other.x());
    set_y(other.y());
    other.set_x(0);
    other.set_y(0);
}
#endif

GU::CartesianCoordinate::~CartesianCoordinate() {}

GU::CartesianCoordinate& GU::CartesianCoordinate::operator=(const CartesianCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_x(other.x());
    set_y(other.y());
    return *this;
}

GU::CartesianCoordinate& GU::CartesianCoordinate::operator=(const gu_cartesian_coordinate& other)
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
GU::CartesianCoordinate& GU::CartesianCoordinate::operator=(CartesianCoordinate&& other)
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

GU::CartesianCoordinate GU::CartesianCoordinate::unsafeCartesianCoordinateAt(const GU::CameraCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset) const
{
    return cartesianCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset));
}

GU::CartesianCoordinate GU::CartesianCoordinate::unsafeCartesianCoordinateAt(const GU::PixelCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset) const
{
    return cartesianCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset));
}

GU::CartesianCoordinate GU::CartesianCoordinate::unsafeCartesianCoordinateAt(const GU::PercentCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset) const
{
    return cartesianCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset));
}

GU::OptionalCartesianCoordinate GU::CartesianCoordinate::rawCartesianCoordinateAt(const GU::CameraCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalCartesianCoordinate(temp.has_value(), cartesianCoordinateAt(temp.value()));
}

GU::OptionalCartesianCoordinate GU::CartesianCoordinate::rawCartesianCoordinateAt(const GU::PixelCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalCartesianCoordinate(temp.has_value(), cartesianCoordinateAt(temp.value()));
}

GU::OptionalCartesianCoordinate GU::CartesianCoordinate::rawCartesianCoordinateAt(const GU::PercentCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalCartesianCoordinate(temp.has_value(), cartesianCoordinateAt(temp.value()));
}

#if __cplusplus >= 201703L
std::optional<GU::CartesianCoordinate> GU::CartesianCoordinate::cartesianCoordinateAt(const GU::CameraCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return cartesianCoordinateAt(temp.value());
}

std::optional<GU::CartesianCoordinate> GU::CartesianCoordinate::cartesianCoordinateAt(const GU::PixelCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return cartesianCoordinateAt(temp.value());
}

std::optional<GU::CartesianCoordinate> GU::CartesianCoordinate::cartesianCoordinateAt(const GU::PercentCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return cartesianCoordinateAt(temp.value());
}
#endif

GU::CartesianCoordinate GU::CartesianCoordinate::cartesianCoordinateAt(const GU::RelativeCoordinate & target) const
{
    return rr_coord_to_cartesian_coord_from_source(target, *this);
}

GU::RelativeCoordinate GU::CartesianCoordinate::relativeCoordinateTo(const GU::CartesianCoordinate & target) const
{
    return cartesian_coord_to_rr_coord_from_source(*this, target);
}

GU::RelativeCoordinate GU::CartesianCoordinate::relativeCoordinateTo(const GU::FieldCoordinate & target) const
{
    return relativeCoordinateTo(target.position());
}

GU::OptionalPercentCoordinate GU::CartesianCoordinate::rawPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).rawPercentCoordinate(cameraPivot, cameraOffset);
}

GU::OptionalPercentCoordinate GU::CartesianCoordinate::rawPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).rawPercentCoordinate(cameraPivot, cameraOffset);
}

GU::OptionalPixelCoordinate GU::CartesianCoordinate::rawPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::OptionalPixelCoordinate GU::CartesianCoordinate::rawPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::OptionalCameraCoordinate GU::CartesianCoordinate::rawCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::OptionalCameraCoordinate GU::CartesianCoordinate::rawCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::CameraCoordinate GU::CartesianCoordinate::unsafeCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::CameraCoordinate GU::CartesianCoordinate::unsafeCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::CartesianCoordinate::unsafePixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafePixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::CartesianCoordinate::unsafePixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafePixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PercentCoordinate GU::CartesianCoordinate::unsafePercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafePercentCoordinate(cameraPivot, cameraOffset);
}

GU::PercentCoordinate GU::CartesianCoordinate::unsafePercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafePercentCoordinate(cameraPivot, cameraOffset);
}

GU::CameraCoordinate GU::CartesianCoordinate::unsafeClampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::CameraCoordinate GU::CartesianCoordinate::unsafeClampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::CartesianCoordinate::unsafeClampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::CartesianCoordinate::unsafeClampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PercentCoordinate GU::CartesianCoordinate::unsafeClampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset);
}

GU::PercentCoordinate GU::CartesianCoordinate::unsafeClampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset);
}

GU::CameraCoordinate GU::CartesianCoordinate::unsafeClampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::CameraCoordinate GU::CartesianCoordinate::unsafeClampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::PixelCoordinate GU::CartesianCoordinate::unsafeClampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::PixelCoordinate GU::CartesianCoordinate::unsafeClampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::PercentCoordinate GU::CartesianCoordinate::unsafeClampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::PercentCoordinate GU::CartesianCoordinate::unsafeClampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::OptionalCameraCoordinate GU::CartesianCoordinate::rawClampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).rawClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalCameraCoordinate GU::CartesianCoordinate::rawClampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).rawClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalPixelCoordinate GU::CartesianCoordinate::rawClampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalPixelCoordinate GU::CartesianCoordinate::rawClampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalPercentCoordinate GU::CartesianCoordinate::rawClampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::OptionalPercentCoordinate GU::CartesianCoordinate::rawClampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

#if __cplusplus >= 201703L
std::optional<GU::PercentCoordinate> GU::CartesianCoordinate::percentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).percentCoordinate(cameraPivot, cameraOffset);
}

std::optional<GU::PercentCoordinate> GU::CartesianCoordinate::percentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).percentCoordinate(cameraPivot, cameraOffset);
}

std::optional<GU::PixelCoordinate> GU::CartesianCoordinate::pixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).pixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::PixelCoordinate> GU::CartesianCoordinate::pixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).pixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::CameraCoordinate> GU::CartesianCoordinate::cameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).cameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::CameraCoordinate> GU::CartesianCoordinate::cameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).cameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::CameraCoordinate> GU::CartesianCoordinate::clampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).clampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::CameraCoordinate> GU::CartesianCoordinate::clampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).clampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::PixelCoordinate> GU::CartesianCoordinate::clampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).clampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::PixelCoordinate> GU::CartesianCoordinate::clampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).clampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::PercentCoordinate> GU::CartesianCoordinate::clampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).clampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

std::optional<GU::PercentCoordinate> GU::CartesianCoordinate::clampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_d tolerance) const
{
    return relativeCoordinateTo(target).clampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}
#endif

centimetres_t GU::CartesianCoordinate::x() const
{
    return gu_cartesian_coordinate::x;
}

void GU::CartesianCoordinate::set_x(const centimetres_t newValue)
{
    gu_cartesian_coordinate::x = newValue;
}

centimetres_t GU::CartesianCoordinate::y() const
{
    return gu_cartesian_coordinate::y;
}

void GU::CartesianCoordinate::set_y(const centimetres_t newValue)
{
    gu_cartesian_coordinate::y = newValue;
}

bool GU::CartesianCoordinate::operator==(const CartesianCoordinate &other) const
{
    return gu_cartesian_coordinate_equals(*this, other);
}

bool GU::CartesianCoordinate::operator!=(const CartesianCoordinate &other) const
{
    return !(*this == other);
}

bool GU::CartesianCoordinate::operator==(const gu_cartesian_coordinate &other) const
{
    return gu_cartesian_coordinate_equals(*this, other);
}

bool GU::CartesianCoordinate::operator!=(const gu_cartesian_coordinate &other) const
{
    return !(*this == other);
}


