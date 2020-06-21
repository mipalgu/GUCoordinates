/*
 * FieldCoordinate.cc 
 * gucoordinates 
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

#include "FieldCoordinate.hpp"
#include "conversions.h"

GU::FieldCoordinate::FieldCoordinate(): gu_field_coordinate() {}

GU::FieldCoordinate::FieldCoordinate(GU::CartesianCoordinate t_position, degrees_t t_heading): gu_field_coordinate { t_position, t_heading } {} 

GU::FieldCoordinate::FieldCoordinate(const FieldCoordinate& other): gu_field_coordinate { other.position(), other.heading() } {}

GU::FieldCoordinate::FieldCoordinate(const gu_field_coordinate & other): gu_field_coordinate { other.position, other.heading } {}

#ifdef __cpp_rvalue_references
GU::FieldCoordinate::FieldCoordinate(FieldCoordinate&& other)
{
    set_position(other.position());
    set_heading(other.heading());
    other.set_position(GU::CartesianCoordinate(0, 0));
    other.set_heading(0);
}
#endif

GU::FieldCoordinate::~FieldCoordinate() {}

GU::FieldCoordinate& GU::FieldCoordinate::operator=(const FieldCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_position(other.position());
    set_heading(other.heading());
    return *this;
}

GU::FieldCoordinate& GU::FieldCoordinate::operator=(const gu_field_coordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_position(other.position);
    set_heading(other.heading);
    return *this;
}

#ifdef __cpp_rvalue_references
GU::FieldCoordinate& GU::FieldCoordinate::operator=(FieldCoordinate&& other)
{
    if (&other == this) {
        return *this;
    }
    set_position(other.position());
    set_heading(other.heading());
    other.set_position(GU::CartesianCoordinate(0, 0));
    other.set_heading(0);
    return *this;
}
#endif

GU::CartesianCoordinate GU::FieldCoordinate::position() const
{
    return gu_field_coordinate::position;
}

void GU::FieldCoordinate::set_position(const GU::CartesianCoordinate newValue)
{
    gu_field_coordinate::position = newValue;
}

degrees_t GU::FieldCoordinate::heading() const
{
    return gu_field_coordinate::heading;
}

void GU::FieldCoordinate::set_heading(const degrees_t newValue)
{
    gu_field_coordinate::heading = newValue;
}

bool GU::FieldCoordinate::operator==(const FieldCoordinate &other) const
{
    return gu_field_coordinate_equals(*this, other);
}

bool GU::FieldCoordinate::operator!=(const FieldCoordinate &other) const
{
    return !(*this == other);
}

bool GU::FieldCoordinate::operator==(const gu_field_coordinate &other) const
{
    return gu_field_coordinate_equals(*this, other);
}

bool GU::FieldCoordinate::operator!=(const gu_field_coordinate &other) const
{
    return !(*this == other);
}
