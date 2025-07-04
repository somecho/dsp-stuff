#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <print>

class btnListener : public juce::Button::Listener {
  void buttonClicked(juce::Button *) override {
    std::println("I've been clicked");
  };

  void buttonStateChanged(juce::Button *) override {}
};

class MainWindow : public juce::DocumentWindow {
public:
  MainWindow(juce::String name)
      : DocumentWindow(name, juce::Colours::lightgrey,
                       DocumentWindow::TitleBarButtons::closeButton) {
    centreWithSize(500, 500);
    setVisible(true);
    setUsingNativeTitleBar(true);

    btn.setBounds(0, 0, 100, 100);
    btn.setTitle("Helo World Button");
    btn.setButtonText("Hello World");
    btn.addListener(&listener);
    addAndMakeVisible(&btn);
  }

  void closeButtonPressed() override {
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
  juce::TextButton btn;
  btnListener listener;
};

class MainWindowTutorialApplication : public juce::JUCEApplication {
public:
  MainWindowTutorialApplication() {}
  ~MainWindowTutorialApplication() {}

  void initialise(const juce::String &commandLine) override {
    mainWindow.reset(new MainWindow(getApplicationName()));
  }

  void shutdown() override { mainWindow = nullptr; }

  const juce::String getApplicationName() override { return "GLFW"; }

  const juce::String getApplicationVersion() override { return "1.0"; }

private:
  std::unique_ptr<MainWindow> mainWindow;
};

juce ::JUCEApplicationBase *juce_CreateApplication() {
  return new MainWindowTutorialApplication();
}

int main(int argc, char *argv[]) {
  juce ::JUCEApplicationBase ::createInstance = &juce_CreateApplication;
  return juce ::JUCEApplicationBase ::main(argc, (const char **)argv);
}
