/*
 * PercentCoordinateTests.cc 
 * tests 
 *
 * Created by Callum McColl on 18/06/2020.
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

#include "GUWrapperTests.hpp"

namespace CGTEST {
    
    class PercentCoordinateCPPTests: public GUWrapperTests<GU::PercentCoordinate, gu_percent_coordinate> {

        protected:

        GU::PercentCoordinate initial()
        {
            return GU::PercentCoordinate(-1.0f, -1.0f);
        }

        GU::PercentCoordinate empty()
        {
            return GU::PercentCoordinate(0.0f, 0.0f);
        }

        void change(GU::PercentCoordinate &obj)
        {
            obj.set_x(0.0f);
        }

        void cchange(gu_percent_coordinate &obj)
        {
            obj.x = 1.0f;
            obj.y = 2.0f;
        }

        gu_percent_coordinate cempty()
        {
            return empty();
        }

    };

    WRAPPER_TEST_Fs(PercentCoordinate, gu_percent_coordinate)
    GETTER_TEST_F(PercentCoordinate, CameraCoordinate, px_coord_to_cam_coord, cameraCoordinate(1920, 1080))
    GETTER_TEST_F(PercentCoordinate, PixelCoordinate, pct_coord_to_px_coord, pixelCoordinate(1920, 1080))
    GETTER_OPT_TEST_F(PercentCoordinate, RelativeCoordinate, pct_coord_to_rr_coord, relativeCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_TEST_NAME_F(PercentCoordinate, unsafeRelativeCoordinate, RelativeCoordinate, unsafe_pct_coord_to_rr_coord, unsafeRelativeCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    TEST_F(PercentCoordinateCPPTests, GettersSetters) {
        GU::PercentCoordinate coord = GU::PercentCoordinate(-1.0f, -1.0f);
        ASSERT_EQ(coord.x(), -1.0f);
        coord.set_x(1.0f);
        ASSERT_EQ(coord.x(), 1.0f);
        ASSERT_EQ(coord.y(), -1.0f);
        coord.set_y(1.0f);
        ASSERT_EQ(coord.y(), 1.0f);
    }

}  // namespace
