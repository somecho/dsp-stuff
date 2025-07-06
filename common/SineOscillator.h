#pragma once

class SineOscillator {
public:
  SineOscillator() = default;
  SineOscillator(double frequency, double sampleRate);

  void setFrequency(double frequency);
  void setGain(double gain);
  void setSampleRate(double sampleRate);

  void process();
  double sample();

private:
  double frequency = 440.f;
  double phase = 0.f;
  double gain = 0.2;
  double sampleRate;
};
