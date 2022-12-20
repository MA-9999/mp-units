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

#include "kalman.h"
#include <units/format.h>
#include <units/isq/space_and_time.h>
#include <units/si/unit_symbols.h>
#include <array>
#include <iostream>

// Based on: https://www.kalmanfilter.net/alphabeta.html#ex3

template<class T>
  requires units::is_scalar<T>
inline constexpr bool units::is_vector<T> = true;

using namespace units;

void print_header(const kalman::State auto& initial)
{
  std::cout << STD_FMT::format("Initial: {}\n", initial);
  std::cout << STD_FMT::format("{:>2} | {:>8} | {:>24} | {:>24}\n", "N", "Measured", "Curr. Estimate", "Next Estimate");
}

void print(auto iteration, Quantity auto measured, const kalman::State auto& current, const kalman::State auto& next)
{
  std::cout << STD_FMT::format("{:2} | {:8} | {:>24.1} | {:>24.1}\n", iteration, measured, current, next);
}

int main()
{
  using namespace units::si::unit_symbols;
  using state = kalman::state<quantity<isq::position_vector[m]>, quantity<isq::velocity[m / s]>>;

  const auto interval = 5 * isq::period_duration[s];
  const state initial = {30 * isq::position_vector[km], 50 * isq::velocity[m / s]};
  const std::array measurements = {30160 * isq::position_vector[m], 30365 * isq::position_vector[m],
                                   30890 * isq::position_vector[m], 31050 * isq::position_vector[m],
                                   31785 * isq::position_vector[m], 32215 * isq::position_vector[m],
                                   33130 * isq::position_vector[m], 34510 * isq::position_vector[m],
                                   36010 * isq::position_vector[m], 37265 * isq::position_vector[m]};
  std::array gain = {quantity{0.2}, quantity{0.1}};

  print_header(initial);
  state next = state_extrapolation(initial, interval);
  for (int index = 1; const auto& measured : measurements) {
    const auto& previous = next;
    const auto current = state_update(previous, measured, gain, interval);
    next = state_extrapolation(current, interval);
    print(index++, measured, current, next);
  }
}
