/*
 * RelativeCoordinateTests.cc 
 * tests 
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

#include "GUCoordinatesTests.hpp"

namespace CGTEST {
    
    class RelativeCoordinateCPPTests: public GUCoordinatesTests<GU::RelativeCoordinate, gu_relative_coordinate> {

        protected:

        GU::RelativeCoordinate initial()
        {
            return GU::RelativeCoordinate(90, 100);
        }

        gu_relative_coordinate empty()
        {
            return { 0, 0 };
        }

        void change(GU::RelativeCoordinate &obj)
        {
            obj.set_direction(-90);
        }

        void cchange(gu_relative_coordinate &obj)
        {
            obj = {40, 15};
        }

    };

    WRAPPER_TEST_Fs(RelativeCoordinate, gu_relative_coordinate)

    TEST_F(RelativeCoordinateCPPTests, GettersSetters) {
        GU::RelativeCoordinate coord = GU::RelativeCoordinate(90, 100);
        ASSERT_EQ(coord.direction(), 90);
        coord.set_direction(-90);
        ASSERT_EQ(coord.direction(), -90);
        ASSERT_EQ(coord.distance(), 100);
        coord.set_distance(10);
        ASSERT_EQ(coord.distance(), 10);
    }

/*
    TEST_F(RelativeCoordinateCPPTests, PixelCoordinate) {
        pct_coord_to_px_coord_fake.return_val = { -959, 540, 1920, 1080 };
        const GU::RelativeCoordinate topLeftEdge = GU::RelativeCoordinate(-1.0f, 1.0f);
        const GU::PixelCoordinate ptopLeftEdge = GU::PixelCoordinate(-959, 540, 1920, 1080);
        const GU::PixelCoordinate out = topLeftEdge.pixelCoordinate(1920, 1080);
        ASSERT_EQ(pct_coord_to_px_coord_fake.call_count, 1);
        ASSERT_EQ(out, ptopLeftEdge);
    }

    TEST_F(RelativeCoordinateCPPTests, RelativeCoordinate) {
        pct_coord_to_px_coord_fake.return_val = { -959, 540, 1920, 1080 };
        px_coord_to_cam_coord_fake.return_val = { 0, 0, 1920, 1080 };
        const GU::RelativeCoordinate topLeftEdge = GU::RelativeCoordinate(-1.0f, 1.0f);
        const GU::RelativeCoordinate ctopLeftEdge = GU::RelativeCoordinate(0, 0, 1920, 1080);
        const GU::RelativeCoordinate out = topLeftEdge.cameraCoordinate(1920, 1080);
        ASSERT_EQ(pct_coord_to_px_coord_fake.call_count, 1);
        ASSERT_EQ(px_coord_to_cam_coord_fake.call_count, 1);
        ASSERT_EQ(out.x(), ctopLeftEdge.x());
        ASSERT_EQ(out.y(), ctopLeftEdge.y());
        ASSERT_EQ(out.resWidth(), ctopLeftEdge.resWidth());
        ASSERT_EQ(out.resHeight(), ctopLeftEdge.resHeight());
    }
*/
}  // namespace
