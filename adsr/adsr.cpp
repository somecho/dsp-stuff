#include "Window.h"
#include <juce_gui_basics/juce_gui_basics.h>

class App : public juce::JUCEApplication {
public:
  App() {};
  ~App() {};

  void initialise([[maybe_unused]] const juce::String &commandline) override {
    window.reset(new Window(getApplicationName()));
  }

  void shutdown() override { window = nullptr; }

  const juce::String getApplicationName() override { return "GLFW"; };
  const juce::String getApplicationVersion() override { return "0"; };

private:
  std::unique_ptr<Window> window;
};

START_JUCE_APPLICATION(App)
