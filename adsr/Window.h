#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Window : public juce::DocumentWindow {
public:
  Window(juce::String name);
  ~Window();

  void closeButtonPressed();

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Window)
};
