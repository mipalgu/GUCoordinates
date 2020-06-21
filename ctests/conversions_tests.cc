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
#include "../gucoordinates.h"
#include <iostream>
#include <gusimplewhiteboard/typeClassDefs/wb_pixel_to_robot_relative_coord.h>

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

    TEST_F(ConversionsTests, ConvertsFromPixelToRelativeCoordinate) {
        const gu_pixel_coordinate centrePoint = { 0, 0, 1920, 1080 };
        const gu_robot robot = GU_NAO_V5_ROBOT(5.0f, 0.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(px_coord_to_rr_coord(centrePoint, robot, &coord, 0));
        ASSERT_EQ(coord.distance, 429);
        ASSERT_EQ(coord.direction, 0);
        //std::cout << coord.distance() << ", " << coord.direction() << std::endl;
    }

    TEST_F(ConversionsTests, ConvertsFromPercentToRelativeCoordinate) {
        const gu_percent_coordinate centrePoint = { 0.0f, 0.0f};
        const gu_robot robot = GU_NAO_V5_ROBOT(5.0f, 0.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(pct_coord_to_rr_coord(centrePoint, robot, &coord, 0));
        ASSERT_EQ(coord.distance, 430);
        ASSERT_EQ(coord.direction, 0);
        /*std::cout << coord.distance() << ", " << coord.direction() << std::endl;
        double distance = 0;
        double angle = 0;
        struct wb_vision_control_status vs = {};
        struct wb_sensors_torsojointsensors joints = {};
        joints.set_HeadYaw(0.0f);
        joints.set_HeadPitch(rad_f_to_f(deg_f_to_rad_f(5.0f)));
        pixel_to_rr_coord(0, 0, Top, &vs, &joints, &distance, &angle);
        std::cout << "distance: " << distance << ", angle: " << angle << std::endl;*/
    }

    TEST_F(ConversionsTests, ConvertsFromPercentToRelativeCoordinate3) {
        const gu_percent_coordinate centrePoint = {0.0f, 0.5f};
        const gu_robot robot = GU_NAO_V5_ROBOT(15.0f, 0.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(pct_coord_to_rr_coord(centrePoint, robot, &coord, 0));
        ASSERT_EQ(coord.distance, 629);
        ASSERT_EQ(coord.direction, 0);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPercent) {
        const gu_relative_coordinate coord = { 0, 430 };
        const gu_robot robot = GU_NAO_V5_ROBOT(5.0f, 0.0f);
        gu_percent_coordinate output;
        ASSERT_TRUE(rr_coord_to_pct_coord(coord, robot, 0, &output));
        ASSERT_TRUE(fabsf(output.x - 0.0f) < 0.01f);
        ASSERT_TRUE(fabsf(output.y - 0.0f) < 0.01f);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPercent2) {
        const gu_relative_coordinate coord = { 0, 153 };
        const gu_robot robot = GU_NAO_V5_ROBOT(15.0f, 0.0f);
        gu_percent_coordinate output;
        ASSERT_TRUE(rr_coord_to_pct_coord(coord, robot, 0, &output));
        ASSERT_LT(fabsf(output.x - 0.0f), 0.01f);
        ASSERT_LT(fabsf(output.y - 0.0f), 0.01f);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPercent3) {
        const gu_relative_coordinate coord = { 0, 629};
        const gu_robot robot = GU_NAO_V5_ROBOT(15.0f, 0.0f);
        gu_percent_coordinate output;
        ASSERT_TRUE(rr_coord_to_pct_coord(coord, robot, 0, &output));
        ASSERT_LT(fabsf(output.x - 0.0f), 0.01f);
        ASSERT_LT(fabsf(output.y - 0.5f), 0.01f);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPixelUsingPreviousCalculation) {
        const gu_pixel_coordinate point = { 450, -330, 1920, 1080 };
        const gu_robot robot = GU_NAO_V5_ROBOT(5.0f, 2.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(px_coord_to_rr_coord(point, robot, &coord, 0));
        gu_pixel_coordinate output;
        ASSERT_TRUE(rr_coord_to_px_coord(coord, robot, 0, &output, 1920, 1080));
        ASSERT_EQ(output.y, -330);
        ASSERT_EQ(output.x, 450);
    }

    TEST_F(ConversionsTests, ConvertsFromFieldCoordinateToRelativeCoordinate) {
        const gu_field_coordinate source = { { 1, 1 }, 45 };
        const gu_cartesian_coordinate target = { 2, 2 };
        const gu_relative_coordinate coord = field_coord_to_rr_coord_to_target(source, target);
        ASSERT_EQ(coord.direction, 0);
        ASSERT_EQ(coord.distance, 1);
        const gu_field_coordinate source2 = { {1, 1}, 90 };
        const gu_cartesian_coordinate target2 =  { 2, 2 };
        const gu_relative_coordinate result2 = field_coord_to_rr_coord_to_target(source2, target2);
        ASSERT_EQ(result2.direction, -45);
        ASSERT_EQ(result2.distance, 1);
        const gu_field_coordinate source3 = { {-1, 1}, 90};
        const gu_cartesian_coordinate target3 = { -2, 2 };
        const gu_relative_coordinate result3 = field_coord_to_rr_coord_to_target(source3, target3);
        ASSERT_EQ(result3.direction, 45);
        ASSERT_EQ(result3.distance, 1);
        const gu_field_coordinate source4 = { {-1, 1}, 180};
        const gu_cartesian_coordinate target4 = { -2, 2 };
        const gu_relative_coordinate result4 = field_coord_to_rr_coord_to_target(source4, target4);
        ASSERT_EQ(result4.direction, -45);
        ASSERT_EQ(result4.distance, 1);
        const gu_field_coordinate source5 = { {-1, -1}, 0};
        const gu_cartesian_coordinate target5 = { -2, -2 };
        const gu_relative_coordinate result5 = field_coord_to_rr_coord_to_target(source5, target5);
        ASSERT_EQ(result5.direction, -135);
        ASSERT_EQ(result5.distance, 1);
        const gu_field_coordinate source6 = { {-1, -1}, 90};
        const gu_cartesian_coordinate target6 = { -2, -2 };
        const gu_relative_coordinate result6 = field_coord_to_rr_coord_to_target(source6, target6);
        ASSERT_EQ(result6.direction, 135);
        ASSERT_EQ(result6.distance, 1);
        const gu_field_coordinate source7 = { {-1, -1}, -90};
        const gu_cartesian_coordinate target7 = { -2, -2 };
        const gu_relative_coordinate result7 = field_coord_to_rr_coord_to_target(source7, target7);
        ASSERT_EQ(result7.direction, -45);
        ASSERT_EQ(result7.distance, 1);
        const gu_field_coordinate source8 = { {-1, -1}, -120};
        const gu_cartesian_coordinate target8 = { -2, -2 };
        const gu_relative_coordinate result8 = field_coord_to_rr_coord_to_target(source8, target8);
        ASSERT_EQ(result8.direction, -15);
        ASSERT_EQ(result8.distance, 1);
        const gu_field_coordinate source9 = { {1, -2}, 180};
        const gu_cartesian_coordinate target9 = { 2, -1 };
        const gu_relative_coordinate result9 = field_coord_to_rr_coord_to_target(source9, target9);
        ASSERT_EQ(result9.direction, -135);
        ASSERT_EQ(result9.distance, 1);
        const gu_field_coordinate source10 = { {1, -2}, -60};
        const gu_cartesian_coordinate target10 = { 2, -1 };
        const gu_relative_coordinate result10 = field_coord_to_rr_coord_to_target(source10, target10);
        ASSERT_EQ(result10.direction, 105);
        ASSERT_EQ(result10.distance, 1);
        const gu_field_coordinate source11 = { {3, -7}, 0};
        const gu_cartesian_coordinate target11 = { -9, 6 };
        const gu_relative_coordinate result11 = field_coord_to_rr_coord_to_target(source11, target11);
        ASSERT_EQ(result11.direction, 133);
        ASSERT_EQ(result11.distance, 18);
        const gu_field_coordinate source12 = { {1, 1}, 0};
        const gu_cartesian_coordinate target12 = { 0, 1 };
        const gu_relative_coordinate result12 = field_coord_to_rr_coord_to_target(source12, target12);
        ASSERT_EQ(result12.direction, 180);
        ASSERT_EQ(result12.distance, 1);
    }

}  // namespace

#pragma clang diagnostic pop
