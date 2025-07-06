#include "Signal.h"

void Signal::setFrequency(double frequency) { this->frequency = frequency; }

void Signal::setGain(double gain) { this->gain = gain; }

void Signal::setSampleRate(double sampleRate) { this->sampleRate = sampleRate; }

double Signal::getFrequency() { return frequency; }

double Signal::getGain() { return gain; }

double Signal::getSampleRate() { return sampleRate; }
