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

#include "gucoordinates_tests.hpp"

namespace CGTEST {
    
    class ConversionsTests: public GUCoordinatesTests {};

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
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(5.0f, 0.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(px_coord_to_rr_coord(centrePoint, camera_pivot, &coord, 0));
        ASSERT_EQ(coord.distance, 430);
        ASSERT_EQ(coord.direction, 0);
        //std::cout << coord.distance() << ", " << coord.direction() << std::endl;
    }

    TEST_F(ConversionsTests, ConvertsFromPercentToRelativeCoordinate) {
        const gu_percent_coordinate centrePoint = { 0.0f, 0.0f};
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(5.0f, 0.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(pct_coord_to_rr_coord(centrePoint, camera_pivot, &coord, 0));
        ASSERT_EQ(coord.distance, 432);
        ASSERT_EQ(coord.direction, 0);
    }

    TEST_F(ConversionsTests, ConvertsFromPercentToRelativeCoordinate3) {
        const gu_percent_coordinate centrePoint = {0.0f, 0.5f};
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(15.0f, 0.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(pct_coord_to_rr_coord(centrePoint, camera_pivot, &coord, 0));
        ASSERT_EQ(coord.distance, 612);
        ASSERT_EQ(coord.direction, 0);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPercent) {
        const gu_relative_coordinate coord = { 0, 430 };
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(5.0f, 0.0f);
        gu_percent_coordinate output;
        ASSERT_TRUE(rr_coord_to_pct_coord(coord, camera_pivot, 0, &output));
        ASSERT_TRUE(fabsf(output.x - 0.0f) < 0.01f);
        ASSERT_TRUE(fabsf(output.y - 0.0f) < 0.01f);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPercent2) {
        const gu_relative_coordinate coord = { 0, 153 };
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(15.0f, 0.0f);
        gu_percent_coordinate output;
        ASSERT_TRUE(rr_coord_to_pct_coord(coord, camera_pivot, 0, &output));
        ASSERT_LT(fabsf(output.x - 0.0f), 0.01f);
        ASSERT_LT(fabsf(output.y - 0.0f), 0.01f);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPercent3) {
        const gu_relative_coordinate coord = { 0, 629};
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(15.0f, 0.0f);
        gu_percent_coordinate output;
        ASSERT_TRUE(rr_coord_to_pct_coord(coord, camera_pivot, 0, &output));
        ASSERT_LT(fabsf(output.x - 0.0f), 0.01f);
        ASSERT_LT(fabsf(output.y - 0.5f), 0.01f);
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToPixelUsingPreviousCalculation) {
        const pixels_t x = 450;
        const pixels_t y = -330;
        const pixels_u res_width = 1920;
        const pixels_u res_height = 1080;
        const gu_pixel_coordinate point = { x, y, res_width, res_height };
        const gu_camera_pivot camera_pivot = GU_NAO_V5_HEAD(5.0f, 45.0f);
        gu_relative_coordinate coord;
        ASSERT_TRUE(px_coord_to_rr_coord(point, camera_pivot, &coord, 0));
        gu_pixel_coordinate output;
        ASSERT_TRUE(rr_coord_to_px_coord(coord, camera_pivot, 0, &output, res_width, res_height));
        ASSERT_LE(abs(output.x - x), px_u_to_px_t(res_width) / 200); // Within 0.5 percent.
        ASSERT_LE(abs(output.y - y), px_u_to_px_t(res_height) / 200); // Within 0.5 percent.
    }

    TEST_F(ConversionsTests, ConvertsFromRelativeCoordinateToFieldCoordinate) {
        const gu_relative_coordinate coord = { .direction = 0, .distance = 1 };
        const gu_field_coordinate target = rr_coord_to_field_coord(coord, 40);
        ASSERT_EQ(target.position.x, 1);
        ASSERT_EQ(target.position.y, 0);
        ASSERT_EQ(target.heading, 40);
        const gu_relative_coordinate coord2 = { .direction = -45, .distance = 2 };
        const gu_field_coordinate target2 = rr_coord_to_field_coord(coord2, 40);
        ASSERT_EQ(target2.position.x, 1);
        ASSERT_EQ(target2.position.y, -1);
        ASSERT_EQ(target2.heading, 40);
        const gu_relative_coordinate coord3 = { .direction = -60, .distance = 6 };
        const gu_field_coordinate target3 = rr_coord_to_field_coord(coord3, 12);
        ASSERT_EQ(target3.position.x, 3);
        ASSERT_EQ(target3.position.y, -5);
        ASSERT_EQ(target3.heading, 12);
    }

    TEST_F(ConversionsTests, ConvertsToRelativeCoordinateFromFieldSource) {
        const gu_field_coordinate source = { { 1, 1 }, 45 };
        const gu_relative_coordinate target = { .direction = 45, .distance = 5};
        const gu_field_coordinate coord = rr_coord_to_field_coord_from_source(target, source, 23);
        ASSERT_EQ(coord.position.x, 1);
        ASSERT_EQ(coord.position.y, 6);
        ASSERT_EQ(coord.heading, 23);
        const gu_relative_coordinate target2 = { .direction = -45, .distance = 5 };
        const gu_field_coordinate coord2 = rr_coord_to_field_coord_from_source(target2, source, 26);
        ASSERT_EQ(coord2.position.x, 6);
        ASSERT_EQ(coord2.position.y, 1);
        ASSERT_EQ(coord2.heading, 26);
        const gu_relative_coordinate target3 = { .direction = 105, .distance = 6 };
        const gu_field_coordinate coord3 = rr_coord_to_field_coord_from_source(target3, source, -18);
        ASSERT_EQ(coord3.position.x, -4);
        ASSERT_EQ(coord3.position.y, 4);
        ASSERT_EQ(coord3.heading, -18);
        const gu_relative_coordinate target4 = { .direction = -135, .distance = 10 };
        const gu_field_coordinate coord4 = rr_coord_to_field_coord_from_source(target4, source, 80);
        ASSERT_EQ(coord4.position.x, 1);
        ASSERT_EQ(coord4.position.y, -9);
        ASSERT_EQ(coord4.heading, 80);
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

    TEST_F(ConversionsTests, ConvertsFromRelativeToCartesianFromSource)
    {
        const gu_cartesian_coordinate source = {-90, 120};
        const gu_relative_coordinate coord1 = {2, 26};
        const gu_cartesian_coordinate result1 = rr_coord_to_cartesian_coord_from_source(coord1, source);
        ASSERT_EQ(result1.x, -64);
        ASSERT_EQ(result1.y, 121);

        const gu_relative_coordinate coord2 = {5, 342};
        const gu_cartesian_coordinate result2 = rr_coord_to_cartesian_coord_from_source(coord2, source);
        ASSERT_EQ(result2.x, 251);
        ASSERT_EQ(result2.y, 150);
    }

    TEST_F(ConversionsTests, ConvertesFromCartesianToRelativeFromSource)
    {
        const gu_cartesian_coordinate source = {-90, 120};
        const gu_cartesian_coordinate coord1 = {-64, 121};
        const gu_relative_coordinate result1 = cartesian_coord_to_rr_coord_from_source(source, coord1);
        ASSERT_EQ(result1.direction, 2);
        ASSERT_EQ(result1.distance, 26);

        const gu_cartesian_coordinate coord2 = {251, 150};
        const gu_relative_coordinate result2 = cartesian_coord_to_rr_coord_from_source(source, coord2);
        ASSERT_EQ(result2.direction, 5);
        ASSERT_EQ(result2.distance, 342);
    }

}  // namespace
