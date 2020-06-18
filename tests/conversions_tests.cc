/*
 * conversions_tests.cc 
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

#include <gu_util.h>
#include "../conversions.h"

namespace CGTEST {
    
    class ConversionsTests: public ::testing::Test {
    protected:
        
        virtual void SetUp() {
        }
        
        virtual void TearDown() {
        }

    };

    void camera_equal(const gu_camera_coordinate lhs, const gu_camera_coordinate rhs)
    {
        ASSERT_EQ(lhs.x, rhs.x);
        ASSERT_EQ(lhs.y, rhs.y);
        ASSERT_EQ(lhs.res_width, rhs.res_width);
        ASSERT_EQ(lhs.res_height, rhs.res_height);
    }

    void pixel_equal(const gu_pixel_coordinate lhs, const gu_pixel_coordinate rhs)
    {
        ASSERT_EQ(lhs.x, rhs.x);
        ASSERT_EQ(lhs.y, rhs.y);
        ASSERT_EQ(lhs.res_width, rhs.res_width);
        ASSERT_EQ(lhs.res_height, rhs.res_height);
    }

    void percent_equal(const gu_percent_coordinate lhs, const gu_percent_coordinate rhs)
    {
        ASSERT_EQ(lhs.x, rhs.x);
        ASSERT_EQ(lhs.y, rhs.y);
    }

    void percent_near(const gu_percent_coordinate lhs, const gu_percent_coordinate rhs)
    {
        ASSERT_LT(fabs(lhs.x - rhs.x), 0.001);
        ASSERT_LT(fabs(lhs.y - rhs.y), 0.001);
    }

    TEST_F(ConversionsTests, ConvertsToCorrectPercentCoordinate) {
        const gu_pixel_coordinate topLeftEdge = { -959, 540, 1920, 1080 };
        const gu_pixel_coordinate topRightEdge = { 960, 540, 1920, 1080 };
        const gu_pixel_coordinate bottomLeftEdge = { -959, -539, 1920, 1080 };
        const gu_pixel_coordinate bottomRightEdge = { 960, -539, 1920, 1080 };
        const gu_pixel_coordinate middle = { 0, 0, 1920, 1080 };
        percent_equal({-1.0f, 1.0f}, px_coord_to_pct_coord(topLeftEdge));
        percent_equal({1.0f, 1.0f}, px_coord_to_pct_coord(topRightEdge));
        percent_equal({-1.0f, -1.0f}, px_coord_to_pct_coord(bottomLeftEdge));
        percent_equal({1.0f, -1.0f}, px_coord_to_pct_coord(bottomRightEdge));
        percent_near({0.0f, 0.0f}, px_coord_to_pct_coord(middle));
    }

    TEST_F(ConversionsTests, ConvertsToCorrectPixelCoordinate) {
        const gu_percent_coordinate topLeftEdge = { -1.0f, 1.0f };
        const gu_percent_coordinate topRightEdge = { 1.0f, 1.0f };
        const gu_percent_coordinate bottomLeftEdge = { -1.0f, -1.0f };
        const gu_percent_coordinate bottomRightEdge = { 1.0f, -1.0f };
        const gu_percent_coordinate middle = { 0, 0 };
        pixel_equal({ -959, 540, 1920, 1080 }, pct_coord_to_px_coord(topLeftEdge, 1920, 1080));
        pixel_equal({ 960, 540, 1920, 1080 }, pct_coord_to_px_coord(topRightEdge, 1920, 1080));
        pixel_equal({ -959, -539, 1920, 1080 }, pct_coord_to_px_coord(bottomLeftEdge, 1920, 1080));
        pixel_equal({ 960, -539, 1920, 1080 }, pct_coord_to_px_coord(bottomRightEdge, 1920, 1080));
        pixel_equal({ 1, 1, 1920, 1080 }, pct_coord_to_px_coord(middle, 1920, 1080));
    }

    TEST_F(ConversionsTests, ConvertsFromCameraToPixelCoordinate) {
        const gu_camera_coordinate topLeftEdge = { 0, 0, 1920, 1080 };
        const gu_camera_coordinate topRightEdge = { 1919, 0, 1920, 1080 };
        const gu_camera_coordinate bottomLeftEdge = { 0, 1079, 1920, 1080 };
        const gu_camera_coordinate bottomRightEdge = { 1919, 1079, 1920, 1080 };
        const gu_pixel_coordinate ptopLeftEdge = { -959, 540, 1920, 1080 };
        const gu_pixel_coordinate ptopRightEdge = { 960, 540, 1920, 1080 };
        const gu_pixel_coordinate pbottomLeftEdge = { -959, -539, 1920, 1080 };
        const gu_pixel_coordinate pbottomRightEdge = { 960, -539, 1920, 1080 };
        const gu_pixel_coordinate otopLeftEdge = cam_coord_to_px_coord(topLeftEdge);
        const gu_pixel_coordinate otopRightEdge = cam_coord_to_px_coord(topRightEdge);
        const gu_pixel_coordinate obottomLeftEdge = cam_coord_to_px_coord(bottomLeftEdge);
        const gu_pixel_coordinate obottomRightEdge = cam_coord_to_px_coord(bottomRightEdge);
        pixel_equal(ptopLeftEdge, otopLeftEdge);
        pixel_equal(ptopRightEdge, otopRightEdge);
        pixel_equal(pbottomLeftEdge, obottomLeftEdge);
        pixel_equal(pbottomRightEdge, obottomRightEdge);
    }

    TEST_F(ConversionsTests, ConvertsFromPixelToCameraCoordinate) {
        const gu_camera_coordinate topLeftEdge = { 0, 0, 1920, 1080 };
        const gu_camera_coordinate topRightEdge = { 1919, 0, 1920, 1080 };
        const gu_camera_coordinate bottomLeftEdge = { 0, 1079, 1920, 1080 };
        const gu_camera_coordinate bottomRightEdge = { 1919, 1079, 1920, 1080 };
        const gu_pixel_coordinate ptopLeftEdge = { -959, 540, 1920, 1080 };
        const gu_pixel_coordinate ptopRightEdge = { 960, 540, 1920, 1080 };
        const gu_pixel_coordinate pbottomLeftEdge = { -959, -539, 1920, 1080 };
        const gu_pixel_coordinate pbottomRightEdge = { 960, -539, 1920, 1080 };
        const gu_camera_coordinate otopLeftEdge = px_coord_to_cam_coord(ptopLeftEdge);
        const gu_camera_coordinate otopRightEdge = px_coord_to_cam_coord(ptopRightEdge);
        const gu_camera_coordinate obottomLeftEdge = px_coord_to_cam_coord(pbottomLeftEdge);
        const gu_camera_coordinate obottomRightEdge = px_coord_to_cam_coord(pbottomRightEdge);
        camera_equal(topLeftEdge, otopLeftEdge);
        camera_equal(topRightEdge, otopRightEdge);
        camera_equal(bottomLeftEdge, obottomLeftEdge);
        camera_equal(bottomRightEdge, obottomRightEdge);
    }

}  // namespace

#pragma clang diagnostic pop
