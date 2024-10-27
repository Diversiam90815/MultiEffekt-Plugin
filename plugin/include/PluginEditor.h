
#pragma once

#include "PluginProcessor.h"

//==============================================================================
/**
 */
class PluginEditor : public juce::AudioProcessorEditor
{
public:
	PluginEditor(PluginProcessor &);
	~PluginEditor() override;

	//==============================================================================
	void paint(juce::Graphics &) override;
	void resized() override;

private:
	PluginProcessor &audioProcessor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
