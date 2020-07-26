/*
 * OptionalPixelCoordinate.cc 
 * gucoordinates 
 *
 * Created by Callum McColl on 27/07/2020.
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

#include "OptionalPixelCoordinate.hpp"

GU::OptionalPixelCoordinate::OptionalPixelCoordinate() {}

GU::OptionalPixelCoordinate::OptionalPixelCoordinate(const bool t_has_value, const GU::PixelCoordinate t_value)
{
    set_has_value(t_has_value);
    set_value(t_value);
}

GU::OptionalPixelCoordinate::OptionalPixelCoordinate(const GU::OptionalPixelCoordinate& other)
{
    set_has_value(other.has_value());
    set_value(other.value());
}

GU::OptionalPixelCoordinate::OptionalPixelCoordinate(const gu_optional_pixel_coordinate &other)
{
    set_has_value(other.has_value);
    set_value(other.value);
}

#if __cplusplus >= 201103L
GU::OptionalPixelCoordinate::OptionalPixelCoordinate(GU::OptionalPixelCoordinate&& other)
{
    set_has_value(other.has_value());
    other.set_has_value(0.0f);
    set_value(other.value());
    other.set_value(GU::PixelCoordinate());
}
#endif

GU::OptionalPixelCoordinate::~OptionalPixelCoordinate() {}

GU::OptionalPixelCoordinate& GU::OptionalPixelCoordinate::operator=(const GU::OptionalPixelCoordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_has_value(other.has_value());
    set_value(other.value());
    return *this;
}

GU::OptionalPixelCoordinate& GU::OptionalPixelCoordinate::operator=(const gu_optional_pixel_coordinate& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_has_value(other.has_value);
    set_value(other.value);
    return *this;
}

#if __cplusplus >= 201103L
GU::OptionalPixelCoordinate& GU::OptionalPixelCoordinate::operator=(GU::OptionalPixelCoordinate&& other)
{
    if (&other == this)
    {
        return *this;
    }
    set_has_value(other.has_value());
    other.set_has_value(false);
    set_value(other.value());
    other.set_value(GU::PixelCoordinate());
    return *this;
}
#endif

bool GU::OptionalPixelCoordinate::has_value() const
{
    return gu_optional_pixel_coordinate::has_value;
}

void GU::OptionalPixelCoordinate::set_has_value(const bool newValue)
{
    gu_optional_pixel_coordinate::has_value = newValue;
}

GU::PixelCoordinate GU::OptionalPixelCoordinate::value() const
{
    return gu_optional_pixel_coordinate::value;
}

void GU::OptionalPixelCoordinate::set_value(const GU::PixelCoordinate newValue)
{
    gu_optional_pixel_coordinate::value = newValue;
}
