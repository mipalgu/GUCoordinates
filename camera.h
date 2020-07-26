/*
 * camera.h 
 * gunavigation 
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

#ifndef CAMERA_H
#define CAMERA_H

#include <guunits/guunits.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct gu_camera
{
    /**
     * The height from the pivot of the camera to the middle of the camera.
     *
     * If there is no pivot then this is the height to the ground. If it is
     * a camera on a stick then it's the length of the stick. If it's a camera
     * on the head of the robot then its the length from the neck to the
     * camera.
     */
    centimetres_f height;

    /**
     * The distance the camera is from the center point. A positive value
     * indicates that the camera is in front of the center point while a
     * negative value indicates that the camera is behind the center
     * point.
     *
     * This property is useful for when the robot is mounted on a robot
     * and distance calculations need to be calculated from the torso,
     * not the camera.
     */
    centimetres_f centerOffset;

    /**
     * The degree in which the camera is facing in the vertical direction.
     *
     * A positive value means that the camera is pointing more to the ground. A
     * negative value means that the camera is pointing more to the sky.
     */
    degrees_f vDirection;

    /**
     * The vertical field of view.
     */
    degrees_f vFov;

    /**
     * The horizontal field of view.
     */
    degrees_f hFov;

} gu_camera;

bool gu_camera_equals(const gu_camera, const gu_camera, const float) __attribute__((const));

gu_camera gu_camera_make(const centimetres_f, const centimetres_f, const degrees_f, const degrees_f, const degrees_f) __attribute__((const));


#ifdef __cplusplus
}
#endif

#endif  /* CAMERA_H */
