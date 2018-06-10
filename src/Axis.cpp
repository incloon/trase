/*
Copyright (c) 2018, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of the Oxford RSE C++ Template project.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Figure.hpp"
#include <limits>

namespace trase {

Axis::Axis(const std::array<float, 4> &area)
    : Drawable(area), m_limits{{std::numeric_limits<float>::max(),
                                std::numeric_limits<float>::max(),
                                std::numeric_limits<float>::min(),
                                std::numeric_limits<float>::min()}} {}

void Axis::add_limits(const std::array<float, 4> limits) {
  const float buffer = 0.05;
  const float xbuffer = buffer * (limits[2] - limits[0]);
  const float ybuffer = buffer * (limits[3] - limits[1]);
  const std::array<float, 4> new_limits = {
      {limits[0] - xbuffer, limits[1] - ybuffer, limits[2] + xbuffer,
       limits[3] + xbuffer}};
  // loop over dimensions
  for (int i = 0; i < 2; ++i) {
    // if min limit less then update
    if (new_limits[i] < m_limits[i]) {
      m_limits[i] = new_limits[i];
    }
    // if max limit greater then update
    if (new_limits[2 + i] > m_limits[2 + i]) {
      m_limits[2 + i] = new_limits[2 + i];
    }
  }
}

void Axis::translate_limits(const std::array<float, 2> &delta) {
  m_limits[0] += delta[0];
  m_limits[2] += delta[0];
  m_limits[1] += delta[1];
  m_limits[3] += delta[1];
}

std::shared_ptr<Plot1D> Axis::plot_impl(std::vector<float> &&x,
                                        std::vector<float> &&y) {
  m_plot1d.emplace_back(new Plot1D(*this));
  m_children.push_back(&*m_plot1d.back());
  m_plot1d.back()->set_values(std::move(x), std::move(y));
  m_plot1d.back()->set_color(default_colors[m_plot1d.size() - 1]);
  return m_plot1d.back();
}

} // namespace trase
