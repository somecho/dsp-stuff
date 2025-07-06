#pragma once

#include <ostream>

#include "Signal.h"

class ADSREnvelope : public Signal {
public:
  void setDurations(double attackDuration, double decayDuration,
                    double releaseDuration);
  void setGains(double attackGain, double releaseGain);

  /**
   * Sets phase to 0 and starts the attack stage;
   * */
  void trigger();
  void release();
  bool isTriggered();

  void process() override;
  double sample() override;

  enum Stage { Attack, Decay, Sustain, Release, Zero };

private:
  double numAttackSamples;
  double numDecaySamples;
  double numReleaseSamples;

  double attackPhase = 0.0;
  double decayPhase = 0.0;
  double releasePhase = 0.0;

  double attackGain;
  double sustainGain;

  double valueOnRelease = 0.0;

  Stage stage = Stage::Zero;

  void setStage(Stage stage);
};
