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

#include "GUCoordinatesTests.hpp"

#define RO5_PREAMBLE \
    gu_camera cameras[GU_ROBOT_NUM_CAMERAS]; \
    cameras[0] = NAO_V5_TOP_CAMERA; \
    cameras[1] = NAO_V5_BOTTOM_CAMERA; \
    centimetres_f offsets[GU_ROBOT_NUM_CAMERAS]; \
    offsets[0] = 0.0f; \
    offsets[1] = 0.0f; \
    for (int i = 2; i < GU_ROBOT_NUM_CAMERAS; i++) \
    { \
        cameras[i] = {}; \
        offsets[i] = 0.0f; \
    } \
    gu_robot empty; \
    empty.headPitch = 0.0f; \
    empty.headYaw = 0.0f; \
    memcpy(empty.cameras, cameras, GU_ROBOT_NUM_CAMERAS * sizeof(gu_camera)); \
    memcpy(empty.cameraHeightOffsets, offsets, GU_ROBOT_NUM_CAMERAS * sizeof(centimetres_f)); \
    empty.numCameras = 0;

#define RO5_CCHANGE \
    obj6.headPitch = 1.0f; \
    obj6.headYaw = 2.0f; \
    memcpy(obj6.cameras, cameras, GU_ROBOT_NUM_CAMERAS * sizeof(gu_camera)); \
    memcpy(obj6.cameraHeightOffsets, offsets, GU_ROBOT_NUM_CAMERAS * sizeof(centimetres_f)); \
    obj6.numCameras = 2;

#define RO5_EMPTY empty

#define RobotCPPTests_CLASS GU::Robot

#define RobotCPPTests_INITIAL GU::Robot(2.0f, 3.0f, cameras, offsets, 2)

#define RobotCPPTests_CHANGE obj.set_headPitch(1.0f);


namespace CGTEST {

    class RobotCPPTests: public GUCoordinatesTests {};

    RO5_TEST_F(RobotCPPTests, RO5, gu_robot, RobotCPPTests_CLASS, RO5_PREAMBLE, RobotCPPTests_INITIAL, RobotCPPTests_CHANGE, RO5_CCHANGE, RO5_EMPTY)

    TEST_F(RobotCPPTests, GettersSetters) {
        gu_robot nao_c = GU_NAO_V5_ROBOT(0.0f, 0.0f);
        GU::Robot nao = nao_c;
        ASSERT_EQ(nao.headPitch(), 0.0f);
        nao.set_headPitch(5.0f);
        ASSERT_EQ(nao.headPitch(), 5.0f);
        ASSERT_EQ(nao.headYaw(), 0.0f);
        nao.set_headYaw(6.0f);
        ASSERT_EQ(nao.headYaw(), 6.0f);
        equals(nao.camera(0), nao_c.cameras[0]);
        nao.set_camera(0, nao_c.cameras[1]);
        equals(nao.camera(1), nao_c.cameras[1]);
        ASSERT_EQ(nao.cameraHeightOffset(0), nao_c.cameraHeightOffsets[0]);
        nao.set_cameraHeightOffset(0, nao_c.cameraHeightOffsets[1]);
        ASSERT_EQ(nao.cameraHeightOffset(1), nao_c.cameraHeightOffsets[1]);
    }

    TEST_F(RobotCPPTests, Equality) {
        gu_robot_equals_fake.return_val = true;
        const GU::Robot nao = GU::Robot(GU_NAO_V5_ROBOT(0.0f, 0.0f));
        const GU::Robot nao2 = GU::Robot(GU_NAO_V5_ROBOT(5.0f, 0.0f));
        ASSERT_EQ(nao, nao);
        ASSERT_EQ(gu_robot_equals_fake.call_count, 1);
        RESET_FAKE(gu_robot_equals)
        gu_robot_equals_fake.return_val = false;
        ASSERT_NE(nao, nao2);
        ASSERT_EQ(gu_robot_equals_fake.call_count, 1);
    }

}  // namespace

#pragma clang diagnostic pop
