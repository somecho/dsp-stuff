#include "MainContentComponent.h"

MainContentComponent::MainContentComponent() {
  addAndMakeVisible(drumpad);
  drumpad.setBounds(8, 8, 48, 48);
  drumpad.onStateChange = [this] {
    if (drumpad.isDown()) {
      sinOsc.setGain(0.2);
    } else if (!drumpad.isDown()) {
      sinOsc.setGain(0.0);
    }
  };
  setSize(600, 400);
  setAudioChannels(0, 2);
}

MainContentComponent::~MainContentComponent() {}

void MainContentComponent::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::lightgrey);
}
void MainContentComponent::resized() {}

void MainContentComponent::prepareToPlay(int samplesPerBlockExpected,
                                         double sampleRate) {
  sinOsc.setFrequency(440.);
  sinOsc.setGain(0.);
  sinOsc.setSampleRate(sampleRate);
}

void MainContentComponent::getNextAudioBlock(
    const juce::AudioSourceChannelInfo &bufferToFill) {
  auto *left =
      bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
  auto *right =
      bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);

  for (auto sample = 0; sample < bufferToFill.numSamples; sample++) {
    auto sampleValue = static_cast<float>(sinOsc.sample());
    left[sample] = sampleValue;
    right[sample] = sampleValue;
    sinOsc.process();
  }
}

void MainContentComponent::releaseResources() {}
