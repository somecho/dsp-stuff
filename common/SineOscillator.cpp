#include "SineOscillator.h"

#include <cmath>
#include <numbers>

SineOscillator::SineOscillator(double frequency, double sampleRate)
    : frequency(frequency), sampleRate(sampleRate) {};

void SineOscillator::setFrequency(double frequency) {
  this->frequency = frequency;
}

void SineOscillator::setGain(double gain) { this->gain = gain; }

void SineOscillator::setSampleRate(double sampleRate) {
  this->sampleRate = sampleRate;
}

void SineOscillator::process() {
  phase += std::numbers::pi_v<double> * 2 * frequency / sampleRate;
  if (phase > std::numbers::pi_v<double> * 2.f) {
    phase -= std::numbers::pi_v<double> * 2.f;
  }
}

double SineOscillator::sample() { return sin(phase) * gain; }
