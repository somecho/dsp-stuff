#include "MainComponent.h"

MainComponent::MainComponent() {
  addAndMakeVisible(btn);
  btn.setButtonText("HELLO");
  // btn.setBounds(50, 50, 150, 150);

  setSize(800, 800);

  // btn.setSize(150, 150);

  // setVisible(true);
  // btn.addListener(this);
}

MainComponent::~MainComponent() {
  // btn.removeListener(this);
}

// void MainComponent::buttonClicked(juce::Button *button) {
//   std::println("HELLO");
// }

void MainComponent::paint(juce::Graphics &g) {
  g.fillAll(juce::Colours::lightsalmon);
  g.setColour(juce::Colours::black);
  g.setFont(20.0f);
  g.drawText("Main Component", 20, 20, 200, 200, juce::Justification::centred,
             true);

  // g.drawLine(getHeight() / 2, getWidth() * 0.1f, getHeight() / 2,
  //            getWidth() * 0.9, 2.0);

  juce::Rectangle<float> area(100, 100, 300, 500);

  g.setColour(juce::Colours::sandybrown);
  g.fillCheckerBoard(area, 30, 30, juce::Colours::white,
                     juce::Colours::burlywood);
}

void MainComponent::resized() {
  btn.setBounds(50, 50, 150, 150);
  // setBounds(getLocalBounds());
  // btn.setBounds(50, 50, 150, 150);
}
