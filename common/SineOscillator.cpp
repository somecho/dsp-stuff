#include "SineOscillator.h"

#include <cmath>
#include <numbers>

void SineOscillator::process() {
  phase += std::numbers::pi_v<double> * 2 * getFrequency() / getSampleRate();
  if (phase > std::numbers::pi_v<double> * 2.f) {
    phase -= std::numbers::pi_v<double> * 2.f;
  }
}

double SineOscillator::sample() { return sin(phase); }
