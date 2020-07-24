/*
 * RelativeCoordinate.hpp 
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

#ifndef RELATIVECOORDINATE_HPP
#define RELATIVECOORDINATE_HPP

#include "relative_coordinate.h"

#include <cstdlib>
#include <guunits/guunits.h>
#include "CameraCoordinate.hpp"
#include "PixelCoordinate.hpp"
#include "PercentCoordinate.hpp"
#include "CartesianCoordinate.hpp"
#include "FieldCoordinate.hpp"
#include "CameraPivot.hpp"

#if __cplusplus >= 201703L
#include <optional>
#endif

namespace GU {

    struct CameraCoordinate;
    struct PixelCoordinate;
    struct PercentCoordinate;
    struct CartesianCoordinate;
    struct FieldCoordinate;

    struct RelativeCoordinate: public gu_relative_coordinate {

        RelativeCoordinate();
        RelativeCoordinate(degrees_t, centimetres_u);
        RelativeCoordinate(const RelativeCoordinate& other);
        RelativeCoordinate(const gu_relative_coordinate& other);
#if __cplusplus >= 201103L
        RelativeCoordinate(RelativeCoordinate&& other);
#endif
        ~RelativeCoordinate();
        RelativeCoordinate& operator=(const RelativeCoordinate& other);
        RelativeCoordinate& operator=(const gu_relative_coordinate& other);
#if __cplusplus >= 201103L
        RelativeCoordinate& operator=(RelativeCoordinate&& other);
#endif

        bool cameraCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u, CameraCoordinate &) const;
        bool pixelCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u, PixelCoordinate &) const;
        bool percentCoordinate(const GU::CameraPivot &, const int, PercentCoordinate & other) const;

        CameraCoordinate unsafeCameraCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u) const;
        PixelCoordinate unsafePixelCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u) const;
        PercentCoordinate unsafePercentCoordinate(const GU::CameraPivot &, const int) const;

        CameraCoordinate unsafeClampedCameraCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u) const;
        PixelCoordinate unsafeClampedPixelCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u) const;
        PercentCoordinate unsafeClampedPercentCoordinate(const GU::CameraPivot &, const int) const;

        CameraCoordinate unsafeClampedCameraCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u, const percent_f) const;
        PixelCoordinate unsafeClampedPixelCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u, const percent_f) const;
        PercentCoordinate unsafeClampedPercentCoordinate(const GU::CameraPivot &, const int, const percent_f) const;

#if __cplusplus >= 201703L
        std::optional<CameraCoordinate> cameraCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u) const;
        std::optional<PixelCoordinate> pixelCoordinate(const GU::CameraPivot &, const int, const pixels_u, const pixels_u) const;
        std::optional<PercentCoordinate> percentCoordinate(const GU::CameraPivot &, const int) const;
#endif

        RelativeCoordinate relativeCoordinateTo(const RelativeCoordinate &) const;
        CartesianCoordinate cartesianCoordinate() const;
        FieldCoordinate fieldCoordinate(const degrees_t) const;

        degrees_t direction() const;
        void set_direction(const degrees_t);

        centimetres_u distance() const;
        void set_distance(const centimetres_u);

        bool operator ==(const RelativeCoordinate &other) const;
        bool operator !=(const RelativeCoordinate &other) const;
        bool operator ==(const gu_relative_coordinate &other) const;
        bool operator !=(const gu_relative_coordinate &other) const;

    };

}

#endif  /* RELATIVECOORDINATE_HPP */
