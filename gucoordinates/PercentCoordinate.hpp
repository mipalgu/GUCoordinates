/*
 * PercentCoordinate.hpp 
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

#ifndef PERCENTCOORDINATE_HPP
#define PERCENTCOORDINATE_HPP

#include "percent_coordinate.h"
#include "RelativeCoordinate.hpp"
#include "PixelCoordinate.hpp"
#include "CameraCoordinate.hpp"
#include "CameraPivot.hpp"

#include "OptionalRelativeCoordinate.hpp"

#include <cstdlib>
#include <gu_util.h>

namespace GU {

    struct CameraCoordinate; // Forward Declaration.
    struct PixelCoordinate; // Forward Declaration.
    struct RelativeCoordinate; // Forward Declaration.

    struct PercentCoordinate: public gu_percent_coordinate {

        PercentCoordinate() NOEXCEPT;
        PercentCoordinate(percent_d, percent_d) NOEXCEPT;
        PercentCoordinate(const PercentCoordinate& other) NOEXCEPT;
        PercentCoordinate(const gu_percent_coordinate& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        PercentCoordinate(PercentCoordinate&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif
        ~PercentCoordinate() NOEXCEPT;
        PercentCoordinate& operator=(const PercentCoordinate& other) NOEXCEPT;
        PercentCoordinate& operator=(const gu_percent_coordinate& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        PercentCoordinate& operator=(PercentCoordinate&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif

        CameraCoordinate cameraCoordinate(const pixels_u, const pixels_u) const NOEXCEPT;
        PixelCoordinate pixelCoordinate(const pixels_u, const pixels_u) const NOEXCEPT;
        RelativeCoordinate relativeCoordinate(const GU::CameraPivot &, const int) const NOEXCEPT;

        percent_d x() const NOEXCEPT;
        void set_x(const percent_d) NOEXCEPT;

        percent_d y() const NOEXCEPT;
        void set_y(const percent_d) NOEXCEPT;

        percent_d xLowerBound() const NOEXCEPT;
        percent_d xUpperBound() const NOEXCEPT;

        percent_d yLowerBound() const NOEXCEPT;
        percent_d yUpperBound() const NOEXCEPT;

        bool operator ==(const PercentCoordinate &other) const NOEXCEPT;
        bool operator !=(const PercentCoordinate &other) const NOEXCEPT;
        bool operator ==(const gu_percent_coordinate &other) const NOEXCEPT;
        bool operator !=(const gu_percent_coordinate &other) const NOEXCEPT;

    };

}

#endif  /* PERCENTCOORDINATE_HPP */
