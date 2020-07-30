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

#include "GUWrapperTests.hpp"

namespace CGTEST {
    
    class RelativeCoordinateCPPTests: public GUWrapperTests<GU::RelativeCoordinate, gu_relative_coordinate> {

        protected:

        GU::RelativeCoordinate initial()
        {
            return GU::RelativeCoordinate(90, 100);
        }

        GU::RelativeCoordinate empty()
        {
            return GU::RelativeCoordinate(0, 0);
        }

        void change(GU::RelativeCoordinate &obj)
        {
            obj.set_direction(-90);
        }

        void cchange(gu_relative_coordinate &obj)
        {
            obj.direction = 40;
            obj.distance = 15;
        }

        gu_relative_coordinate cempty()
        {
            return empty();
        }

    };

    WRAPPER_TEST_Fs(RelativeCoordinate, gu_relative_coordinate)
    GETTER_BOOL_TEST_F(RelativeCoordinate, PercentCoordinate, rr_coord_to_pct_coord, rawPercentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_BOOL_IM_TEST_F(RelativeCoordinate, PixelCoordinate, rr_coord_to_pct_coord, pct_coord_to_px_coord, rawPixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_BOOL_IM_TEST_F(RelativeCoordinate, CameraCoordinate, rr_coord_to_pct_coord, px_coord_to_cam_coord, rawCameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_IM_TEST_F(RelativeCoordinate, CameraCoordinate, rr_coord_to_pct_coord, px_coord_to_cam_coord, cameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_IM_TEST_F(RelativeCoordinate, PixelCoordinate, rr_coord_to_pct_coord, pct_coord_to_px_coord, pixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_TEST_F(RelativeCoordinate, PercentCoordinate, rr_coord_to_pct_coord, percentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_TEST_F(RelativeCoordinate, CartesianCoordinate, rr_coord_to_cartesian_coord, cartesianCoordinate())
    GETTER_TEST_F(RelativeCoordinate, FieldCoordinate, rr_coord_to_field_coord, fieldCoordinate(30))
    GETTER_TEST_F(RelativeCoordinate, RelativeCoordinate, cartesian_coord_to_rr_coord_from_source, relativeCoordinateTo(GU::RelativeCoordinate(30, 120)))

    GETTER_IM_TEST_NAME_F(RelativeCoordinate, unsafeCameraCoordinate, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafeCameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(RelativeCoordinate, unsafePixelCoordinate, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafePixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_TEST_NAME_F(RelativeCoordinate, unsafePercentCoordinate, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafePercentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_IM_TEST_NAME_F(RelativeCoordinate, unsafeClampedCameraCoordinate, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedCameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(RelativeCoordinate, unsafeClampedPixelCoordinate, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedPixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_TEST_NAME_F(RelativeCoordinate, unsafeClampedPercentCoordinate, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedPercentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_IM_TEST_NAME_F(RelativeCoordinate, unsafeClampedToleranceCameraCoordinate, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedCameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1))
    GETTER_IM_TEST_NAME_F(RelativeCoordinate, unsafeClampedTolerancePixelCoordinate, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedPixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1))
    GETTER_TEST_NAME_F(RelativeCoordinate, unsafeClampedTolerancePercentCoordinate, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedPercentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1))

    GETTER_BOOL_IM_TEST_NAME_F(RelativeCoordinate, clampedToleranceCameraCoordinate, CameraCoordinate, clamped_tolerance_rr_coord_to_pct_coord, px_coord_to_cam_coord, rawClampedCameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1))
    GETTER_BOOL_IM_TEST_NAME_F(RelativeCoordinate, clampedTolerancePixelCoordinate, PixelCoordinate, clamped_tolerance_rr_coord_to_pct_coord, pct_coord_to_px_coord, rawClampedPixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1))
    GETTER_BOOL_TEST_NAME_F(RelativeCoordinate, clampedTolerancePercentCoordinate, PercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedPercentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1))
    GETTER_OPT_IM_TEST_NAME_F(RelativeCoordinate, optClampedToleranceCameraCoordinate, CameraCoordinate, clamped_tolerance_rr_coord_to_pct_coord, px_coord_to_cam_coord, clampedCameraCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1))
    GETTER_OPT_IM_TEST_NAME_F(RelativeCoordinate, optClampedTolerancePixelCoordinate, PixelCoordinate, clamped_tolerance_rr_coord_to_pct_coord, pct_coord_to_px_coord, clampedPixelCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1))
    GETTER_OPT_TEST_NAME_F(RelativeCoordinate, optClampedTolerancePercentCoordinate, PercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, clampedPercentCoordinate(nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1))

    TEST_F(RelativeCoordinateCPPTests, GettersSetters) {
        GU::RelativeCoordinate coord = GU::RelativeCoordinate(90.0, 1000);
        ASSERT_EQ(coord.direction(), 90.0);
        coord.set_direction(-90.0);
        ASSERT_EQ(coord.direction(), -90.0);
        ASSERT_EQ(coord.distance(), 1000);
        coord.set_distance(100);
        ASSERT_EQ(coord.distance(), 100);
    }

}  // namespace
