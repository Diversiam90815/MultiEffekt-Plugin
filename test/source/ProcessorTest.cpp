#include <gtest/gtest.h>

#include "PluginProcessor.h"



TEST(PluginProcessor, PrepareToPlay)
{
	PluginProcessor processor;
	processor.prepareToPlay(44100, 512);

	ASSERT_NO_THROW(processor.prepareToPlay(44100, 512)); // Ensure no exceptions are thrown
}

TEST(PluginProcessor, ProcessBlock)
{
	PluginProcessor processor;
	processor.prepareToPlay(44100, 512);

	juce::AudioBuffer<float> buffer(2, 512);
	buffer.clear();
	buffer.setSample(0, 0, 1.0f);

	juce::MidiBuffer midi;
	processor.processBlock(buffer, midi);

	ASSERT_NE(buffer.getSample(0, 0), 0.0f); // Expect processing to occur
}

