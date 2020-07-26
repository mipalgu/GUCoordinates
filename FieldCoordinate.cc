/*
 * FieldCoordinate.cc 
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

#include "FieldCoordinate.hpp"
#include "conversions.h"

#if __cplusplus >= 201703L
#include <optional>
#endif

GU::FieldCoordinate::FieldCoordinate() {}

GU::FieldCoordinate::FieldCoordinate(GU::CartesianCoordinate t_position, degrees_t t_heading)
{
    set_position(t_position);
    set_heading(t_heading);
}

GU::FieldCoordinate::FieldCoordinate(const FieldCoordinate& other)
{
    set_position(other.position());
    set_heading(other.heading());
}

GU::FieldCoordinate::FieldCoordinate(const gu_field_coordinate & other)
{
    set_position(other.position);
    set_heading(other.heading);
}

#if __cplusplus >= 201103L
GU::FieldCoordinate::FieldCoordinate(FieldCoordinate&& other)
{
    set_position(other.position());
    set_heading(other.heading());
    other.set_position(GU::CartesianCoordinate(0, 0));
    other.set_heading(0);
}
#endif

GU::FieldCoordinate::~FieldCoordinate() {}

GU::FieldCoordinate& GU::FieldCoordinate::operator=(const FieldCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_position(other.position());
    set_heading(other.heading());
    return *this;
}

GU::FieldCoordinate& GU::FieldCoordinate::operator=(const gu_field_coordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_position(other.position);
    set_heading(other.heading);
    return *this;
}

#if __cplusplus >= 201103L
GU::FieldCoordinate& GU::FieldCoordinate::operator=(FieldCoordinate&& other)
{
    if (&other == this) {
        return *this;
    }
    set_position(other.position());
    set_heading(other.heading());
    other.set_position(GU::CartesianCoordinate(0, 0));
    other.set_heading(0);
    return *this;
}
#endif

GU::CartesianCoordinate GU::FieldCoordinate::unsafeCartesianCoordinateAt(const GU::CameraCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset) const
{
    return cartesianCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset));
}

GU::CartesianCoordinate GU::FieldCoordinate::unsafeCartesianCoordinateAt(const GU::PixelCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset) const
{
    return cartesianCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset));
}

GU::CartesianCoordinate GU::FieldCoordinate::unsafeCartesianCoordinateAt(const GU::PercentCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset) const
{
    return cartesianCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset));
}

GU::FieldCoordinate GU::FieldCoordinate::unsafeFieldCoordinateAt(const GU::CameraCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    return fieldCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset), targetHeading);
}

GU::FieldCoordinate GU::FieldCoordinate::unsafeFieldCoordinateAt(const GU::PixelCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    return fieldCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset), targetHeading);
}

GU::FieldCoordinate GU::FieldCoordinate::unsafeFieldCoordinateAt(const GU::PercentCoordinate &target, const GU::CameraPivot &cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    return fieldCoordinateAt(target.unsafeRelativeCoordinate(cameraPivot, cameraOffset), targetHeading);
}

GU::OptionalCartesianCoordinate GU::FieldCoordinate::rawCartesianCoordinateAt(const GU::CameraCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalCartesianCoordinate(temp.has_value(), cartesianCoordinateAt(temp.value()));
}

GU::OptionalCartesianCoordinate GU::FieldCoordinate::rawCartesianCoordinateAt(const GU::PixelCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalCartesianCoordinate(temp.has_value(), cartesianCoordinateAt(temp.value()));
}

GU::OptionalCartesianCoordinate GU::FieldCoordinate::rawCartesianCoordinateAt(const GU::PercentCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalCartesianCoordinate(temp.has_value(), cartesianCoordinateAt(temp.value()));
}

GU::OptionalFieldCoordinate GU::FieldCoordinate::rawFieldCoordinateAt(const GU::CameraCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalFieldCoordinate(temp.has_value(), fieldCoordinateAt(temp.value(), targetHeading));
}

GU::OptionalFieldCoordinate GU::FieldCoordinate::rawFieldCoordinateAt(const GU::PixelCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalFieldCoordinate(temp.has_value(), fieldCoordinateAt(temp.value(), targetHeading));
}

GU::OptionalFieldCoordinate GU::FieldCoordinate::rawFieldCoordinateAt(const GU::PercentCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    const GU::OptionalRelativeCoordinate temp = target.rawRelativeCoordinate(cameraPivot, cameraOffset);
    return GU::OptionalFieldCoordinate(temp.has_value(), fieldCoordinateAt(temp.value(), targetHeading));
}

#if __cplusplus >= 201703L
std::optional<GU::CartesianCoordinate> GU::FieldCoordinate::cartesianCoordinateAt(const GU::CameraCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return cartesianCoordinateAt(temp.value());
}

std::optional<GU::CartesianCoordinate> GU::FieldCoordinate::cartesianCoordinateAt(const GU::PixelCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return cartesianCoordinateAt(temp.value());
}

std::optional<GU::CartesianCoordinate> GU::FieldCoordinate::cartesianCoordinateAt(const GU::PercentCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return cartesianCoordinateAt(temp.value());
}

std::optional<GU::FieldCoordinate> GU::FieldCoordinate::fieldCoordinateAt(const GU::CameraCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return fieldCoordinateAt(temp.value(), targetHeading);
}

std::optional<GU::FieldCoordinate> GU::FieldCoordinate::fieldCoordinateAt(const GU::PixelCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return fieldCoordinateAt(temp.value(), targetHeading);
}

std::optional<GU::FieldCoordinate> GU::FieldCoordinate::fieldCoordinateAt(const GU::PercentCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const degrees_t targetHeading) const
{
    const std::optional<GU::RelativeCoordinate> temp = target.relativeCoordinate(cameraPivot, cameraOffset);
    if (!temp.has_value())
        return std::nullopt;
    return fieldCoordinateAt(temp.value(), targetHeading);
}
#endif

GU::CartesianCoordinate GU::FieldCoordinate::cartesianCoordinateAt(const GU::RelativeCoordinate & target) const
{
    return rr_coord_to_cartesian_coord_from_field(target, *this);
}

GU::FieldCoordinate GU::FieldCoordinate::fieldCoordinateAt(const GU::RelativeCoordinate & target, const degrees_t targetHeading) const
{
    return rr_coord_to_field_coord_from_source(target, *this, targetHeading);
}

GU::RelativeCoordinate GU::FieldCoordinate::relativeCoordinateTo(const GU::CartesianCoordinate & target) const
{
    return field_coord_to_rr_coord_to_target(*this, target);
}

GU::RelativeCoordinate GU::FieldCoordinate::relativeCoordinateTo(const GU::FieldCoordinate & target) const
{
    return relativeCoordinateTo(target.position());
}

GU::CameraCoordinate GU::FieldCoordinate::unsafeCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::CameraCoordinate GU::FieldCoordinate::unsafeCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::FieldCoordinate::unsafePixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafePixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::FieldCoordinate::unsafePixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafePixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PercentCoordinate GU::FieldCoordinate::unsafePercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafePercentCoordinate(cameraPivot, cameraOffset);
}

GU::PercentCoordinate GU::FieldCoordinate::unsafePercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafePercentCoordinate(cameraPivot, cameraOffset);
}

GU::CameraCoordinate GU::FieldCoordinate::unsafeClampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::CameraCoordinate GU::FieldCoordinate::unsafeClampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::FieldCoordinate::unsafeClampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PixelCoordinate GU::FieldCoordinate::unsafeClampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::PercentCoordinate GU::FieldCoordinate::unsafeClampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset);
}

GU::PercentCoordinate GU::FieldCoordinate::unsafeClampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset);
}

GU::CameraCoordinate GU::FieldCoordinate::unsafeClampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::CameraCoordinate GU::FieldCoordinate::unsafeClampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::PixelCoordinate GU::FieldCoordinate::unsafeClampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::PixelCoordinate GU::FieldCoordinate::unsafeClampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::PercentCoordinate GU::FieldCoordinate::unsafeClampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::PercentCoordinate GU::FieldCoordinate::unsafeClampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).unsafeClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::OptionalCameraCoordinate GU::FieldCoordinate::rawClampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).rawClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalCameraCoordinate GU::FieldCoordinate::rawClampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).rawClampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalPixelCoordinate GU::FieldCoordinate::rawClampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalPixelCoordinate GU::FieldCoordinate::rawClampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

GU::OptionalPercentCoordinate GU::FieldCoordinate::rawClampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::OptionalPercentCoordinate GU::FieldCoordinate::rawClampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).rawClampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

GU::OptionalPercentCoordinate GU::FieldCoordinate::rawPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).rawPercentCoordinate(cameraPivot, cameraOffset);
}

GU::OptionalPercentCoordinate GU::FieldCoordinate::rawPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).rawPercentCoordinate(cameraPivot, cameraOffset);
}

GU::OptionalPixelCoordinate GU::FieldCoordinate::rawPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::OptionalPixelCoordinate GU::FieldCoordinate::rawPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::OptionalCameraCoordinate GU::FieldCoordinate::rawCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

GU::OptionalCameraCoordinate GU::FieldCoordinate::rawCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).rawCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

#if __cplusplus >= 201703L
std::optional<GU::PercentCoordinate> GU::FieldCoordinate::percentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).percentCoordinate(cameraPivot, cameraOffset);
}

std::optional<GU::PercentCoordinate> GU::FieldCoordinate::percentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset) const
{
    return relativeCoordinateTo(target).percentCoordinate(cameraPivot, cameraOffset);
}

std::optional<GU::PixelCoordinate> GU::FieldCoordinate::pixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).pixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::PixelCoordinate> GU::FieldCoordinate::pixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).pixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::CameraCoordinate> GU::FieldCoordinate::cameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).cameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::CameraCoordinate> GU::FieldCoordinate::cameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight) const
{
    return relativeCoordinateTo(target).cameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight);
}

std::optional<GU::CameraCoordinate> GU::FieldCoordinate::clampedCameraCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).clampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::CameraCoordinate> GU::FieldCoordinate::clampedCameraCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).clampedCameraCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::PixelCoordinate> GU::FieldCoordinate::clampedPixelCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).clampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::PixelCoordinate> GU::FieldCoordinate::clampedPixelCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const pixels_u resWidth, const pixels_u resHeight, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).clampedPixelCoordinate(cameraPivot, cameraOffset, resWidth, resHeight, tolerance);
}

std::optional<GU::PercentCoordinate> GU::FieldCoordinate::clampedPercentCoordinateTo(const GU::CartesianCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).clampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

std::optional<GU::PercentCoordinate> GU::FieldCoordinate::clampedPercentCoordinateTo(const GU::FieldCoordinate & target, const GU::CameraPivot & cameraPivot, const int cameraOffset, const percent_f tolerance) const
{
    return relativeCoordinateTo(target).clampedPercentCoordinate(cameraPivot, cameraOffset, tolerance);
}

#endif

GU::CartesianCoordinate GU::FieldCoordinate::position() const
{
    return gu_field_coordinate::position;
}

void GU::FieldCoordinate::set_position(const GU::CartesianCoordinate newValue)
{
    gu_field_coordinate::position = newValue;
}

degrees_t GU::FieldCoordinate::heading() const
{
    return gu_field_coordinate::heading;
}

void GU::FieldCoordinate::set_heading(const degrees_t newValue)
{
    gu_field_coordinate::heading = newValue;
}

bool GU::FieldCoordinate::operator==(const FieldCoordinate &other) const
{
    return gu_field_coordinate_equals(*this, other);
}

bool GU::FieldCoordinate::operator!=(const FieldCoordinate &other) const
{
    return !(*this == other);
}

bool GU::FieldCoordinate::operator==(const gu_field_coordinate &other) const
{
    return gu_field_coordinate_equals(*this, other);
}

bool GU::FieldCoordinate::operator!=(const gu_field_coordinate &other) const
{
    return !(*this == other);
}
