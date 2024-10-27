
#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "Project.h"
#include "Parameters.h"

#include "Distortion.h"


class PluginProcessor : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
	//==============================================================================
	//						CONSTRUCTOR - DESTRUCTOR
	//==============================================================================

	PluginProcessor();

	~PluginProcessor() override;


	//==============================================================================
	//						PUBLIC METHODS
	//==============================================================================

	juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	void												parameterChanged(const juce::String &parameterID, float newValue) override;

	DistortionType										getCurrentDistortionType() const;
	void												setCurrentDistortionType(const DistortionType newType);


	//==============================================================================
	//						PUBLIC METHODS - JUCE OVERRIDES
	//==============================================================================

	void												prepareToPlay(double sampleRate, int samplesPerBlock) override;

	void												releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

	void						processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

	juce::AudioProcessorEditor *createEditor() override;

	bool						hasEditor() const override;

	const juce::String			getName() const override;

	bool						acceptsMidi() const override;

	bool						producesMidi() const override;

	bool						isMidiEffect() const override;

	double						getTailLengthSeconds() const override;

	int							getNumPrograms() override;

	int							getCurrentProgram() override;

	void						setCurrentProgram(int index) override;

	const juce::String			getProgramName(int index) override;

	void						changeProgramName(int index, const juce::String &newName) override;

	void						getStateInformation(juce::MemoryBlock &destData) override;

	void						setStateInformation(const void *data, int sizeInBytes) override;


private:
	//==============================================================================
	//						PRIVATE METHODS
	//==============================================================================
	template <typename SampleType>
	SampleType processSoftClipping(SampleType input);

	template <typename SampleType>
	SampleType processHardClipping(SampleType input);

	template <typename SampleType>
	SampleType processSaturation(SampleType input);

	template <typename SampleType>
	SampleType						   processSample(SampleType input) noexcept;


	//==============================================================================
	//						PRIVATE OBJECTS
	//==============================================================================

	float							   drive;
	float							   input;
	float							   output;
	float							   blend;

	std::atomic<DistortionType>		   mDistortionType;

	Distortion<float>				   mDistortionModule;

	juce::AudioProcessorValueTreeState mValueTreeState;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
