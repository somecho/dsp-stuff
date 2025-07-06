#pragma once

#include "Signal.h"

class SineOscillator : public Signal {
public:
  void process() override;
  double sample() override;
};
