/*
 * CartesianCoordinate.hpp 
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

#ifndef CARTESIANCOORDINATE_HPP
#define CARTESIANCOORDINATE_HPP

#include "cartesian_coordinate.h"

#include <cstdlib>
#include <guunits/guunits.h>
#include "CameraCoordinate.hpp"
#include "PixelCoordinate.hpp"
#include "PercentCoordinate.hpp"
#include "RelativeCoordinate.hpp"
#include "FieldCoordinate.hpp"
#include "Robot.hpp"

#if __cplusplus >= 201703L
#include <optional>
#endif

namespace GU {

    struct CameraCoordinate;
    struct PixelCoordinate;
    struct PercentCoordinate;
    struct RelativeCoordinate;
    struct FieldCoordinate;

    struct CartesianCoordinate: public gu_cartesian_coordinate {

        CartesianCoordinate();
        CartesianCoordinate(centimetres_t, centimetres_t);
        CartesianCoordinate(const CartesianCoordinate& other);
        CartesianCoordinate(const gu_cartesian_coordinate& other);
#ifdef __cpp_rvalue_references
        CartesianCoordinate(CartesianCoordinate&& other);
#endif
        ~CartesianCoordinate();
        CartesianCoordinate& operator=(const CartesianCoordinate& other);
        CartesianCoordinate& operator=(const gu_cartesian_coordinate& other);
#ifdef __cpp_rvalue_references
        CartesianCoordinate& operator=(CartesianCoordinate&& other);
#endif

        CartesianCoordinate cartesianCoordinateAt(const GU::RelativeCoordinate &) const;
        RelativeCoordinate relativeCoordinateTo(const GU::CartesianCoordinate &) const;
        RelativeCoordinate relativeCoordinateTo(const GU::FieldCoordinate &) const;

        bool percentCoordinateTo(const GU::RelativeCoordinate &, const GU::Robot &, const int, GU::PercentCoordinate &) const;
        bool percentCoordinateTo(const GU::CartesianCoordinate &, const GU::Robot &, const int, GU::PercentCoordinate &) const;
        bool percentCoordinateTo(const GU::FieldCoordinate &, const GU::Robot &, const int, GU::PercentCoordinate &) const;

#if __cplusplus >= 201703L
        std::optional<GU::PercentCoordinate> percentCoordinateTo(const GU::RelativeCoordinate &, const GU::Robot &, const int) const;
        std::optional<GU::PercentCoordinate> percentCoordinateTo(const GU::CartesianCoordinate &, const GU::Robot &, const int) const;
        std::optional<GU::PercentCoordinate> percentCoordinateTo(const GU::FieldCoordinate &, const GU::Robot &, const int) const;
#endif

        bool pixelCoordinateTo(const GU::CartesianCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u, GU::PixelCoordinate &) const;
        bool pixelCoordinateTo(const GU::FieldCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u, GU::PixelCoordinate &) const;

#if __cplusplus >= 201703L
        std::optional<GU::PixelCoordinate> pixelCoordinateTo(const GU::CartesianCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u) const;
        std::optional<GU::PixelCoordinate> pixelCoordinateTo(const GU::FieldCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u) const;
#endif

        bool cameraCoordinateTo(const GU::CartesianCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u, GU::CameraCoordinate &) const;
        bool cameraCoordinateTo(const GU::FieldCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u, GU::CameraCoordinate &) const;

#if __cplusplus >= 201703L
        std::optional<GU::CameraCoordinate> cameraCoordinateTo(const GU::CartesianCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u) const;
        std::optional<GU::CameraCoordinate> cameraCoordinateTo(const GU::FieldCoordinate &, const GU::Robot &, const int, const pixels_u, const pixels_u) const;
#endif

        centimetres_t x() const;
        void set_x(const centimetres_t);

        centimetres_t y() const;
        void set_y(const centimetres_t);

        bool operator ==(const CartesianCoordinate &other) const;
        bool operator !=(const CartesianCoordinate &other) const;
        bool operator ==(const gu_cartesian_coordinate &other) const;
        bool operator !=(const gu_cartesian_coordinate &other) const;

    };

}

#endif  /* CARTESIANCOORDINATE_HPP */
