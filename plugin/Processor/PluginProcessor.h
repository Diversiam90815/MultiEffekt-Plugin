/*
  ==============================================================================

	Module			MainPluginProcessor
	Description		Main processor of the plugin

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "Project.h"
#include "Parameters.h"
#include "Distortion.h"
#include "Delay.h"
#include "PannerManager.h"


class PluginProcessor : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
	PluginProcessor();
	~PluginProcessor();


	juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	void												parameterChanged(const juce::String &parameterID, float newValue) override;

	void												prepareToPlay(double sampleRate, int samplesPerBlock) override;

	void												releaseResources() override {}

	bool												isBusesLayoutSupported(const BusesLayout &layouts) const override;

	void												processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

	juce::AudioProcessorEditor						   *createEditor() override;

	bool												hasEditor() const override { return true; }

	const juce::String									getName() const override {}

	bool												acceptsMidi() const override { return false; }

	bool												producesMidi() const override { return false; }

	bool												isMidiEffect() const override { return false; }

	double												getTailLengthSeconds() const override { return 0.0; }

	int													getNumPrograms() override { return 1; }

	int													getCurrentProgram() override { return 0; }

	void												setCurrentProgram(int index) override {}

	const juce::String									getProgramName(int index) override { return {}; }

	void												changeProgramName(int index, const juce::String &newName) override {}

	void												getStateInformation(juce::MemoryBlock &destData) override {};

	void												setStateInformation(const void *data, int sizeInBytes) override {}


private:
	void							   updateParameters();

	void							   updateGainParameter();

	void							   updateDelayParameter();

	void							   updateDistortionParameter();

	void							   updatePannerParameter();

	void							   setOutput(float value);

	void							   setInput(float value);


	Distortion<float>				   mDistortionModule;

	Delay<float>					   mDelayModule;

	PannerManager<float>			   mPanner;

	juce::SmoothedValue<float>		   mInput;

	juce::SmoothedValue<float>		   mOutput;

	int								   mNumInputChannels{0};

	juce::AudioProcessorValueTreeState mValueTreeState;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
