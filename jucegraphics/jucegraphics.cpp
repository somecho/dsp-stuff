
#include "juce_events/juce_events.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <juce_core/juce_core.h>

#include "MainWindow.h"

class App : public juce::JUCEApplication {
public:
  App() {};
  ~App() {};

  void initialise([[maybe_unused]] const juce::String &commandline) override {
    window.reset(new MainWindow(getApplicationName()));
  }

  void shutdown() override { window = nullptr; }

  const juce::String getApplicationName() override { return "GLFW"; };

  const juce::String getApplicationVersion() override { return "0"; };

private:
  std::unique_ptr<MainWindow> window;
};

START_JUCE_APPLICATION(App)
