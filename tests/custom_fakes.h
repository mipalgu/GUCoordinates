/*
 * custom_fakes.h 
 * tests 
 *
 * Created by Callum McColl on 22/06/2020.
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

#ifndef CUSTOM_FAKES_H
#define CUSTOM_FAKES_H

#include "../gucoordinates.h"

#ifdef __cplusplus
extern "C" {
#endif

#define px_coord_to_rr_coord_custom_fake_result { .direction = 20, .distance = 200 }

bool px_coord_to_rr_coord_custom_fake_true(const gu_pixel_coordinate, const gu_robot, gu_relative_coordinate *, const int);

bool px_coord_to_rr_coord_custom_fake_false(const gu_pixel_coordinate, const gu_robot, gu_relative_coordinate *, const int);


#define pct_coord_to_rr_coord_custom_fake_result { .direction = 10, .distance = 100 }

bool pct_coord_to_rr_coord_custom_fake_true(const gu_percent_coordinate, const gu_robot, gu_relative_coordinate * out, const int);

bool pct_coord_to_rr_coord_custom_fake_false(const gu_percent_coordinate, const gu_robot, gu_relative_coordinate *, const int);

#define rr_coord_to_pct_coord_custom_fake_result { .x = -0.4f, .y = -0.2f }

bool rr_coord_to_pct_coord_custom_fake_true(const gu_relative_coordinate, const gu_robot, const int, gu_percent_coordinate *);

bool rr_coord_to_pct_coord_custom_fake_false(const gu_relative_coordinate, const gu_robot, const int, gu_percent_coordinate *);

#define rr_coord_to_px_coord_custom_fake_result { .x = -5, .y = 10, .res_width = 1920, .res_height = 1080 }

bool rr_coord_to_px_coord_custom_fake_true(const gu_relative_coordinate, const gu_robot, const int, gu_pixel_coordinate *, pixels_u, pixels_u);

bool rr_coord_to_px_coord_custom_fake_false(const gu_relative_coordinate, const gu_robot, const int, gu_pixel_coordinate *, pixels_u, pixels_u);

#ifdef __cplusplus
}
#endif

#endif  /* CUSTOM_FAKES_H */