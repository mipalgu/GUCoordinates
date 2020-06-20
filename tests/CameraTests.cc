/*
 * CameraTests.cc 
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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma clang diagnostic ignored "-Wshift-sign-overflow"
#pragma clang diagnostic ignored "-Wused-but-marked-unused"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-compare"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wfloat-equal"

#include <gtest/gtest.h>
#include "fff.h"

#include "../GUCoordinates.hpp"
#include "fakes.h"

namespace CGTEST {
    
    class CameraCPPTests: public ::testing::Test {
    protected:
        
        virtual void SetUp() {
            ALL_FAKES(RESET_FAKE);
            FFF_RESET_HISTORY();
        }
        
        virtual void TearDown() {
            ALL_FAKES(RESET_FAKE);
            FFF_RESET_HISTORY();
        }

    };

    void camera_equals(const GU::Camera lhs, const GU::Camera rhs)
    {
        ASSERT_EQ(lhs.height(), rhs.height());
        ASSERT_EQ(lhs.centerOffset(), rhs.centerOffset());
        ASSERT_EQ(lhs.vDirection(), rhs.vDirection());
        ASSERT_EQ(lhs.vFov(), rhs.vFov());
        ASSERT_EQ(lhs.hFov(), rhs.hFov());
    }

    void camera_nequals(const GU::Camera lhs, const GU::Camera rhs)
    {
        ASSERT_FALSE(lhs.height() == rhs.height()
                && lhs.centerOffset() == rhs.centerOffset()
                && lhs.vDirection() == rhs.vDirection()
                && lhs.vFov() == rhs.vFov()
                && lhs.hFov() == rhs.hFov()
                );
    }

    TEST_F(CameraCPPTests, RO5)
    {
        GU::Camera camera = GU::Camera(1.0f, 1.5f, 2.0f, 3.0f, 4.0f);
        GU::Camera camera2 = GU::Camera(camera);
        camera_equals(camera, camera2);
        GU::Camera camera3 = camera2;
        camera_equals(camera, camera3);
        camera.set_height(0.0f);
        camera_nequals(camera, camera3);
        camera_equals(camera2, camera3);
#if __cplusplus >= 199711L
        GU::Camera camera4 = std::move(camera2);
        camera_nequals(camera4, camera2);
        camera_equals(camera4, camera3);
        ASSERT_EQ(camera2.height(), 0.0f);
        ASSERT_EQ(camera2.centerOffset(), 0.0f);
        ASSERT_EQ(camera2.vDirection(), 0.0f);
        ASSERT_EQ(camera2.vFov(), 0.0f);
        ASSERT_EQ(camera2.hFov(), 0.0f);
        GU::Camera camera5;
        camera5 = std::move(camera4);
        camera_nequals(camera5, camera2);
        camera_equals(camera5, camera3);
        ASSERT_EQ(camera4.height(), 0.0f);
        ASSERT_EQ(camera4.centerOffset(), 0.0f);
        ASSERT_EQ(camera4.vDirection(), 0.0f);
        ASSERT_EQ(camera4.vFov(), 0.0f);
        ASSERT_EQ(camera4.hFov(), 0.0f);
#endif
        const gu_camera camera6 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        GU::Camera camera7 = camera6;
        GU::Camera camera8;
        camera8 = camera6;
        camera_equals(camera7, camera6);
        camera_equals(camera8, camera6);
        camera_equals(camera7, camera8);
    }

    TEST_F(CameraCPPTests, GettersSetters) {
        GU::Camera camera = GU::Camera(1.0f, 1.5f, 2.0f, 3.0f, 4.0f);
        ASSERT_EQ(camera.height(), 1.0f);
        camera.set_height(-1.0f);
        ASSERT_EQ(camera.height(), -1.0f);
        ASSERT_EQ(camera.centerOffset(), 1.5f);
        camera.set_centerOffset(-1.5f);
        ASSERT_EQ(camera.centerOffset(), -1.5f);
        ASSERT_EQ(camera.vDirection(), 2.0f);
        camera.set_vDirection(-2.0f);
        ASSERT_EQ(camera.vDirection(), -2.0f);
        ASSERT_EQ(camera.vFov(), 3.0f);
        camera.set_vFov(-3.0f);
        ASSERT_EQ(camera.vFov(), -3.0f);
        ASSERT_EQ(camera.hFov(), 4.0f);
        camera.set_hFov(-4.0f);
        ASSERT_EQ(camera.hFov(), -4.0f);
    }

    TEST_F(CameraCPPTests, Equality) {
        gu_camera_equals_fake.return_val = true;
        const GU::Camera topCamera = NAO_V5_TOP_CAMERA;
        const GU::Camera bottomCamera = NAO_V5_BOTTOM_CAMERA;
        ASSERT_EQ(topCamera, topCamera);
        ASSERT_EQ(gu_camera_equals_fake.call_count, 1);
        RESET_FAKE(gu_camera_equals)
        gu_camera_equals_fake.return_val = false;
        ASSERT_NE(topCamera, bottomCamera);
        ASSERT_EQ(gu_camera_coordinate_equals_fake.call_count, 1);
    }

}  // namespace

#pragma clang diagnostic pop
