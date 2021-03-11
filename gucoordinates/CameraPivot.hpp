/*
 * CameraPivot.hpp 
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

#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "camera_pivot.h"
#include "Camera.hpp"

#include <cstdlib>
#include <gu_util.h>

namespace GU {

    struct CameraPivot: public gu_camera_pivot {

        CameraPivot() NOEXCEPT;
        CameraPivot(const degrees_d, const degrees_d, const centimetres_d, const gu_camera[GU_CAMERA_PIVOT_NUM_CAMERAS], int) NOEXCEPT;
        CameraPivot(const CameraPivot& other) NOEXCEPT;
        CameraPivot(const gu_camera_pivot& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        CameraPivot(CameraPivot&& other) NOEXCEPT;
        CameraPivot(gu_camera_pivot&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif
        ~CameraPivot() NOEXCEPT;
        CameraPivot& operator=(const CameraPivot& other) NOEXCEPT;
        CameraPivot& operator=(const gu_camera_pivot& other) NOEXCEPT;
#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        CameraPivot& operator=(CameraPivot&& other) NOEXCEPT;
        CameraPivot& operator=(gu_camera_pivot&& other) NOEXCEPT;
#pragma clang diagnostic pop
#endif

        degrees_d pitch() const NOEXCEPT;
        void set_pitch(const degrees_d) NOEXCEPT;

        degrees_d yaw() const NOEXCEPT;
        void set_yaw(const degrees_d) NOEXCEPT;

        centimetres_d height() const NOEXCEPT;
        void set_height(const centimetres_d) NOEXCEPT;

        const gu_camera * cameras() const NOEXCEPT;
        void set_cameras(const gu_camera[GU_CAMERA_PIVOT_NUM_CAMERAS]) NOEXCEPT;

        Camera camera(const int) const NOEXCEPT;
        void set_camera(const int, const Camera) NOEXCEPT;

        int numCameras() const NOEXCEPT;
        void set_numCameras(const int) NOEXCEPT;

        bool operator ==(const CameraPivot &other) const NOEXCEPT;
        bool operator !=(const CameraPivot &other) const NOEXCEPT;
        bool operator ==(const gu_camera_pivot &other) const NOEXCEPT;
        bool operator !=(const gu_camera_pivot &other) const NOEXCEPT;

    };

}

#endif  /* ROBOT_HPP */
