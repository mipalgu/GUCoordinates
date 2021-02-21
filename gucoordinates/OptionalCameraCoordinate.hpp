/*
 * OptionalCameraCoordinate.hpp 
 * gucoordinates 
 *
 * Created by Callum McColl on 27/07/2020.
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

#ifndef GUCOORDINATES_OPTIONALCAMERACOORDINATE_HPP
#define GUCOORDINATES_OPTIONALCAMERACOORDINATE_HPP

#include "optional_camera_coordinate.h"
#include "CameraCoordinate.hpp"

#include <cstdlib>
#include <gu_util.h>

namespace GU {

    struct CameraCoordinate;

    struct OptionalCameraCoordinate: public gu_optional_camera_coordinate {

        OptionalCameraCoordinate() NOEXCEPT;
        OptionalCameraCoordinate(const CameraCoordinate) NOEXCEPT;
        OptionalCameraCoordinate(const bool, const CameraCoordinate) NOEXCEPT;
        OptionalCameraCoordinate(const OptionalCameraCoordinate& other) NOEXCEPT;
        OptionalCameraCoordinate(const gu_optional_camera_coordinate& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        OptionalCameraCoordinate(OptionalCameraCoordinate&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif
        ~OptionalCameraCoordinate() NOEXCEPT;
        OptionalCameraCoordinate& operator=(const OptionalCameraCoordinate& other) NOEXCEPT;
        OptionalCameraCoordinate& operator=(const gu_optional_camera_coordinate& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        OptionalCameraCoordinate& operator=(OptionalCameraCoordinate&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif

        bool has_value() const NOEXCEPT;
        void set_has_value(const bool) NOEXCEPT;
        
        CameraCoordinate value() const NOEXCEPT;
        void set_value(const CameraCoordinate) NOEXCEPT;

    };

}

#endif  /* GUCOORDINATES_OPTIONALCAMERACOORDINATE_HPP */
