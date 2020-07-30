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

#include "GUWrapperTests.hpp"

namespace CGTEST {
    
    class CameraCPPTests: public GUWrapperTests<GU::Camera, gu_camera> {

        protected:

        GU::Camera initial()
        {
            return GU::Camera(1.0, 1.5, 2.0, 3.0, 4.0);
        }

        GU::Camera empty()
        {
            return GU::Camera(0.0, 0.0, 0.0, 0.0, 0.0);
        }

        void change(GU::Camera &obj)
        {
            obj.set_height(0.0);
        }

        void cchange(gu_camera &obj)
        {
            obj.height = 1.0;
            obj.centerOffset = 2.0;
            obj.vDirection = 3.0;
            obj.vFov = 4.0;
            obj.hFov = 5.0;
        }

        gu_camera cempty()
        {
            return empty();
        }

    };

    WRAPPER_TEST_Fs(Camera, gu_camera)

    TEST_F(CameraCPPTests, GettersSetters) {
        GU::Camera camera = GU::Camera(1.0, 1.5, 2.0, 3.0, 4.0);
        ASSERT_EQ(camera.height(), 1.0);
        camera.set_height(-1.0);
        ASSERT_EQ(camera.height(), -1.0);
        ASSERT_EQ(camera.centerOffset(), 1.5);
        camera.set_centerOffset(-1.5);
        ASSERT_EQ(camera.centerOffset(), -1.5);
        ASSERT_EQ(camera.vDirection(), 2.0);
        camera.set_vDirection(-2.0);
        ASSERT_EQ(camera.vDirection(), -2.0);
        ASSERT_EQ(camera.vFov(), 3.0);
        camera.set_vFov(-3.0);
        ASSERT_EQ(camera.vFov(), -3.0);
        ASSERT_EQ(camera.hFov(), 4.0);
        camera.set_hFov(-4.0);
        ASSERT_EQ(camera.hFov(), -4.0);
    }

}  // namespace
