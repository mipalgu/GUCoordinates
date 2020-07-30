/*
 * CameraPivotTests.cc 
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

    class CameraPivotCPPTests: public GUWrapperTests<GU::CameraPivot, gu_camera_pivot> {

        protected:

        gu_camera cameras[GU_CAMERA_PIVOT_NUM_CAMERAS];
        gu_camera_pivot empty_strct;
    
        void preamble()
        {
            cameras[0] = GU_NAO_V5_TOP_CAMERA;
            cameras[1] = GU_NAO_V5_BOTTOM_CAMERA;
            for (int i = 2; i < GU_CAMERA_PIVOT_NUM_CAMERAS; i++)
            {
                cameras[i].height = 0.0;
                cameras[i].centerOffset = 0.0;
                cameras[i].vDirection = 0.0;
                cameras[i].vFov = 0.0;
                cameras[i].hFov = 0.0;
            }
            empty_strct.pitch = 0.0;
            empty_strct.yaw = 0.0;
            empty_strct.height = 0.0;
            memcpy(empty_strct.cameras, cameras, GU_CAMERA_PIVOT_NUM_CAMERAS * sizeof(gu_camera));
            empty_strct.numCameras = 0;
        }

        GU::CameraPivot initial()
        {
            return GU::CameraPivot(2.0, 3.0, 4.0, cameras, 2);
        }

        GU::CameraPivot empty()
        {
            return GU::CameraPivot(empty_strct);
        }

        void change(GU::CameraPivot & obj)
        {
            obj.set_pitch(1.0);
        }

        void cchange(gu_camera_pivot & obj)
        {
            obj.pitch = 1.0;
            obj.yaw = 2.0;
            obj.height = 3.0;
            memcpy(obj.cameras, cameras, GU_CAMERA_PIVOT_NUM_CAMERAS * sizeof(gu_camera));
            obj.numCameras = 2;
        }

        gu_camera_pivot cempty()
        {
            return empty();
        }

    };

    WRAPPER_TEST_Fs(CameraPivot, gu_camera_pivot)

    TEST_F(CameraPivotCPPTests, GettersSetters) {
        gu_camera_pivot nao_c = GU_NAO_V5_HEAD(0.0, 0.0);
        GU::CameraPivot nao = nao_c;
        ASSERT_EQ(nao.pitch(), 0.0);
        nao.set_pitch(5.0);
        ASSERT_EQ(nao.pitch(), 5.0);
        ASSERT_EQ(nao.yaw(), 0.0);
        nao.set_yaw(6.0);
        ASSERT_EQ(nao.yaw(), 6.0);
        ASSERT_EQ(nao.height(), 41.7);
        nao.set_height(7.0);
        ASSERT_EQ(nao.height(), 7.0);
        equals(nao.camera(0), nao_c.cameras[0]);
        nao.set_camera(0, nao_c.cameras[1]);
        equals(nao.camera(1), nao_c.cameras[1]);
    }

}  // namespace
