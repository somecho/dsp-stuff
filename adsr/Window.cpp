#include "Window.h"
#include "MainContentComponent.h"

Window::Window(juce::String name)
    : juce::DocumentWindow(name, juce::Colours::lightgrey,
                           juce::DocumentWindow::allButtons) {
  setContentOwned(new MainContentComponent(), true);
  centreWithSize(getWidth(), getHeight());
  setVisible(true);
}

Window::~Window() {}

void Window::closeButtonPressed() {
  juce::JUCEApplication::getInstance()->systemRequestedQuit();
}
