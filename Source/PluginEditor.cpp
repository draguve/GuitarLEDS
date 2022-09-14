/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "juce_serialport/juce_serialport.h"

SerialPortConfig config = SerialPortConfig(115200, 8, SerialPortConfig::SERIALPORT_PARITY_NONE, SerialPortConfig::STOPBITS_1, SerialPortConfig::FLOWCONTROL_NONE);


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    juce::StringPairArray portlist = SerialPort::getSerialPortPaths();
	if(portlist.size())
	{
		//open the first port on the system
		SerialPort * pSP = new SerialPort(portlist.getAllValues()[0],config,(DebugFunction)CustomDebugFunction);
		if(pSP->exists())
		{
			//create streams for reading/writing
			SerialPortOutputStream * pOutputStream = new SerialPortOutputStream(pSP);
			SerialPortInputStream * pInputStream = new SerialPortInputStream(pSP);

			pOutputStream->write("on", 22); //write some bytes

		}
	}
    startTimerHz(10);
}

void CustomDebugFunction(juce::String a,juce::String b) {

}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

void NewProjectAudioProcessorEditor::timerCallback(){
    repaint();
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
