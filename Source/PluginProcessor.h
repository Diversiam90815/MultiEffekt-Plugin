
#pragma once

#include <JuceHeader.h>

#include "Parameters.h"


class PluginProcessor : public AudioProcessor, public AudioProcessorValueTreeState::Listener
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

	AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

	void										  parameterChanged(const String &parameterID, float newValue) override;


	//==============================================================================
	//						PUBLIC METHODS - JUCE OVERRIDES
	//==============================================================================

	void prepareToPlay(double sampleRate, int samplesPerBlock) override;

	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

	void										  processBlock(AudioBuffer<float> &, MidiBuffer &) override;

	AudioProcessorEditor						 *createEditor() override;

	bool										  hasEditor() const override;

	const String								  getName() const override;

	bool										  acceptsMidi() const override;

	bool										  producesMidi() const override;

	bool										  isMidiEffect() const override;

	double										  getTailLengthSeconds() const override;

	int											  getNumPrograms() override;

	int											  getCurrentProgram() override;

	void										  setCurrentProgram(int index) override;

	const String								  getProgramName(int index) override;

	void										  changeProgramName(int index, const String &newName) override;

	void										  getStateInformation(MemoryBlock &destData) override;

	void										  setStateInformation(const void *data, int sizeInBytes) override;


private:
	//==============================================================================
	//						PRIVATE OBJECTS
	//==============================================================================

	AudioProcessorValueTreeState mValueTreeState;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
};
