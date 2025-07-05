#pragma once

#include "juce_gui_basics/juce_gui_basics.h"
#include <print>

class MainComponent : public juce::Component
/* , juce::Button::Listener */
{
public:
  MainComponent();
  ~MainComponent();
  void paint(juce::Graphics &g) override;
  void resized() override;

  /* void buttonClicked(juce::Button *button) override; */

private:
  juce::TextButton btn;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
