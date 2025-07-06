#pragma once

#include <SineOscillator.h>
#include <juce_audio_utils/juce_audio_utils.h>

class MainContentComponent : public juce::AudioAppComponent {
public:
  MainContentComponent();
  ~MainContentComponent();

  void paint(juce::Graphics &g) override;
  void resized() override;

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

  void
  getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

  void releaseResources() override;

private:
  juce::TextButton drumpad;
  SineOscillator sinOsc;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContentComponent)
};
