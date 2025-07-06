
#include "ADSREnvelope.h"

#include <print>
#include <utility>

void ADSREnvelope::setDurations(double attackDuration, double decayDuration,
                                double releaseDuration) {
  if (getSampleRate() == 0) {
    std::println("ADSREnvelope: Warning - sample rate is 0");
  }
  numAttackSamples = attackDuration * getSampleRate();
  numDecaySamples = decayDuration * getSampleRate();
  numReleaseSamples = releaseDuration * getSampleRate();
};

void ADSREnvelope::setGains(double attackGain, double sustainGain) {
  this->attackGain = attackGain;
  this->sustainGain = sustainGain;
}

void ADSREnvelope::trigger() {
  setStage(Stage::Attack);
  attackPhase = 0.0;
  decayPhase = 0.0;
  releasePhase = 0.0;
}

void ADSREnvelope::release() { setStage(Stage::Release); }

bool ADSREnvelope::isTriggered() { return stage != Stage::Zero; }

void ADSREnvelope::process() {
  if (stage == Stage::Attack) {
    attackPhase += 1.0;
    if (attackPhase >= numAttackSamples) {
      setStage(Stage::Decay);
    }
  } else if (stage == Stage::Decay) {
    decayPhase += 1.0;
    if (decayPhase >= numDecaySamples) {
      setStage(Stage::Sustain);
    }
  } else if (stage == Stage::Release) {
    releasePhase += 1.0;
    if (releasePhase >= numReleaseSamples) {
      setStage(Stage::Zero);
    }
  }
}

double ADSREnvelope::sample() {
  switch (stage) {
  case Stage::Zero: {
    return 0.;
  }
  case Stage::Attack: {
    return (attackPhase / numAttackSamples) * attackGain;
  }
  case Stage::Decay: {
    return attackGain * (1. - decayPhase) + sustainGain * decayPhase;
  }
  case Stage::Sustain: {
    return sustainGain;
  }
  case Stage::Release: {
    return (1.0 - (releasePhase / numReleaseSamples)) * sustainGain;
  }
  }
  std::unreachable();
}

void ADSREnvelope::setStage(Stage stage) { this->stage = stage; };
