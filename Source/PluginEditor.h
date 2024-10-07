
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class PluginEditor : public AudioProcessorEditor
{
public:
	PluginEditor(PluginProcessor &);
	~PluginEditor() override;

	//==============================================================================
	void paint(Graphics &) override;
	void resized() override;

private:
	PluginProcessor &audioProcessor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
