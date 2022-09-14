/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::OSCSender sender;

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    startTimerHz(10);
    if (!sender.connect("127.0.0.1", 9001))   // [4]
        showConnectionErrorMessage("Error: could not connect to UDP port 9001.");
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

void NewProjectAudioProcessorEditor::timerCallback(){
    repaint();
    if (!sender.send("/juce/rootnote", (float)audioProcessor.getRootNote()))
        showConnectionErrorMessage("Error: could not send OSC message.");
}

void NewProjectAudioProcessorEditor::showConnectionErrorMessage(const juce::String& messageText) {
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint(juce::Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);

    int sampleRate = processor.getSampleRate();
    int blockSize = processor.getBlockSize();
    char test[100];
    sprintf(test, "Hello World! %d %d %d %lf",sampleRate,blockSize,audioProcessor.getRootNote(),audioProcessor.getChroma());

    g.drawFittedText(test, getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}