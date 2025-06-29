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
#include "Distortion/Distortion.h"
#include "Delay/Delay.h"
#include "Panner/PannerManager.h"
#include "ParametricEQ/ParametricEQ.h"


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

	const juce::String									getName() const override { return ""; }

	bool												acceptsMidi() const override { return false; }

	bool												producesMidi() const override { return false; }

	bool												isMidiEffect() const override { return false; }

	double												getTailLengthSeconds() const override { return 0.0; }

	int													getNumPrograms() override { return 1; }

	int													getCurrentProgram() override { return 0; }

	void												setCurrentProgram(int index) override { juce::ignoreUnused(index); }

	const juce::String									getProgramName(int index) override
	{
		juce::ignoreUnused(index);
		return {};
	}

	void changeProgramName(int index, const juce::String &newName) override { juce::ignoreUnused(index, newName); }

	void getStateInformation(juce::MemoryBlock &destData) override { juce::ignoreUnused(destData); };

	void setStateInformation(const void *data, int sizeInBytes) override { juce::ignoreUnused(data, sizeInBytes); }


private:
	void updateParameters();

	void setParameter(const std::string &name, float value);

	template <typename EffectType, size_t N>
	void							   updateEffectParameters(EffectType &effect, const std::array<const char *, N> &parameters);

	void							   updateGainParameters();
	void							   updateDelayParameters();
	void							   updateDistortionParameters();
	void							   updatePannerParameters();
	void							   updateEQParameters();

	void							   setOutput(float value);

	void							   setInput(float value);


	Distortion<float>				   mDistortionModule;

	Delay<float>					   mDelayModule;

	PannerManager<float>			   mPannerModule;

	ParametricEQ<float>				   mEQModule;

	juce::SmoothedValue<float>		   mInput;

	juce::SmoothedValue<float>		   mOutput;

	int								   mNumInputChannels{0};

	juce::AudioProcessorValueTreeState mValueTreeState;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
