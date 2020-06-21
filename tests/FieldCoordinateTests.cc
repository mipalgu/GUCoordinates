/*
 * FieldCoordinateTests.cc 
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

#include "GUCoordinatesTests.hpp"

namespace CGTEST {
    
    class FieldCoordinateCPPTests: public GUCoordinatesTests<GU::FieldCoordinate, gu_field_coordinate> {

        protected:

        GU::FieldCoordinate initial()
        {
            return GU::FieldCoordinate(GU::CartesianCoordinate(90, 50), 100);
        }

        gu_field_coordinate empty()
        {
            return { { 0, 0 }, 0 };
        }

        void change(GU::FieldCoordinate &obj)
        {
            obj.set_position(GU::CartesianCoordinate(-90, -50));
        }

        void cchange(gu_field_coordinate &obj)
        {
            obj = { {40, 30}, 15};
        }

    };

    WRAPPER_TEST_Fs(FieldCoordinate, gu_field_coordinate)

    TEST_F(FieldCoordinateCPPTests, GettersSetters) {
        GU::FieldCoordinate coord = GU::FieldCoordinate(GU::CartesianCoordinate(90, 50), 100);
        equals(coord.position(), GU::CartesianCoordinate(90, 50));
        coord.set_position(GU::CartesianCoordinate(-90, -50));
        equals(coord.position(), GU::CartesianCoordinate(-90, -50));
        ASSERT_EQ(coord.heading(), 100);
        coord.set_heading(10);
        ASSERT_EQ(coord.heading(), 10);
    }

}  // namespace
