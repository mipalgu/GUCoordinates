/*
 * PixelCoordinate.hpp 
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
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES NOEXCEPT; LOSS OF USE, DATA, OR
 * PROFITS NOEXCEPT; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * -----------------------------------------------------------------------
 * This program is free software NOEXCEPT; you can redistribute it and/or
 * modify it under the above terms or under the terms of the GNU
 * General Public License as published by the Free Software Foundation NOEXCEPT;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY NOEXCEPT; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program NOEXCEPT; if not, see http://www.gnu.org/licenses/
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef PIXELCOORDINATE_HPP
#define PIXELCOORDINATE_HPP

#include "pixel_coordinate.h"
#include "CameraCoordinate.hpp"
#include "PercentCoordinate.hpp"
#include "RelativeCoordinate.hpp"
#include "CameraPivot.hpp"
#include "OptionalRelativeCoordinate.hpp"

#include <cstdlib>

#if __cplusplus >= 201703L
#include <optional>
#endif

#include <gu_util.h>

namespace GU {

    struct CameraCoordinate; // Forward Declaration.
    struct PercentCoordinate; // Forward Declaration.
    struct RelativeCoordinate; // Forward Declaration.

    struct PixelCoordinate: public gu_pixel_coordinate {

        PixelCoordinate() NOEXCEPT;
        PixelCoordinate(pixels_t, pixels_t, pixels_u, pixels_u) NOEXCEPT;
        PixelCoordinate(const PixelCoordinate& other) NOEXCEPT;
        PixelCoordinate(const gu_pixel_coordinate& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        PixelCoordinate(PixelCoordinate&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif
        ~PixelCoordinate() NOEXCEPT;
        PixelCoordinate& operator=(const PixelCoordinate& other) NOEXCEPT;
        PixelCoordinate& operator=(const gu_pixel_coordinate& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        PixelCoordinate& operator=(PixelCoordinate&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif

        CameraCoordinate cameraCoordinate() const NOEXCEPT;
        PercentCoordinate percentCoordinate() const NOEXCEPT;
        RelativeCoordinate relativeCoordinate(const GU::CameraPivot &, const int) const NOEXCEPT;

        pixels_t x() const NOEXCEPT;
        void set_x(const pixels_t) NOEXCEPT;

        pixels_t y() const NOEXCEPT;
        void set_y(const pixels_t) NOEXCEPT;

        pixels_u resWidth() const NOEXCEPT;
        void set_resWidth(const pixels_u) NOEXCEPT;

        pixels_u resHeight() const NOEXCEPT;
        void set_resHeight(const pixels_u) NOEXCEPT;

        pixels_t xLowerBound() const NOEXCEPT;
        pixels_t xUpperBound() const NOEXCEPT;

        pixels_t yLowerBound() const NOEXCEPT;
        pixels_t yUpperBound() const NOEXCEPT;

        bool operator ==(const PixelCoordinate &other) const NOEXCEPT;
        bool operator !=(const PixelCoordinate &other) const NOEXCEPT;
        bool operator ==(const gu_pixel_coordinate &other) const NOEXCEPT;
        bool operator !=(const gu_pixel_coordinate &other) const NOEXCEPT;

    };

}

#endif  /* PIXELCOORDINATE_HPP */
