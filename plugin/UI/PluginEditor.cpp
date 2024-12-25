/*
  ==============================================================================

	Module			PluginEditor
	Description		Main module for the UI

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PluginEditor::PluginEditor(PluginProcessor &p) : juce::AudioProcessorEditor(&p), audioProcessor(p)
{
	setSize(400, 300);
}


PluginEditor::~PluginEditor()
{
}


//==============================================================================
void PluginEditor::paint(juce::Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.setColour(juce::Colours::white);
	g.setFont(juce::FontOptions(15.0f));
	g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}


void PluginEditor::resized()
{
}
