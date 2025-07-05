#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

#include "MainComponent.h"

class MainWindow : public juce::DocumentWindow {
public:
  MainWindow(juce::String name);
  ~MainWindow();

  void closeButtonPressed() override;

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
