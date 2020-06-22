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

#include "GUCoordinatesTests.hpp" 

namespace CGTEST {

    class RobotCPPTests: public GUCoordinatesTests<GU::Robot, gu_robot> {

        protected:

        gu_camera cameras[GU_ROBOT_NUM_CAMERAS];
        centimetres_f offsets[GU_ROBOT_NUM_CAMERAS];
        gu_robot empty_strct;
    
        void preamble()
        {
            cameras[0] = GU_NAO_V5_TOP_CAMERA;
            cameras[1] = GU_NAO_V5_BOTTOM_CAMERA;
            offsets[0] = 0.0f;
            offsets[1] = 0.0f;
            for (int i = 2; i < GU_ROBOT_NUM_CAMERAS; i++)
            {
                cameras[i].height = 0.0f;
                cameras[i].centerOffset = 0.0f;
                cameras[i].vDirection = 0.0f;
                cameras[i].vFov = 0.0f;
                cameras[i].hFov = 0.0f;
                offsets[i] = 0.0f;
            }
            empty_strct.headPitch = 0.0f;
            empty_strct.headYaw = 0.0f;
            memcpy(empty_strct.cameras, cameras, GU_ROBOT_NUM_CAMERAS * sizeof(gu_camera));
            memcpy(empty_strct.cameraHeightOffsets, offsets, GU_ROBOT_NUM_CAMERAS * sizeof(centimetres_f));
            empty_strct.numCameras = 0;
        }

        GU::Robot initial()
        {
            return GU::Robot(2.0f, 3.0f, cameras, offsets, 2);
        }

        gu_robot empty()
        {
            return empty_strct;
        }

        void change(GU::Robot & obj)
        {
            obj.set_headPitch(1.0f);
        }

        void cchange(gu_robot & obj)
        {
            obj.headPitch = 1.0f; \
            obj.headYaw = 2.0f; \
            memcpy(obj.cameras, cameras, GU_ROBOT_NUM_CAMERAS * sizeof(gu_camera)); \
            memcpy(obj.cameraHeightOffsets, offsets, GU_ROBOT_NUM_CAMERAS * sizeof(centimetres_f)); \
            obj.numCameras = 2;
        }

    };

    WRAPPER_TEST_Fs(Robot, gu_robot)

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

}  // namespace
