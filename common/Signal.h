#pragma once

class Signal {
public:
  Signal() = default;
  ~Signal() = default;

  void setFrequency(double frequency);
  void setGain(double gain);
  void setSampleRate(double sampleRate);

  double getFrequency();
  double getGain();
  double getSampleRate();

  virtual void process() = 0;
  virtual double sample() = 0;

  double phase;

private:
  double frequency;
  double gain;
  double sampleRate;
};
