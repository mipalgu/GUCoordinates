/*
 * PixelCoordinateTests.cc 
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

#include "GUCoordinatesTests.hpp"

namespace CGTEST {

    class PixelCoordinateCPPTests: public GUCoordinatesTests<GU::PixelCoordinate, gu_pixel_coordinate> {

        protected:

        GU::PixelCoordinate initial()
        {
            return GU::PixelCoordinate(1, 2, 3, 4);
        }

        gu_pixel_coordinate empty()
        {
            gu_pixel_coordinate temp;
            temp.x = 0;
            temp.y = 0;
            temp.res_width = 0;
            temp.res_height = 0;
            return temp;
        }

        void change(GU::PixelCoordinate &obj)
        {
            obj.set_x(0);
        }

        void cchange(gu_pixel_coordinate &obj)
        {
            obj.x = 1;
            obj.y = 2;
            obj.res_width = 3;
            obj.res_height = 4;
        }

    };

    WRAPPER_TEST_Fs(PixelCoordinate, gu_pixel_coordinate)

    TEST_F(PixelCoordinateCPPTests, GettersSetters) {
        GU::PixelCoordinate coord = GU::PixelCoordinate(-959, 540, 1920, 1080);
        ASSERT_EQ(coord.x(), -959);
        coord.set_x(1);
        ASSERT_EQ(coord.x(), 1);
        ASSERT_EQ(coord.y(), 540);
        coord.set_y(1);
        ASSERT_EQ(coord.y(), 1);
        ASSERT_EQ(coord.resWidth(), 1920);
        coord.set_resWidth(1);
        ASSERT_EQ(coord.resWidth(), 1);
        ASSERT_EQ(coord.resHeight(), 1080);
        coord.set_resHeight(1);
        ASSERT_EQ(coord.resHeight(), 1);
    }

    TEST_F(PixelCoordinateCPPTests, CameraCoordinate) {
        gu_camera_coordinate cam;
        cam.x = 0;
        cam.y = 0;
        cam.res_width = 1920;
        cam.res_height = 1080;
        px_coord_to_cam_coord_fake.return_val = cam;
        const GU::PixelCoordinate ptopLeftEdge = GU::PixelCoordinate(-959, 540, 1920, 1080);
        const GU::CameraCoordinate topLeftEdge = GU::CameraCoordinate(0, 0, 1920, 1080);
        const GU::CameraCoordinate out = ptopLeftEdge.cameraCoordinate();
        ASSERT_EQ(px_coord_to_cam_coord_fake.call_count, 1);
        ASSERT_EQ(out.x(), topLeftEdge.x());
        ASSERT_EQ(out.y(), topLeftEdge.y());
        ASSERT_EQ(out.resWidth(), topLeftEdge.resWidth());
        ASSERT_EQ(out.resHeight(), topLeftEdge.resHeight());
    }

    TEST_F(PixelCoordinateCPPTests, PercentCoordinate) {
        gu_percent_coordinate pct;
        pct.x = -1.0f;
        pct.y = 1.0f;
        px_coord_to_pct_coord_fake.return_val = pct;
        const GU::PixelCoordinate ptopLeftEdge = GU::PixelCoordinate(-959, 540, 1920, 1080);
        const GU::PercentCoordinate topLeftEdge = GU::PercentCoordinate(-1.0f, 1.0f);
        const GU::PercentCoordinate out = ptopLeftEdge.percentCoordinate();
        ASSERT_EQ(px_coord_to_pct_coord_fake.call_count, 1);
        ASSERT_EQ(out.x(), topLeftEdge.x());
        ASSERT_EQ(out.y(), topLeftEdge.y());
    }

}  // namespace
