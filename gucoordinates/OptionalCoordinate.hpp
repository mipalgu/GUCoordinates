/*
 * OptionalCoordinate.hpp 
 * gucoordinates 
 *
 * Created by Callum McColl on 21/02/2021.
 * Copyright © 2021 Callum McColl. All rights reserved.
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

#ifndef GUCOORDINATES_OPTIONALCOORDINATE_HPP
#define GUCOORDINATES_OPTIONALCOORDINATE_HPP

#if __cplusplus >= 201703L
#include <optional>
#endif

namespace GU {

    template <class Raw, class Wrapped>
    struct OptionalCoordinate: public Raw {

        OptionalCoordinate() NOEXCEPT {}

        OptionalCoordinate(const Wrapped t_value) NOEXCEPT
        {
            set_has_value(true);
            set_value(t_value);
        }

        OptionalCoordinate(const bool t_has_value, const Wrapped t_value) NOEXCEPT
        {
            set_has_value(t_has_value);
            set_value(t_value);
        }

        OptionalCoordinate(const OptionalCoordinate<Raw, Wrapped>& other) NOEXCEPT
        {
            set_has_value(other.has_value());
            set_value(other.value());
        }

        OptionalCoordinate(const Raw& other) NOEXCEPT
        {
            set_has_value(other.has_value);
            set_value(other.value);
        }

#if __cplusplus >= 201703L
        OptionalCoordinate(const std::optional<Wrapped>& other) NOEXCEPT
        {
            set_has_value(other.has_value());
            if (!other.has_value())
            {
                set_value(Wrapped());
                return;
            }
            set_value(other.value());
        }
#endif

#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        OptionalCoordinate(OptionalCoordinate<Raw, Wrapped>&& other) NOEXCEPT
        {
            set_has_value(other.has_value());
            other.set_has_value(0.0f);
            set_value(other.value());
            other.set_value(Wrapped());
        }
#pragma clang diagnostic pop
#endif

        ~OptionalCoordinate() NOEXCEPT {}

        OptionalCoordinate<Raw, Wrapped>& operator=(const OptionalCoordinate<Raw, Wrapped>& other) NOEXCEPT
        {
            if (&other == this)
            {
                return *this;
            }
            set_has_value(other.has_value());
            set_value(other.value());
            return *this;
        }

        OptionalCoordinate<Raw, Wrapped>& operator=(const Raw& other) NOEXCEPT
        {
            if (&other == this)
            {
                return *this;
            }
            set_has_value(other.has_value);
            set_value(other.value);
            return *this;
        }

#if __cplusplus >= 201703L
        OptionalCoordinate<Raw, Wrapped>& operator=(const std::optional<Wrapped>& other) NOEXCEPT
        {
            set_has_value(other.has_value());
            if (!other.has_value())
            {
                set_value(Wrapped());
                return *this;
            }
            set_value(other.value());
            return *this;
        }
#endif

#if __cplusplus >= 201103L
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
        OptionalCoordinate<Raw, Wrapped>& operator=(OptionalCoordinate<Raw, Wrapped>&& other) NOEXCEPT
        {
            if (&other == this)
            {
                return *this;
            }
            set_has_value(other.has_value());
            other.set_has_value(false);
            set_value(other.value());
            other.set_value(Wrapped());
            return *this;
        }
#pragma clang diagnostic pop
#endif

        bool has_value() const NOEXCEPT
        {
            return Raw::has_value;
        }

        void set_has_value(const bool newValue) NOEXCEPT
        {
            Raw::has_value = newValue;
        }
        
        Wrapped value() const NOEXCEPT
        {
            return Raw::value;
        }

        void set_value(const Wrapped newValue) NOEXCEPT
        {
            Raw::value = newValue;
        }
        
#if __cplusplus >= 201703L
        std::optional<Wrapped> asOptional() const NOEXCEPT
        {
            if (has_value())
                return std::optional<Wrapped>(value());
            return std::nullopt;
        }
#endif

    };

}

#endif  /* GUCOORDINATES_OPTIONALCOORDINATE_HPP */
