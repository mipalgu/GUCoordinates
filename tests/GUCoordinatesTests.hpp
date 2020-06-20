/*
 * GUCoordinatesTests.hpp 
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

#ifndef GUCOORDINATESTESTS_HPP
#define GUCOORDINATESTESTS_HPP

#include <gtest/gtest.h>
#include "fff.h"

#include "../GUCoordinates.hpp"
#include "fakes.h"

#if __cplusplus >= 199711L
#define RO5_TEST_CPP17(testclass) \
    testclass##_CLASS obj4 = std::move(obj2); \
    nequals(obj4, obj2); \
    equals(obj4, obj3); \
    equals(obj2, testclass##_EMPTY); \
    testclass##_CLASS obj5; \
    obj5 = std::move(obj4); \
    nequals(obj5, obj2); \
    equals(obj5, obj3); \
    equals(obj4, testclass##_EMPTY);
#else
#define RO5_TEST_CPP17(class, empty) do { } while(0);
#endif


#define RO5_TEST_F(testclass) \
    TEST_F(testclass, testclass##_RO5) \
    { \
        testclass##_PREAMBLE \
        testclass##_CLASS obj = testclass##_INITIAL; \
        testclass##_CLASS obj2 = testclass##_CLASS(obj); \
        equals(obj, obj2); \
        testclass##_CLASS obj3 = obj2; \
        equals(obj, obj3); \
        testclass##_CHANGE \
        nequals(obj, obj3); \
        equals(obj2, obj3); \
        RO5_TEST_CPP17(testclass) \
        testclass##_STRCT obj6 = {}; \
        testclass##_CCHANGE \
        testclass##_CLASS obj7 = obj6; \
        testclass##_CLASS obj8; \
        obj8 = obj6; \
        equals(obj7, obj6); \
        equals(obj8, obj6); \
        equals(obj7, obj8); \
    }

namespace CGTEST {

    class GUCoordinatesTests: public ::testing::Test {
        protected:

            virtual void SetUp() {
                ALL_FAKES(RESET_FAKE);
                FFF_RESET_HISTORY();
            }

            virtual void TearDown() {
                ALL_FAKES(RESET_FAKE);
                FFF_RESET_HISTORY();
            }

            void equals(const GU::CameraCoordinate lhs, const GU::CameraCoordinate rhs)
            {
                ASSERT_EQ(lhs.x(), rhs.x());
                ASSERT_EQ(lhs.y(), rhs.y());
                ASSERT_EQ(lhs.resWidth(), rhs.resWidth());
                ASSERT_EQ(lhs.resHeight(), rhs.resHeight());
            }

            void nequals(const GU::CameraCoordinate lhs, const GU::CameraCoordinate rhs)
            {
                ASSERT_FALSE(lhs.x() == rhs.x()
                        && lhs.y() == rhs.y()
                        && lhs.resWidth() == rhs.resWidth()
                        && lhs.resHeight() == rhs.resHeight()
                        );
            }

            void equals(const GU::Camera lhs, const GU::Camera rhs)
            {
                ASSERT_EQ(lhs.height(), rhs.height());
                ASSERT_EQ(lhs.centerOffset(), rhs.centerOffset());
                ASSERT_EQ(lhs.vDirection(), rhs.vDirection());
                ASSERT_EQ(lhs.vFov(), rhs.vFov());
                ASSERT_EQ(lhs.hFov(), rhs.hFov());
            }

            void nequals(const GU::Camera lhs, const GU::Camera rhs)
            {
                ASSERT_FALSE(lhs.height() == rhs.height()
                        && lhs.centerOffset() == rhs.centerOffset()
                        && lhs.vDirection() == rhs.vDirection()
                        && lhs.vFov() == rhs.vFov()
                        && lhs.hFov() == rhs.hFov()
                        );
            }

            void equals(const GU::PixelCoordinate lhs, const GU::PixelCoordinate rhs)
            {
                ASSERT_EQ(lhs.x(), rhs.x());
                ASSERT_EQ(lhs.y(), rhs.y());
                ASSERT_EQ(lhs.resWidth(), rhs.resWidth());
                ASSERT_EQ(lhs.resHeight(), rhs.resHeight());
            }

            void nequals(const GU::PixelCoordinate lhs, const GU::PixelCoordinate rhs)
            {
                ASSERT_FALSE(
                        lhs.x() == rhs.x()
                        && lhs.y() == rhs.y()
                        && lhs.resWidth() == rhs.resWidth()
                        && lhs.resHeight() == rhs.resHeight()
                    );
            }

            void equals(const GU::PercentCoordinate lhs, const GU::PercentCoordinate rhs)
            {
                ASSERT_EQ(lhs.x(), rhs.x());
                ASSERT_EQ(lhs.y(), rhs.y());
            }

            void nequals(const GU::PercentCoordinate lhs, const GU::PercentCoordinate rhs)
            {
                ASSERT_FALSE(
                        lhs.x() == rhs.x()
                        && lhs.y() == rhs.y()
                    );
            }

            void equals(const GU::RelativeCoordinate lhs, const GU::RelativeCoordinate rhs)
            {
                ASSERT_EQ(lhs.direction(), rhs.direction());
                ASSERT_EQ(lhs.distance(), rhs.distance());
            }

            void nequals(const GU::RelativeCoordinate lhs, const GU::RelativeCoordinate rhs)
            {
                ASSERT_FALSE(
                        lhs.direction() == rhs.direction()
                        && lhs.distance() == rhs.distance()
                    );
            }

            void equals(const GU::Robot lhs, const GU::Robot rhs)
            {
                ASSERT_EQ(lhs.headPitch(), rhs.headPitch());
                ASSERT_EQ(lhs.headYaw(), rhs.headYaw());
                ASSERT_EQ(lhs.numCameras(), rhs.numCameras());
                for (int i = 0; i < lhs.numCameras(); i++)
                {
                    const GU::Camera lcamera = lhs.camera(i);
                    const GU::Camera rcamera = rhs.camera(i);
                    ASSERT_EQ(lcamera.height(), rcamera.height());
                    ASSERT_EQ(lcamera.centerOffset(), rcamera.centerOffset());
                    ASSERT_EQ(lcamera.vDirection(), rcamera.vDirection());
                    ASSERT_EQ(lcamera.vFov(), rcamera.vFov());
                    ASSERT_EQ(lcamera.hFov(), rcamera.hFov());
                    ASSERT_EQ(lhs.cameraHeightOffset(i), rhs.cameraHeightOffset(i));
                }
            }

            void nequals(const GU::Robot lhs, const GU::Robot rhs)
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
                            && lhs.cameraHeightOffset(i) == rhs.cameraHeightOffset(i)
                            );
                }
            }

    };

};

#endif  /* GUCOORDINATESTESTS_HPP */
