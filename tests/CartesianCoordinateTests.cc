/*
 * CartesianCoordinateTests.cc 
 * tests 
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

#include "GUWrapperTests.hpp"

namespace CGTEST {
    
    class CartesianCoordinateCPPTests: public GUWrapperTests<GU::CartesianCoordinate, gu_cartesian_coordinate> {

        protected:

        GU::CartesianCoordinate initial()
        {
            return GU::CartesianCoordinate(90, 100);
        }

        GU::CartesianCoordinate empty()
        {
            return GU::CartesianCoordinate(0, 0);
        }

        void change(GU::CartesianCoordinate &obj)
        {
            obj.set_x(-90);
        }

        void cchange(gu_cartesian_coordinate &obj)
        {
            obj.x = 40;
            obj.y = 15;
        }

        gu_cartesian_coordinate cempty()
        {
            return empty();
        }

    };

    WRAPPER_TEST_Fs(CartesianCoordinate, gu_cartesian_coordinate)

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeCartesianCoordinateCamera, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, RelativeCoordinate, unsafe_pct_coord_to_rr_coord, unsafeCartesianCoordinateAt(GU::CameraCoordinate(23, 52, 1920, 1080), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeCartesianCoordinatePixel, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, RelativeCoordinate, unsafe_pct_coord_to_rr_coord, unsafeCartesianCoordinateAt(GU::PixelCoordinate(42, -123, 1920, 1080), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeCartesianCoordinatePercent, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, RelativeCoordinate, unsafe_pct_coord_to_rr_coord, unsafeCartesianCoordinateAt(GU::PercentCoordinate(-0.24f, 0.5f), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, CartesianCoordinateCameraBool, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, OptionalRelativeCoordinate, pct_coord_to_rr_coord, rawCartesianCoordinateAt(GU::CameraCoordinate(23, 52, 1920, 1080), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, CartesianCoordinatePixelBool, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, OptionalRelativeCoordinate, pct_coord_to_rr_coord, rawCartesianCoordinateAt(GU::PixelCoordinate(42, -123, 1920, 1080), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, CartesianCoordinatePercentBool, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, OptionalRelativeCoordinate, pct_coord_to_rr_coord, rawCartesianCoordinateAt(GU::PercentCoordinate(-0.24f, 0.5f), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, CartesianCoordinateCamera, CartesianCoordinate, pct_coord_to_rr_coord, rr_coord_to_cartesian_coord_from_source, cartesianCoordinateAt(GU::CameraCoordinate(23, 52, 1920, 1080), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, CartesianCoordinatePixel, CartesianCoordinate, pct_coord_to_rr_coord, rr_coord_to_cartesian_coord_from_source, cartesianCoordinateAt(GU::PixelCoordinate(42, -123, 1920, 1080), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, CartesianCoordinatePercent, CartesianCoordinate, pct_coord_to_rr_coord, rr_coord_to_cartesian_coord_from_source, cartesianCoordinateAt(GU::PercentCoordinate(-0.24f, 0.5f), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_TEST_F(CartesianCoordinate, CartesianCoordinate, rr_coord_to_cartesian_coord_from_source, cartesianCoordinateAt(GU::RelativeCoordinate(10, 123)))
    GETTER_TEST_NAME_F(CartesianCoordinate, RelativeCoordinateCartesian, RelativeCoordinate, cartesian_coord_to_rr_coord_from_source, relativeCoordinateTo(GU::CartesianCoordinate(123, 323)))
    GETTER_TEST_NAME_F(CartesianCoordinate, RelativeCoordinateField, RelativeCoordinate, cartesian_coord_to_rr_coord_from_source, relativeCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(123, 323), -50)))

    GETTER_TEST_NAME_F(CartesianCoordinate, PercentCoordinateCartesianBool, OptionalPercentCoordinate, rr_coord_to_pct_coord, rawPercentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_TEST_NAME_F(CartesianCoordinate, PercentCoordinateFieldBool, OptionalPercentCoordinate, rr_coord_to_pct_coord, rawPercentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_OPT_TEST_NAME_F(CartesianCoordinate, PercentCoordinateCartesian, PercentCoordinate, rr_coord_to_pct_coord, percentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_OPT_TEST_NAME_F(CartesianCoordinate, PercentCoordinateField, PercentCoordinate, rr_coord_to_pct_coord, percentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, PixelCoordinateCartesianBool, PixelCoordinate, pct_coord_to_px_coord, OptionalPercentCoordinate, rr_coord_to_pct_coord, rawPixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, PixelCoordinateFieldBool, PixelCoordinate, pct_coord_to_px_coord, OptionalPercentCoordinate, rr_coord_to_pct_coord, rawPixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, PixelCoordinateCartesian, PixelCoordinate, rr_coord_to_pct_coord, pct_coord_to_px_coord, pixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, PixelCoordinateField, PixelCoordinate, rr_coord_to_pct_coord, pct_coord_to_px_coord, pixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, CameraCoordinateCartesianBool, CameraCoordinate, px_coord_to_cam_coord, OptionalPercentCoordinate, rr_coord_to_pct_coord, rawCameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, CameraCoordinateFieldBool, CameraCoordinate, px_coord_to_cam_coord, OptionalPercentCoordinate, rr_coord_to_pct_coord, rawCameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, CameraCoordinateCartesian, CameraCoordinate, rr_coord_to_pct_coord, px_coord_to_cam_coord, cameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, CameraCoordinateField, CameraCoordinate, rr_coord_to_pct_coord, px_coord_to_cam_coord, cameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))

    GETTER_TEST_NAME_F(CartesianCoordinate, unsafePercentCoordinateCartesianBool, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafePercentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_TEST_NAME_F(CartesianCoordinate, unsafePercentCoordinateFieldBool, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafePercentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafePixelCoordinateCartesianBool, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafePixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafePixelCoordinateFieldBool, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafePixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeCameraCoordinateCartesianBool, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafeCameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeCameraCoordinateFieldBool, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_rr_coord_to_pct_coord, unsafeCameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))

    GETTER_TEST_NAME_F(CartesianCoordinate, unsafeClampedPercentCoordinateCartesianBool, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedPercentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))
    GETTER_TEST_NAME_F(CartesianCoordinate, unsafeClampedPercentCoordinateFieldBool, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedPercentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedPixelCoordinateCartesianBool, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedPixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedPixelCoordinateFieldBool, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedPixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedCameraCoordinateCartesianBool, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedCameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedCameraCoordinateFieldBool, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_clamped_rr_coord_to_pct_coord, unsafeClampedCameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080))

    GETTER_TEST_NAME_F(CartesianCoordinate, unsafeClampedTolerancePercentCoordinateCartesianBool, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedPercentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1f))
    GETTER_TEST_NAME_F(CartesianCoordinate, unsafeClampedTolerancePercentCoordinateFieldBool, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedPercentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1f))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedTolerancePixelCoordinateCartesianBool, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedPixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedTolerancePixelCoordinateFieldBool, PixelCoordinate, pct_coord_to_px_coord, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedPixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedToleranceCameraCoordinateCartesianBool, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedCameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, unsafeClampedToleranceCameraCoordinateFieldBool, CameraCoordinate, px_coord_to_cam_coord, PercentCoordinate, unsafe_clamped_tolerance_rr_coord_to_pct_coord, unsafeClampedCameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))

    GETTER_TEST_NAME_F(CartesianCoordinate, clampedTolerancePercentCoordinateCartesianBool, OptionalPercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedPercentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1f))
    GETTER_TEST_NAME_F(CartesianCoordinate, clampedTolerancePercentCoordinateFieldBool, OptionalPercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedPercentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1f))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, clampedTolerancePixelCoordinateCartesianBool, PixelCoordinate, pct_coord_to_px_coord, OptionalPercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedPixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, clampedTolerancePixelCoordinateFieldBool, PixelCoordinate, pct_coord_to_px_coord, OptionalPercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedPixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))

    GETTER_IM_TEST_NAME_F(CartesianCoordinate, clampedToleranceCameraCoordinateCartesianBool, CameraCoordinate, px_coord_to_cam_coord, OptionalPercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedCameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))
    GETTER_IM_TEST_NAME_F(CartesianCoordinate, clampedToleranceCameraCoordinateFieldBool, CameraCoordinate, px_coord_to_cam_coord, OptionalPercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, rawClampedCameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))

    GETTER_OPT_TEST_NAME_F(CartesianCoordinate, optClampedTolerancePercentCoordinateCartesianBool, PercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, clampedPercentCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1f))
    GETTER_OPT_TEST_NAME_F(CartesianCoordinate, optClampedTolerancePercentCoordinateFieldBool, PercentCoordinate, clamped_tolerance_rr_coord_to_pct_coord, clampedPercentCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 0.1f))

    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, optClampedTolerancePixelCoordinateCartesianBool, PixelCoordinate, clamped_tolerance_rr_coord_to_pct_coord, pct_coord_to_px_coord, clampedPixelCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, optClampedTolerancePixelCoordinateFieldBool, PixelCoordinate, clamped_tolerance_rr_coord_to_pct_coord, pct_coord_to_px_coord, clampedPixelCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))

    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, optClampedToleranceCameraCoordinateCartesianBool, CameraCoordinate, clamped_tolerance_rr_coord_to_pct_coord, px_coord_to_cam_coord, clampedCameraCoordinateTo(GU::CartesianCoordinate(-3, 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))
    GETTER_OPT_IM_TEST_NAME_F(CartesianCoordinate, optClampedToleranceCameraCoordinateFieldBool, CameraCoordinate, clamped_tolerance_rr_coord_to_pct_coord, px_coord_to_cam_coord, clampedCameraCoordinateTo(GU::FieldCoordinate(GU::CartesianCoordinate(23, 100), 12), nao, GU_NAO_V5_BOTTOM_CAMERA_INDEX, 1920, 1080, 0.1f))


    TEST_F(CartesianCoordinateCPPTests, GettersSetters) {
        GU::CartesianCoordinate coord = GU::CartesianCoordinate(90, 100);
        ASSERT_EQ(coord.x(), 90);
        coord.set_x(-90);
        ASSERT_EQ(coord.x(), -90);
        ASSERT_EQ(coord.y(), 100);
        coord.set_y(10);
        ASSERT_EQ(coord.y(), 10);
    }

}  // namespace
