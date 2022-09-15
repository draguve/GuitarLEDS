/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,public juce::Timer
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    class OSCThread : public juce::Thread,public juce::Timer {
    public:
        OSCThread(NewProjectAudioProcessor& p);
        void showConnectionErrorMessage(const juce::String& messageText);
        void run() override;
        void timerCallback() override;
        NewProjectAudioProcessor& audioProcessor;
    };

    NewProjectAudioProcessor& audioProcessor;
    OSCThread oscThread;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)

};