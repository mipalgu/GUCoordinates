/*
 * RobotTests.cc 
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

    class RobotCPPTests: public ::testing::Test {
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

    void robot_equals(const GU::Robot lhs, const GU::Robot rhs)
    {
        ASSERT_EQ(lhs.headPitch(), rhs.headPitch());
        ASSERT_EQ(lhs.headYaw(), rhs.headYaw());
        ASSERT_EQ(lhs.numCameras(), rhs.numCameras());
        for (int i = 0; i < lhs.numCameras(); i++)
        {
            const GU::Camera lcamera = lhs.camera(i);
            const GU::Camera rcamers = rhs.camera(i);
            ASSERT_EQ(lcamera.height(), rcamera.height());
            ASSERT_EQ(lcamera.centerOffset(), rcamera.centerOffset());
            ASSERT_EQ(lcamera.vDirection(), rcamera.vDirection());
            ASSERT_EQ(lcamera.vFov(), rcamera.vFov());
            ASSERT_EQ(lcamera.hFov(), rcamera.hFov());
            ASSERT_EQ(lhs.cameraHeightOffset(i), rhs.cameraHeightOffset(i));
        }
    }

    void robot_nequals(const GU::Robot lhs, const GU::Robot rhs)
    {
        if (!(lhs.headPitch() == rhs.headPitch()
                && lhs.headYaw() == rhs.headYaw()
                && lhs.numCameras() == rhs.numCameras()
           ))
        {
            ASSERT_FALSE(lhs.headPitch() == rhs.headPitch()
                && lhs.headYaw() == rhs.headYaw()
                && lhs.numCameras() == rhs.numCameras()
                );
            return;
        }
        for (int i = 0; i < lhs.numCameras(); i++)
        {
            const GU::Camera lcamera = lhs.camera(i);
            const GU::Camera rcamera = rhs.camera(i);
            ASSERT_FALSE(
                    lcamera.height() == rcamera.height()
                    && lcamera.centerOffset() == rcamera.centerOffset()
                    && lcamera.vDirection() == rcamera.vDirection()
                    && lcamera.vFov() == rcamera.vFov()
                    && lcamera.hFov() == rcamera.hFov()
                    && lhs.cameraHeightOffsets(i) == rhs.cameraHeightOffsets(i)
                    );
        }
    }

    TEST_F(RobotCPPTests, RO5)
    {
        const gu_camera cameras[GU_ROBOT_NUM_CAMERAS] = {};
        const centimetres_f offsets[GU_ROBOT_NUM_CAMERAS] = {};
        GU::Robot coord = GU::Robot(2.0f, 3.0f, cameras, offsets, 0);
        GU::Robot coord2 = GU::Robot(coord);
        robot_equals(coord, coord2);
        GU::Robot coord3 = coord2;
        robot_equals(coord, coord3);
        coord.set_headPitch(1.0f);
        robot_nequals(coord, coord3);
        robot_equals(coord2, coord3);
#if __cplusplus >= 199711L
        GU::Robot coord4 = std::move(coord2);
        robot_nequals(coord4, coord2);
        robot_equals(coord4, coord3);
        robot_equals(coord2, {0.0f, 0.0f, cameras, offsets, 0});
        GU::Robot coord5;
        coord5 = std::move(coord4);
        robot_nequals(coord5, coord2);
        robot_equals(coord5, coord3);
        robot_equals(coord4, {0.0f, 0.0f, cameras, offsets, 0});
#endif
        const gu_robot coord6 = {1.0f, 2.0f cameras, offsets, 1};
        GU::Robot coord7 = coord6;
        GU::Robot coord8;
        coord8 = coord6;
        robot_equals(coord7, coord6);
        robot_equals(coord8, coord6);
        robot_equals(coord7, coord8);
    }

    TEST_F(RobotCPPTests, GettersSetters) {
        gu_robot nao_c = GU_NAO_V5_ROBOT(0.0f, 0.0f);
        GU::Robot nao = GU_NAO_V5_Robot(0.0f, 0.0f); 
        ASSERT_EQ(nao.headPitch(), 0.0f);
        coord.set_headPitch(5.0f);
        ASSERT_EQ(nao.headPitch(), 5.0f);
        ASSERT_EQ(nao.headYaw(), 0.0f);
        nao.set_headYaw(6.0f);
        ASSERT_EQ(nao.headYaw(), 6.0f);
        ASSERT_EQ(nao.camera(0), nao_c.cameras[0]);
        nao.set_camera(0, nao_c.cameras[1]);
        ASSERT_EQ(nao.camera(1), nao_c.cameras[1]);
        ASSERT_EQ(nao.cameraHeightOffsets(0), nao_c.cameraHeightOffsets[0]);
        nao.set_cameraHeightOffset(0, nao_c.cameraHeightOffsets[1]);
        ASSERT_EQ(nao.cameraHeightOffset(1), nao_c.cameraHeightOffset[1]);
    }

    TEST_F(RobotCPPTests, Equality) {
        gu_robot_equals_fake.return_val = true;
        const GU::Robot nao = GU_NAO_V5_ROBOT(0.0f, 0.0f);
        const GU::Robot nao2 = GU_NAO_V5_ROBOT(5.0f, 0.0f);
        ASSERT_EQ(nao, nao);
        ASSERT_EQ(gu_robot_equals_fake.call_count, 1);
        RESET_FAKE(gu_robot_equals)
        gu_robot_equals_fake.return_val = false;
        ASSERT_NE(nao, nao2);
        ASSERT_EQ(gu_robot_equals_fake.call_count, 1);
    }

}  // namespace

#pragma clang diagnostic pop
