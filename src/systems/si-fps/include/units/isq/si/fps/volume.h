// The MIT License (MIT)
//
// Copyright (c) 2018 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// IWYU pragma: begin_exports
#include <units/isq/dimensions/volume.h>
#include <units/quantity.h>
#include <units/reference.h>
#include <units/symbol_text.h>
// IWYU pragma: end_exports

#include <units/isq/si/fps/length.h>
#include <units/unit.h>

namespace units::isq::si::fps {

struct cubic_foot : unit<cubic_foot> {};
struct dim_volume : isq::dim_volume<dim_volume, cubic_foot, dim_length> {};

struct cubic_yard : deduced_unit<cubic_yard, dim_volume, yard> {};

template<UnitOf<dim_volume> U, Representation Rep = double>
using volume = quantity<dim_volume, U, Rep>;

#ifdef UNITS_LITERALS

inline namespace literals {

// ft3
constexpr auto operator"" _q_ft3(unsigned long long l) { gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); return volume<cubic_foot, std::int64_t>(static_cast<std::int64_t>(l)); }
constexpr auto operator"" _q_ft3(long double l) { return volume<cubic_foot, long double>(l); }

// yd3
constexpr auto operator"" _q_yd3(unsigned long long l) { gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); return volume<cubic_yard, std::int64_t>(static_cast<std::int64_t>(l)); }
constexpr auto operator"" _q_yd3(long double l) { return volume<cubic_yard, long double>(l); }

}  // namespace literals

#endif // UNITS_LITERALS

namespace references {

inline constexpr auto ft3 = reference<dim_volume, cubic_foot>{};
inline constexpr auto yd3 = reference<dim_volume, cubic_yard>{};

}  // namespace references

}  // namespace units::isq::si::fps
