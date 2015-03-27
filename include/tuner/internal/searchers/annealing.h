
// =================================================================================================
// This file is part of the CLTune project, which loosely follows the Google C++ styleguide and uses
// a tab-size of two spaces and a max-width of 100 characters per line.
//
// Author: cedric.nugteren@surfsara.nl (Cedric Nugteren)
//
// This file implements the simulated annealing algorithm. (...)
//
// -------------------------------------------------------------------------------------------------
//
// Copyright 2014 SURFsara
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//  http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// =================================================================================================

#ifndef CLBLAS_TUNER_SEARCHERS_ANNEALING_H_
#define CLBLAS_TUNER_SEARCHERS_ANNEALING_H_

#include <vector>
#include <random>

#include "tuner/internal/searcher.h"

namespace cltune {
// =================================================================================================

// See comment at top of file for a description of the class
class Annealing: public Searcher {
 public:

  // Maximum number of successive visits to already visited states. If this number is exceeded, the
  // algorithm ends
  static constexpr auto kMaxAlreadyVisitedStates = 10;

  // Takes additionally a fraction of configurations to consider
  Annealing(const Configurations &configurations,
            const float fraction, const double max_temperature);

  // Retrieves the next configuration to test
  virtual KernelInfo::Configuration GetConfiguration() override;

  // Calculates the next index
  virtual void CalculateNextIndex() override;

  // Retrieves the total number of configurations to try
  virtual size_t NumConfigurations() override;

 private:

  // Retrieves a vector with all neighbours of a reference configuration
  std::vector<size_t> GetNeighboursOf(const size_t reference_id) const;

  // Computes the acceptance probability P of simulated annealing based on the 'energy' of the
  // current and neighbouring state, and the 'temperature'.
  double AcceptanceProbability(const double current_energy,
                               const double neighbour_energy,
                               const double temperature) const;

  // Configuration parameters
  float fraction_;
  double max_temperature_;

  // Annealing-specific member variables
  size_t num_visited_states_;
  size_t current_state_;
  size_t neighbour_state_;
  size_t num_already_visisted_states_;

  // Random number generation
  std::default_random_engine generator_;
  std::random_device rd_;
  std::uniform_int_distribution<int> int_distribution_;
  std::uniform_real_distribution<double> probability_distribution_;
};

// =================================================================================================
} // namespace cltune

// CLBLAS_TUNER_SEARCHERS_ANNEALING_H_
#endif
