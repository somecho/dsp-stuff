#include "MainContentComponent.h"

MainContentComponent::MainContentComponent() {
  addAndMakeVisible(drumpad);
  drumpad.setBounds(8, 8, 48, 48);
  drumpad.onStateChange = [this] {
    if (drumpad.isDown()) {
      adsr.trigger();
    } else if (!drumpad.isDown() && adsr.isTriggered()) {
      adsr.release();
    }
  };

  addAndMakeVisible(slider);
  slider.setBounds(drumpad.getBounds().getRight(), 8, 180, 180);
  slider.setRange(0.01, 2.0, 0.01);
  slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);

  slider.onValueChange = [this] {
    adsr.setDurations(slider.getValue(), 0.01, 1.0);
  };

  setSize(600, 400);
  setAudioChannels(0, 2);
}

MainContentComponent::~MainContentComponent() { shutdownAudio(); }

void MainContentComponent::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::lightgrey);
}
void MainContentComponent::resized() {}

void MainContentComponent::prepareToPlay(int samplesPerBlockExpected,
                                         double sampleRate) {
  sinOsc.setFrequency(440.);
  sinOsc.setGain(0.2);
  sinOsc.setSampleRate(sampleRate);

  adsr.setSampleRate(sampleRate);
  adsr.setDurations(0.01, 0.01, 1.0);
  adsr.setGains(0.3, 0.3);

  slider.setValue(0.01)
}

void MainContentComponent::getNextAudioBlock(
    const juce::AudioSourceChannelInfo &bufferToFill) {
  auto *left =
      bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  auto *right =
      bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

  for (auto sample = 0; sample < bufferToFill.numSamples; sample++) {
    auto sampleValue = static_cast<float>(sinOsc.sample() * adsr.sample());
    left[sample] = sampleValue;
    right[sample] = sampleValue;
    sinOsc.process();
    adsr.process();
  }
}

void MainContentComponent::releaseResources() {}
