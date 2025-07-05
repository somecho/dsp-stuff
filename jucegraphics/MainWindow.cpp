#include "MainWindow.h"

#include "MainComponent.h"

MainWindow::MainWindow(juce::String name)
    : juce::DocumentWindow(name, juce::Colours::lightgrey,
                           juce::DocumentWindow::allButtons) {
  // setUsingNativeTitleBar(true);
  setContentOwned(new MainComponent(), true);
  // setSize(800, 800);
  setVisible(true);
  centreWithSize(getWidth(), getHeight());
}

MainWindow::~MainWindow() {};

void MainWindow::closeButtonPressed() {
  juce::JUCEApplication::getInstance()->systemRequestedQuit();
}
